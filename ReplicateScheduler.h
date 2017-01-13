#ifndef _REPLICATE_SCHEDULER_H_
#define _REPLICATE_SCHEDULER_H_

#include "Scheduler.h"

namespace simulator {

class ReplicateScheduler : public Scheduler {
public:
    ReplicateScheduler(ClusterPtr);
    
    void checkStragglers(JobPtr) override;

public:

};

}

#endif // _REPLICATE_SCHEDULER_H_
