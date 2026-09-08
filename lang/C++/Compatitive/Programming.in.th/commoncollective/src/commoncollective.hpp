#ifndef CMNCLCT_HPP
    #define CMNCLCT_HPP
    
    #ifndef __clang__
        #pragma GCC optimize("O3", "unroll-loops")
        #ifdef __x86_64__
            #pragma GCC target("avx2")
        #else
            #pragma GCC target("arch=armv8-a+simd")
        #endif
    #endif  
    
    #include <iostream>
    #include <math.h>
    #include <string>
    #include <cstdlib>
    #include <vector>
    #include <stdio.h>
    #include <stdint.h>
    #include <stdarg.h>
#endif