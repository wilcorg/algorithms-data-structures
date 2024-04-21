#ifndef ARR_SORT_SORTSCOMMON_HPP
#define ARR_SORT_SORTSCOMMON_HPP

#include <optional>
#include <random>
#include <vector>

enum SortStrategy {
    INSERTION, QUICK, QUICK_HYBRID, DP_QUICK, MERGE, K_MERGE
};

typedef struct {
    uint32_t comparison_count;
    uint32_t swap_count;
} SortMetric;

typedef struct {
    SortStrategy strategy;
    bool is_present;
    int32_t hybrid_sort_threshold;
    int32_t present_limit;
} SortConfig;

typedef struct {
    const int32_t count;  // from stdin
    std::vector<int32_t> array;  // from stdin
    const SortConfig config;
    SortMetric metric;  // result holder
    int32_t max_el_width;
} SortTask;

#endif//ARR_SORT_SORTSCOMMON_HPP
