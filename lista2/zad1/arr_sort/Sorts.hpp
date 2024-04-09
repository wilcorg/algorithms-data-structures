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
private:
    static int32_t qs_partition(std::vector<int32_t>& array, int32_t p, int32_t r, SortMetric& metric);
    static void quick_sort_impl(std::vector<int32_t>& array, int32_t p, int32_t r, SortMetric& metric);
    static void hybrid_quick_sort_impl(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric, const int32_t& threshold);
};


#endif //ARR_SORT_SORTS_HPP
