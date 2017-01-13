#include "Job.h"

namespace simulator {

Job::Job(Time time, JobId jid, std::vector<TaskPtr> tasks) :
    time_(time),
    tasks_(tasks),
    job_id_(jid) {}


void Job::addTask(TaskPtr task) {
    tasks_.push_back(task);
}

std::ostream& operator<<(std::ostream& os, const Job& j) {
    os << "Job" 
       << " N tasks: " << j.tasks_.size()
       << std::endl;
    return os;
}

}
