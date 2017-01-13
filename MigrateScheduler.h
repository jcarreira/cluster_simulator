#ifndef _MIGRATE_SCHEDULER_H_
#define _MIGRATE_SCHEDULER_H_

#include "Scheduler.h"

namespace simulator {

class MigrateScheduler : public Scheduler {
public:
    MigrateScheduler(ClusterPtr);
    
    void checkStragglers(JobPtr) override;

public:

};

}

#endif // _MIGRATE_SCHEDULER_H_
