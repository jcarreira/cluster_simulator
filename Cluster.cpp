#include "Cluster.h"

namespace simulator {

Cluster::Cluster(uint64_t num_nodes,
            uint64_t cores_per_node,
            uint64_t nw_bw,
            uint64_t nw_lat,
            uint64_t disk_bw) :
    num_nodes_(num_nodes),
    cores_per_node_(cores_per_node),
    nw_bw_(nw_bw),
    nw_lat_(nw_lat),
    disk_bw_(disk_bw) 
{
    // create pristine nodes
    for (uint64_t i = 0; i < num_nodes_; ++i) {
        nodes_.push_back(new Node(cores_per_node));
    }
}

} // namespace simulator

