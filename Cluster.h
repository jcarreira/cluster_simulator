#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include "Node.h"
#include <memory>

namespace simulator {

class Cluster;

using ClusterPtr = std::shared_ptr<Cluster>;

class Cluster {
public:
    Cluster(uint64_t num_nodes,
            uint64_t cores_per_node,
            uint64_t nw_bw,
            uint64_t nw_lat,
            uint64_t disk_bw);
public:
    uint64_t num_nodes_;
    uint64_t cores_per_node_;
    uint64_t nw_bw_;
    uint64_t nw_lat_;
    uint64_t disk_bw_;

    std::vector<Node*> nodes_;
};

}

#endif // _CLUSTER_H_
