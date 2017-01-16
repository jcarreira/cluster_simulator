#include "Event.h"
#include "Log.h"
#include "Scheduler.h"
#include "Params.h"

extern void add_to_queue(std::shared_ptr<simulator::Event> event);
extern simulator::SchedPtr scheduler;
extern simulator::Params params;

#define CHECK_STRAGGLERS 1

namespace simulator {

Event::Event(Time t) :
    time(t) {}

ScheduleJobEvent::ScheduleJobEvent(Time time, JobPtr j, SchedPtr sch) :
    Event(time),
    job(j), scheduler(sch)
{ }

void ScheduleJobEvent::process() {
    LOG<INFO>("ScheduleJobEvent::process");

    scheduler->scheduleJob(job);
}

StartTaskEvent::StartTaskEvent(Time time, TaskPtr task) :
    Event(time),
    task_(task)
{}

void StartTaskEvent::process() {
    LOG<INFO>("StartTaskEvent::process");

    Time taskCompletionTime = task_->getTaskCompletionTime();

    // task is finishing
    add_to_queue(std::make_shared<EndTaskEvent>(
                current_time + taskCompletionTime,
                task_));
}

EndTaskEvent::EndTaskEvent(Time time, TaskPtr task) :
    Event(time),
    task_(task)
{}

void EndTaskEvent::process() {
    LOG<INFO>("EndTaskEvent::process");
    LOG<INFO>("task id: ", task_->task_id_);

    // inform scheduler
    task_->done_ = true;

    add_to_queue(std::make_shared<EndTaskSchedulerEvent>(
                current_time + params.nw_lat,
                task_));
}

EndTaskSchedulerEvent::EndTaskSchedulerEvent(Time time, TaskPtr task) :
    Event(time),
    task_(task)
{ }

void EndTaskSchedulerEvent::process() {
    LOG<INFO>("EndTaskSchedulerEvent::process");

    auto jobid = task_->jobId;

    if (task_->replicated_ == true) {
        LOG<INFO>("Killing clone");
        scheduler->completeTask(jobid, task_->clone);
    }

    scheduler->completeTask(jobid, task_);

    if (scheduler->isJobDone(jobid)) {
        LOG<INFO>("process Job done");
    }
}

CheckStragglersEvent::CheckStragglersEvent(Time time) :
    Event(time)
{ }

void CheckStragglersEvent::process() {
    LOG<INFO>("CheckStragglersEvent::process");

    if (CHECK_STRAGGLERS) {
        // check all jobs
        scheduler->checkStragglers();
    } else {

    }

    LOG<INFO>("NumActiveJobs: ", scheduler->getNumActiveJobs());
    if (scheduler->getNumActiveJobs()) {
        add_to_queue(std::make_shared<CheckStragglersEvent>(
                    current_time + params.stragglers_time));
    }
}

void NodeDownEvent::process() {
    LOG<INFO>("NodeDownEvent::process");
}

} // namespace simulator

