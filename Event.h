class Event {
public:
    uint64_t time;
private:
};

// scheduler computes necessary number of tasks
// and deploys them in the right place (i.e., creates start task events)
class StartJobEvent {

};

// task is deployed in a node and starts running
// this event creates a task ends event
class StartTaskEvent {

};

// Task ends and creates an event 
class EndTaskEvent {

};

// message gets to the scheduler.
// Scheduler is informed that task has ended and can decide on faith output
// need to ask Shivaram about this
class EndTaskSchedulerEvent {

};

// Node malfunctions and goes down
class NodeDownEvent {

};

struct EventComparator {
    bool operator()(const std::shared_ptr<Event>& e1,
            const std::shared_ptr<Event>&e2) {
        return e1->time < e2->time;
    }
};
