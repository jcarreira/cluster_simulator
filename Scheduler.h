#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "Cluster.h"
#include "Job.h"
#include "Log.h"
#include <memory>
#include <map>

namespace simulator {

class Scheduler;

using SchedPtr = std::shared_ptr<Scheduler>;

class Scheduler {
public:
    Scheduler(ClusterPtr);

    void scheduleJob(JobPtr);
    void completeTask(JobId, TaskPtr);

    bool isJobDone(JobId);
    uint64_t getNumTasks(JobId);

    uint64_t getNumActiveJobs() const;

    void deployTask(TaskPtr task);

    void checkStragglers();
    void checkStragglers(JobPtr);

    void replicateTask(JobPtr, const TaskPtr);

    uint64_t newTaskId() { static uint64_t id = 0; return id++; }

public:
    ClusterPtr cluster_;
    std::map<JobId, JobPtr> idToJob_;
    std::map<JobId, std::vector<TaskPtr>> scheduledTasks_;
    std::map<JobId, std::vector<TaskPtr>> jobCompletedTasks_;
    uint64_t nActiveJobs_;
};

} // namespace simulator

#endif // _SCHEDULER_H_

