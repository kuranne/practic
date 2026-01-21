#ifndef __clang__
    #pragma GCC optimize("Ofast", "unroll-loops", "omit-frame-pointer", "inline")
    #ifdef __x86_64__
        #pragma GCC target("avx2")
    #else
        #pragma GCC target("arch=armv8-a+simd")
    #endif
    #include <bits/stdc++.h>
#else
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <cmath>
#endif
#define endl "\n"
#define unsync ios::sync_with_stdio(false); cin.tie(nullptr);
#define del delete
#define loop(i, x) for ((i) = 0; (i) < (x); (i)++)
#define ll long long
#define i64 int64_t
#define MAXIMUM (ll)pow(10, 9)

using namespace std;

signed main(const int argc, char *argv[]){
    unsync
    i64 
    *a = (i64*)calloc(1, sizeof(i64)),
    *b = (i64*)calloc(1, sizeof(i64)),
    *c = (i64*)calloc(1, sizeof(i64)),
    i; 

    if(argc == 3) {
        *(a + sizeof(i64) * 0) = stoll(argv[1]);
        *(b + sizeof(i64) * 0) = stoll(argv[2]);
    } else {
        cin >> a[0] >> b[0];
    }
    loop(i, *(a + sizeof(i64) * 0)) c[0]++;
    loop(i, *(b + sizeof(i64) * 0)) c[0]++;

    cout << c[0] << endl;

    del a; del b; del c;
    return 0;
}