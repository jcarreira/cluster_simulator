#ifndef _PARAMS_H_
#define _PARAMS_H_

#include <cstdint>
#include <string>

namespace simulator {

class Params {
public:
    uint64_t disk_bw;               // MBps
    double disk_lat;                //
    uint64_t nvm_bw;                // Gbps
    double nvm_lat;                 //
    uint64_t nw_bw;                 // Gbps
    double nw_lat;                  //
    uint64_t use_migration;         // 0 / 1
    uint64_t job_data_size;         // GB
    double stragglers_time;         // 
    double input_task_size;         // 
    double output_task_size;        // 
    double strag_slowdown;          // 
    double strag_check_slowdown;    // 
    double avg_task_duration;       // 
};

void read_params(Params& params, const std::string& params_file);

} // namespace simulator

#endif // _PARAMS_H_
