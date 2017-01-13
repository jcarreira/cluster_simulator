#ifndef _EVENT_H_
#define _EVENT_H_

#include "Time.h"
#include "Task.h"
#include "Job.h"
#include "Scheduler.h"
#include <memory>
#include <string>

namespace simulator {

class Event {
public:
    Event(Time);
    virtual ~Event() = default;

    virtual void process() = 0;
    virtual std::string getType() const = 0;
    
    double time;
};

// scheduler computes necessary number of tasks
// and deploys them in the right place (i.e., creates start task events)
class ScheduleJobEvent : public Event {
public:
    ScheduleJobEvent(Time, JobPtr, SchedPtr);
    ~ScheduleJobEvent() = default;

    void process() override final;
    std::string getType() const override final { return "ScheduleJobEvent"; }

public:
    JobPtr job;
    SchedPtr scheduler;
};

// task is deployed in a node and starts running
// this event creates a task ends event
class StartTaskEvent : public Event {
public:
    StartTaskEvent(Time, TaskPtr);
    void process() override final;
    std::string getType() const override final { return "StartTaskEvent"; }

    TaskPtr task_;
};

// Task ends and creates an event 
class EndTaskEvent : public Event {
public:
    EndTaskEvent(Time, TaskPtr);
    void process() override final;
    std::string getType() const override final { return "EndTaskEvent"; }
    
    TaskPtr task_;
};

// message gets to the scheduler.
// Scheduler is informed that task has ended and can decide on faith output
// need to ask Shivaram about this
class EndTaskSchedulerEvent : public Event {
public:
    EndTaskSchedulerEvent(Time, TaskPtr);
    void process() override final;
    std::string getType() const override final { return "EndTaskSchedulerEvent"; }

    TaskPtr task_;
};

// Node malfunctions and goes down
class NodeDownEvent : public Event {
public:
    NodeDownEvent(Time, NodePtr);
    void process() override final;
    std::string getType() const override final { return "NodeDownEvent"; }

    NodePtr node;
};

class CheckStragglersEvent : public Event {
public:
    CheckStragglersEvent(Time);
    void process() override final;
    std::string getType() const override final { return "CheckStragglersEvent"; }
};

struct EventComparator {
    bool operator()(const std::shared_ptr<Event>& e1,
            const std::shared_ptr<Event>&e2) {
        return e2->time < e1->time;
    }
};

}

#endif // _EVENT_H_
