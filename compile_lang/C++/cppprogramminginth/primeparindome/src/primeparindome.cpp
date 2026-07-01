#ifndef __clang__
    #pragma GCC optimize("O3", "unroll-loops")
    #ifdef __x86_64__
        #pragma GCC target("avx2")
    #else
        #pragma GCC target("arch=armv8-a+simd")
    #endif
#endif

#include <bits/stdc++.h>

using namespace std;

int is_prime(int n){
    int i;
    if (n == 1 || n % 2 == 0){
        return 0;
    }else
    for (i = 3; i < (int)(sqrt(n)) + 1; i+=2){
        if (n % i == 0){return 0;}
    }
    return 1;
}

int is_parindome(int n){
    string nums = to_string(n);
    string renums;
    while(n > 0){
        renums += '0' + (n%10);
        n /= 10;
    }
    return (nums == renums)?(1):(0);
}

signed main(){
    int intiger;
    cin >> intiger;
    int nums = intiger;
    while(1) {
        if (is_prime(nums) && is_parindome(nums)){
            printf("%d\n", nums);
            return 0;
        }
        nums++;
    }
    return 1;
}