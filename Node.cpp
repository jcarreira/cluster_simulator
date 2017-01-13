#include "Node.h"
#include "Event.h"

#include <stdexcept>

double SCHEDULER_TO_TASK_TIME = 0.001;

extern void add_to_queue(std::shared_ptr<simulator::Event> event);
extern double current_time;
namespace simulator {


Node::Node(uint64_t num_cores) :
    num_cores_(num_cores) 
    {}

void Node::deployTask(TaskPtr task) {
    cur_tasks_.push_back(task);

    if (cur_tasks_.size() >= num_cores_) {
        throw std::runtime_error("Too many tasks");
    }

    add_to_queue(std::make_shared<StartTaskEvent>(
                current_time + SCHEDULER_TO_TASK_TIME,
                task));
}

void Node::removeTask(TaskPtr task) {

//    for (auto& t : cur_tasks_) {
//        if (t == task) {
//
//        }
//    }


    auto it = std::find_if(std::begin(cur_tasks_), std::end(cur_tasks_), 
            [task](auto& t) {
                return t == task;
                });
    //if (it == cur_tasks_.end())
    //    throw std::runtime_error("Removing non existent task");
    //cur_tasks_.erase(it);
}

}
