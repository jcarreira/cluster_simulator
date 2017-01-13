#include "Scheduler.h"
#include <cassert>
#include <algorithm>

namespace simulator {

Scheduler::Scheduler(ClusterPtr cluster) :
    cluster_(cluster),
    nActiveJobs_(0)
{ }

void Scheduler::completeTask(JobId jid, TaskPtr task) {
    jobCompletedTasks_[jid].push_back(task);

    LOG<INFO>("scheduled tasks: ", scheduledTasks_[jid].size());
    LOG<INFO>("completed tasks: ",  jobCompletedTasks_[jid].size());
    if (isJobDone(jid)) {
        LOG<INFO>("Decreasing n jobs: ", nActiveJobs_);
        nActiveJobs_--;
    }
}

bool Scheduler::isJobDone(JobId jid) {
    return scheduledTasks_[jid].size() == jobCompletedTasks_[jid].size();
}

uint64_t Scheduler::getNumTasks(JobId jid) {
    return scheduledTasks_[jid].size();
}

uint64_t Scheduler::getNumActiveJobs() const {
    return nActiveJobs_;
}

void Scheduler::deployTask(TaskPtr task) {

    uint64_t location = task->data_location_;
    
    LOG<INFO>("Deploying task id: ", task->task_id_,
            " location: ", location);

    cluster_->nodes_[location]->deployTask(task);
}

void Scheduler::scheduleJob(JobPtr job) {
    auto tasks = job->tasks_;
    LOG<INFO>("Deploying ", tasks.size(), " tasks");

    for (auto task: tasks) {
        scheduledTasks_[job->job_id_].push_back(task);
        deployTask(task);
    }

    nActiveJobs_++;
    assert(idToJob_.find(job->job_id_) == idToJob_.end());
    idToJob_[job->job_id_] = job;
}

void Scheduler::checkStragglers() {
    LOG<INFO>("Checking stragglers (scheduler). ");

    for (auto& pair : idToJob_) {
        LOG<INFO>("Checking stragglers in job");
        checkStragglers(pair.second);
    }
}

void Scheduler::replicateTask(JobPtr job, const TaskPtr task) {
    task->setStraggler();

    TaskPtr clone = std::make_shared<Task>(
            task->jobId,
            newTaskId(),
            task->input_data_size,
            task->output_data_size,
            task->data_location_);

    clone->clone = task;
    task->clone = clone;

    // add task to scheduler list
    scheduledTasks_[job->job_id_].push_back(task);
    // add clone to job tasks
    
    //job->addTask(clone);

    // deploy this task in the cluster
    LOG<INFO>("replicateTask deploying task");
    deployTask(clone);
}

}

