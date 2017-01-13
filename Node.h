#ifndef _NODE_H_
#define _NODE_H_

#include "Task.h"
#include <memory>
#include <vector>

namespace simulator {

class Node;

using NodePtr = std::shared_ptr<Node>;
using NodeId = uint64_t;

class Node {
public:
    Node(uint64_t);

    void deployTask(TaskPtr task);
    void removeTask(TaskPtr task);

private:
    uint64_t num_cores_;
    
    std::vector<TaskPtr> cur_tasks_;
};

}

#endif // _NODE_H_
