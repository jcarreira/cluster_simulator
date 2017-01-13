#include <queue>
#include <memory>
#include <vector>

#include "Event.h"
#include "ReplicateScheduler.h"
#include "Cluster.h"
#include "Log.h"

#define MB (1024*1024)
#define GB (1024*MB)

using namespace simulator;

std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, EventComparator> event_queue;

extern const double STRAGGLER_TIME;
const double STRAGGLER_TIME = 0.100; // 100 ms
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
        tasks.push_back(std::make_shared<Task>(job_id, scheduler->newTaskId(), GB, 100 * MB, n_tasks));
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


int main() {
    auto cluster = createCluster();
    scheduler = std::make_shared<ReplicateScheduler>(cluster);
    auto jobs = createJobs(scheduler);

    //scheduler.start(cluster, jobs);

    std::shared_ptr<Event> first_event = std::make_shared<ScheduleJobEvent>(
                    jobs[0]->time_,
                    jobs[0],
                    scheduler);

    std::shared_ptr<Event> check_stragglers_event = std::make_shared<CheckStragglersEvent>(
            jobs[0]->time_ + STRAGGLER_TIME);

    add_to_queue(first_event);
    add_to_queue(check_stragglers_event);

    LOG<INFO>("Running simulation");
    run_simulation();
    
    LOG<INFO>("No more events. End of simulation");

    return 0;
}

