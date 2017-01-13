#ifndef _JOB_H_
#define _JOB_H_

#include "Time.h"
#include "Task.h"
#include <cstdint>
#include <memory>
#include <vector>
#include <iostream>

namespace simulator {

class Job;

using JobPtr = std::shared_ptr<Job>;
using JobId = uint64_t;

class Job {
public:
    Job(Time, JobId, std::vector<TaskPtr>);

    void addTask(TaskPtr task);

    std::ostream& operator<<(std::ostream& os) const {
        os << "Job time" << std::endl;
        return os;
    }

public:
   
    Time time_;
    std::vector<TaskPtr> tasks_;
    JobId job_id_;

};

std::ostream& operator<<(std::ostream&, const Job&);

}

#endif // _JOB_H_
