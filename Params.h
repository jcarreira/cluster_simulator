#ifndef _PARAMS_H_
#define _PARAMS_H_

namespace simulator {

class Params {
public:
    uint64_t disk_bw;
    uint64_t mem_bw;
    uint64_t nw_bw;
    uint64_t nw_lat;
};

} // namespace simulator

#endif // _PARAMS_H_
