#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "Cluster.h"
#include "Job.h"
#include <memory>
#include <map>

namespace simulator {

class Scheduler;

using SchedPtr = std::shared_ptr<Scheduler>;

class Scheduler {
public:
    Scheduler(ClusterPtr);

    void completeTask(JobId);

public:
    ClusterPtr cluster_;
    std::map<JobId, Job> idToJob_;
    std::map<JobId, std::vector<TaskPtr>> scheduledTasks_;
    std::map<JobId, std::vector<TaskPtr>> jobCompletedTasks_;
};

} // namespace simulator

#endif // _SCHEDULER_H_
