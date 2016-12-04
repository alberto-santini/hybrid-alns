//
// Created by alberto on 01/12/16.
//

#ifndef HYBRID_ALNS_SUPPRESSOUTPUT_H
#define HYBRID_ALNS_SUPPRESSOUTPUT_H

// When some shitty library decides it's ok to print out stuff on the console...
// I'll teach them with the following, ugly, non-portable code... yeah! (AS)

#include <cstdio>


#ifndef SUPPRESS_OUTPUT
    #define SUPPRESS_OUTPUT(x) \
    if(std::freopen("/dev/null", "w", stdout)) { \
        x \
        std::fclose(stdout); \
        if(!std::freopen("/dev/tty", "a", stdout)) {} \
    }
#endif


#endif //HYBRID_ALNS_SUPPRESSOUTPUT_H
