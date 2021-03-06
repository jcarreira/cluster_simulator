#include "MigrateScheduler.h"
#include <cassert>
#include <algorithm>

namespace simulator {

MigrateScheduler::MigrateScheduler(ClusterPtr c) :
    Scheduler(c)
{
}

void MigrateScheduler::migrateTask(JobPtr job, TaskPtr task) {

}

// Spark way of dealing with stragglers
void MigrateScheduler::checkStragglers(JobPtr job) {
    LOG<INFO>("MigrateScheduler::checkStragglers. ", *job);

    std::vector<TaskPtr> finishedTasks;

    for (auto task : job->tasks_) {
        if (task->done_) {
            assert(task->getTaskCompletionTime() <= current_time);
            finishedTasks.push_back(task);
        }
    }
    
    if (finishedTasks.size() == 0)
        return;

    LOG<INFO>("Finished tasks size: ", finishedTasks.size());
    std::sort(finishedTasks.begin(), finishedTasks.end(),
            [](auto task1, auto task2) {
                return task1->getTotalTime() < task2->getTotalTime();
                });

    if (finishedTasks.size() >= 0.75 * job->tasks_.size()) {
        double median = finishedTasks[finishedTasks.size() / 2]->getTotalTime();

        LOG<INFO>("median: ", median);
       
        while (1) {
            for (auto task : job->tasks_) {
                if (false == task->done_ && (current_time - task->start_time) >= 1.5 * median) {
                    LOG<INFO>("Task ", task->getTaskId(), " is straggler");
                    // replicate Task
                    migrateTask(job, task);
                }
            }
        }
    }
}

} // namespace simulator
