#ifndef BENCHMARK_COMMON_HPP
#define BENCHMARK_COMMON_HPP

#include "include/SortCommon.hpp"
#include "include/GenCommon.hpp"

typedef struct {
    GenTask genTask;
    SortTask sortTask;
    uint32_t k;
} BenchTask;
#endif // BENCHMARK_COMMON_HPP