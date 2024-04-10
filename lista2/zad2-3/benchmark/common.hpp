#ifndef ARR_SORT_COMMON_HPP
#define ARR_SORT_COMMON_HPP

#include <optional>
#include <random>
#include <vector>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/program_options.hpp>

enum SortStrategy {
    INSERTION, QUICK, QUICK_HYBRID, KMERGE, DUAL_QUICK, MERGE
};

enum GenerateMode {
    RANDOM, ASCENDING, DESCENDING
};

typedef struct {
    SortStrategy strategy;
    std::optional<int32_t> count;
    std::vector<int32_t> input;
    int32_t hybrid_sort_threshold;
} SortTask;

typedef struct {
    GenerateMode mode;
    uint32_t count;
    int32_t low;
    int32_t high;
    uint32_t k;
} GenerateTask;

typedef struct {
    int32_t n;
    uint32_t comparison_count;
    uint32_t swap_count;
} SortMetric;
#endif //ARR_SORT_COMMON_HPP
