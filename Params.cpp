#include "Params.h"

#include <sstream>
#include <fstream>

namespace simulator {

void read_params(Params& params, const std::string& params_file) {
    std::ifstream input(params_file);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream lineStream(line);

        std::string key;
        lineStream >> key;

        if (key[key.length()-1] != ':')
            throw std::runtime_error("Wrong param");

        key = key.substr(0, key.length()-1);

        if (key == "nw_bw") {
            lineStream >> params.nw_bw;
        } else if (key == "nw_lat") {
            lineStream >> params.nw_lat;
        } else if (key == "nvm_lat") {
            lineStream >> params.nvm_lat;
        } else if (key == "nvm_bw") {
            lineStream >> params.nvm_bw;
        } else if (key == "disk_bw") {
            lineStream >> params.disk_bw;
        } else if (key == "disk_lat") {
            lineStream >> params.disk_lat;
        } else if (key == "use_migration") {
            lineStream >> params.use_migration;
        } else if (key == "job_data_size") {
            lineStream >> params.job_data_size;
        } else if (key == "stragglers_time") {
            lineStream >> params.stragglers_time;
        } else if (key == "input_task_size") {
            lineStream >> params.input_task_size;
        } else if (key == "output_task_size") {
            lineStream >> params.output_task_size;
        } else if (key == "strag_slowdown") {
            lineStream >> params.strag_slowdown;
        } else if (key == "strag_check_slowdown") {
            lineStream >> params.strag_check_slowdown;
        } else if (key == "avg_task_duration") {
            lineStream >> params.avg_task_duration;
        }
    }
}

};
