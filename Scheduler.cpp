#include "Scheduler.h"

namespace simulator {

Scheduler::Scheduler(ClusterPtr cluster) :
    cluster_(cluster)
{}

void Scheduler::completeTask(JobId jid) {
    jobCompletedTasks_[jid]++;
}

}
