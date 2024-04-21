#ifndef ARR_GEN_GENCOMMON_HPP
#define ARR_GEN_GENCOMMON_HPP

#include <cstdint>
#include <vector>

enum GenStrategy {
    RANDOM, ASCENDING, DESCENDING
};

typedef struct {
    GenStrategy strategy;
    int32_t count;
    int32_t low;
    int32_t high;
} GenTask;

#endif //ARR_GEN_GENCOMMON_HPP
