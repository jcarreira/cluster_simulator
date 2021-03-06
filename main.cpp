#include <queue>
#include <memory>
#include <vector>

#include "Event.h"
#include "Params.h"
#include "ReplicateScheduler.h"
#include "MigrateScheduler.h"
#include "Cluster.h"
#include "Log.h"
#include "Params.h"

static const uint64_t MB = (1024*1024);
static const uint64_t GB = 1024 * MB;

using namespace simulator;

std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, EventComparator> event_queue;

extern simulator::Params params;
simulator::Params params;

extern double current_time;
double current_time = 0;

SchedPtr scheduler;

void run_simulation() {
    while (event_queue.size()) {
        auto event = event_queue.top();
        event_queue.pop();

        if (event->time < current_time)
            throw std::runtime_error("Wrong time");        
        current_time = event->time;

        LOG<INFO>("Processing event.");
        LOG<INFO>("event time ", current_time);
        LOG<INFO>("event type", event->getType());

        event->process();
    }
}

std::vector<std::shared_ptr<Job>> createJobs(SchedPtr scheduler) {
 
    std::vector<std::shared_ptr<Job>> jobs;
    std::vector<std::shared_ptr<Task>> tasks;

    uint64_t job_id = 42;

    for (uint64_t n_tasks = 0; n_tasks < 50; ++n_tasks) {
        tasks.push_back(std::make_shared<Task>(job_id, scheduler->newTaskId(), 10 * GB, 100 * MB, n_tasks));
    }

    Time start = 1; // first job at 1 second
    jobs.push_back(std::make_shared<Job>(start,
                job_id,
                tasks));

    return jobs;
}

ClusterPtr createCluster() {
    return std::make_shared<Cluster>(
            50, // nodes
            4, // 4 cores per node
            200, // NW bandwidth Gbps 
            1, // network latency (us)
            100 // disk bandwidth MB/s
            );
}

void add_to_queue(std::shared_ptr<Event> event) {
    event_queue.push(event);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "./simulator <config_file>" << std::endl;
        return -1;
    }

    LOG<INFO>("Reading params from: ", argv[1]);
    std::string config_file = argv[1];
    read_params(params, config_file);

    LOG<INFO>("Creating cluster..");
    auto cluster = createCluster();
    LOG<INFO>("Creating scheduler and jobs..");

    if (params.use_migration) {
        scheduler = std::make_shared<MigrateScheduler>(cluster);
    } else {
        scheduler = std::make_shared<ReplicateScheduler>(cluster);
    }
    auto jobs = createJobs(scheduler);

    std::shared_ptr<Event> first_event = std::make_shared<ScheduleJobEvent>(
                    jobs[0]->time_,
                    jobs[0],
                    scheduler);

    std::shared_ptr<Event> check_stragglers_event = std::make_shared<CheckStragglersEvent>(
            jobs[0]->time_ + params.stragglers_time);

    LOG<INFO>("Adding deploy job event and check stragglers event");
    add_to_queue(first_event);
    add_to_queue(check_stragglers_event);

    LOG<INFO>("Running simulation");
    run_simulation();
    
    LOG<INFO>("No more events. End of simulation");

    return 0;
}

