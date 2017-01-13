/* Copyright 2016 Joao Carreira */

#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <utility>

extern double current_time;

namespace simulator {

struct INFO {
    static const int value = 5;
};
struct ERROR {
    static const int value = 10;
};

#if __GNUC__ >= 7
struct FLUSH {
};

struct NO_FLUSH {
};
    
template<typename T, typename K = NO_FLUSH, typename ... Params>
#else
template<typename T, typename ... Params>
#endif
bool LOG(Params&& ... param) {

    auto f = [](const auto& arg) {
        std::cout << " " << arg;
    };

    // print timestamp
    std::cout << current_time << "\t";

 __attribute__((unused))
    int dummy[] = { 0, ( (void) f(std::forward<Params>(param)), 0) ... }; 

#if __GNUC__ >= 7
    if constexpr (std::is_same(K, FLUSH)) {
        std::cout << std::endl;
    }
#else
    std::cout << std::endl;
#endif
//    sl.signal();

    return true; // success
}

} 

#endif // _LOG_H_
