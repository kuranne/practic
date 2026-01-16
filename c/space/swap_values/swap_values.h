#ifndef swap_value
#define swap_values(a, b) do { \
    __typeof__(a) temp_holder = (a); \
    (a) = (b); \
    (b) = temp_holder; \
} while (0)
#endif