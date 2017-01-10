#ifndef _TASK_H_
#define _TASK_H_

#include "Time.h"
#include <memory>

namespace simulator {

class Task;

using TaskPtr = std::shared_ptr<Task>;

class Task {
public:
    using JobId = uint64_t;
    Task(JobId jid, uint64_t task_id, uint64_t ids,
            uint64_t ods, uint64_t data_location) :
        jobId(jid),
        input_data_size(ids),
        output_data_size(ods),
        task_id_(task_id),
        data_location_(data_location)
    {}

public:
    Time start_time;
    Time task_completion_time;

    JobId jobId;

    // data sizes
    uint64_t input_data_size;
    uint64_t output_data_size;

    uint64_t task_id_;
    uint64_t data_location_;
};

}

#endif // _TASK_H_
