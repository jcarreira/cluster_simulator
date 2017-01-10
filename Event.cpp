#include "Event.h"
#include "Log.h"
#include "Scheduler.h"
#include <random>

extern void add_to_queue(std::shared_ptr<simulator::Event> event);
extern simulator::SchedPtr scheduler;

// 1 ms
static const double TIME_TO_INFORM_SCHEDULER = 0.001;

namespace simulator {

Event::Event(Time t) :
    time(t) {}

ScheduleJobEvent::ScheduleJobEvent(Time time, JobPtr j, SchedPtr sch) :
    Event(time),
    job(j), scheduler(sch)
    { }


void deploy_task(ClusterPtr cluster, TaskPtr task) {

    uint64_t location = task->data_location_;
    
    LOG<INFO>("Deploying task id: ", task->task_id_,
            " location: ", location);

    cluster->nodes_[location]->deploy_task(task);
}


void ScheduleJobEvent::process() {
    LOG<INFO>("Processing ScheduleJobEvent");

    auto cluster = scheduler->cluster_;

    auto tasks = job->tasks_;

    LOG<INFO>("Deploying ", tasks.size(), " tasks");
    for (auto task: tasks) {
        deploy_task(cluster, task);
    }    
}

StartTaskEvent::StartTaskEvent(Time time, TaskPtr task) :
    Event(time),
    task_(task)
{}

void StartTaskEvent::process() {
    LOG<INFO>("Processing StartTaskEvent");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(10, 50);
    task_->task_completion_time = dis(gen);

    // task is finishing
    add_to_queue(std::make_shared<EndTaskEvent>(
                current_time + task_->task_completion_time,
                task_));
}

EndTaskEvent::EndTaskEvent(Time time, TaskPtr task) :
    Event(time),
    task_(task)
{}

void EndTaskEvent::process() {
    LOG<INFO>("Processing EndTaskEvent");

    // inform scheduler
    add_to_queue(std::make_shared<EndTaskSchedulerEvent>(
                current_time + TIME_TO_INFORM_SCHEDULER,
                task_));
}

EndTaskSchedulerEvent::EndTaskSchedulerEvent(Time time, TaskPtr task) :
    Event(time),
    task_(task)
{}

void EndTaskSchedulerEvent::process() {
    LOG<INFO>("Processing EndTaskSchedulerEvent");

    auto jobid = task_->jobId;
    scheduler->completeTask(jobid);

    auto n_tasks = scheduler->numTasks_[jobid];

    if (scheduler->jobCompletedTasks_[jobid] >= n_tasks) {
        LOG<INFO>("Job done");
    }
}

CheckStragglersEvent::CheckStragglersEvent(Time time) :
    Event(time)
{ }

void CheckStragglersEvent::process() {
    LOG<INFO>("Processing CheckStragglersEvent");

}

} // namespace simulator
