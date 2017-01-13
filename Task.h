#ifndef _TASK_H_
#define _TASK_H_

#include "Time.h"
#include "Log.h"
#include <memory>
#include <random>

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
        data_location_(data_location),
        done_(false),
        straggler_(false),
        replicated_(false)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);
        //std::uniform_real_distribution<> dis(10, 50);
        taskCompletionTime = 20.0 + dis(gen);

        if (task_id_ == 20)
            taskCompletionTime = 50;

        LOG<INFO>("Created task.",
                " taskCompletionTime: ", taskCompletionTime);
    }

    double getTotalTime() const {
        if (done_ == false)
            throw std::runtime_error("Task has not finished");

        return taskCompletionTime - start_time;
    }

    void setStraggler() { straggler_ = true; }

    Time getTaskCompletionTime() const {
        return taskCompletionTime;
    }

    uint64_t getTaskId() const { return task_id_; }

public:
    // time when task started running
    Time start_time;
    // time when task completed
    Time taskCompletionTime;

    JobId jobId;

    // data sizes
    uint64_t input_data_size;
    uint64_t output_data_size;

    uint64_t task_id_;
    uint64_t data_location_;

    bool done_; // true if task is complete
    bool straggler_; // true if task is a straggler

    bool replicated_;

    TaskPtr clone;
};

}

#endif // _TASK_H_


