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

    virtual void scheduleJob(JobPtr);
    virtual void completeTask(JobId, TaskPtr);

    virtual bool isJobDone(JobId);
    virtual uint64_t getNumTasks(JobId);

    virtual uint64_t getNumActiveJobs() const;

    virtual void deployTask(TaskPtr task);

    virtual void checkStragglers();
    virtual void checkStragglers(JobPtr) = 0;

    virtual void replicateTask(JobPtr, const TaskPtr);

    virtual uint64_t newTaskId() { static uint64_t id = 0; return id++; }

public:
    ClusterPtr cluster_;
    std::map<JobId, JobPtr> idToJob_;
    std::map<JobId, std::vector<TaskPtr>> scheduledTasks_;
    std::map<JobId, std::vector<TaskPtr>> jobCompletedTasks_;
    uint64_t nActiveJobs_;
};

} // namespace simulator

#endif // _SCHEDULER_H_

