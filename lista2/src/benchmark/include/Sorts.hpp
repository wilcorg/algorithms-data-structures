#ifndef ARR_SORT_SORTS_HPP
#define ARR_SORT_SORTS_HPP

#include "SortCommon.hpp"
#include <algorithm>
#include <iostream>

class Sorts {
public:
    static void arr_sort(SortTask& task);

protected:
    static void insertion_sort(SortTask& task, int32_t p, int32_t r);
    static void quick_sort(SortTask& task, int32_t p, int32_t r);
    static void hybrid_quick_sort(SortTask& task, int32_t p, int32_t r);
    static void dual_quick_sort(SortTask& task, int32_t p, int32_t r);
    static void merge_sort(SortTask& task, int32_t p, int32_t r);
    static void k_merge_sort(SortTask& task);

private:
    static int32_t qs_partition(SortTask& task, int32_t p, int32_t r);
    static std::pair<int32_t, int32_t> dual_qs_partition(SortTask& task, int32_t p, int32_t r);
    static void ms_merge(SortTask& task, int32_t left, int32_t mid, int32_t right);
    static std::vector<int32_t> kms_divide(SortTask& task, const std::vector<std::vector<int32_t>>& subvector, int32_t left, int32_t right);
    static std::vector<int32_t> kms_merge(SortTask& task, std::vector<int32_t> leftVector, std::vector<int32_t> rightVector);
};

#endif //ARR_SORT_SORTS_HPP
