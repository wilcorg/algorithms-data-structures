#ifndef ARR_SORT_SORTS_HPP
#define ARR_SORT_SORTS_HPP

#include <vector>
#include <string>
#include <iomanip>
#include "common.hpp"

class Sorts {
public:
    static SortMetric arr_sort(Task& task);
    static void arr_print(const std::vector<int32_t>& array);

protected:
    static void insertion_sort(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric);
    static void quick_sort(std::vector<int32_t>& array, SortMetric& metric);
    static void hybrid_quick_sort(std::vector<int32_t>& array, SortMetric& metric, int32_t threshold);
    static void kmerge_sort(std::vector<int32_t>& array, SortMetric& metric);
    static void dual_quick_sort(std::vector<int32_t>& array, SortMetric& metric);
private:
    static int32_t qs_partition(std::vector<int32_t>& array, int32_t p, int32_t r, SortMetric& metric);
    static void quick_sort_impl(std::vector<int32_t>& array, int32_t p, int32_t r, SortMetric& metric);
    static void hybrid_quick_sort_impl(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric, const int32_t& threshold);
    static void dual_quick_sort_impl(std::vector<int32_t>& array, int32_t p, int32_t r, SortMetric& metric);

    static std::vector<int32_t> divide(std::vector<std::vector<int32_t>> &subvector, int32_t left, int32_t right, SortMetric& metric);
    static std::vector<int32_t> merge_two_lists(std::vector<int32_t>& leftVector, std::vector<int32_t>& rightVector, SortMetric& metric);

    static std::pair<int32_t, int32_t> dual_qs_partition(std::vector<int32_t>& array, int32_t p, int32_t r, SortMetric& metric);
};


#endif //ARR_SORT_SORTS_HPP
