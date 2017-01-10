#include "Job.h"

namespace simulator {

Job::Job(Time time, JobId jid, std::vector<TaskPtr> tasks) :
    time_(time),
    tasks_(tasks),
    job_id_(jid) {}

}
