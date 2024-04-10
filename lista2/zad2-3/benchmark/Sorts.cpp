#include "Sorts.hpp"

void Sorts::insertion_sort(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric) {
    for (int32_t i = p + 1; i < r + 1; i++) {

        // element to insert into left hand
        int32_t key = array[i];
        // left hand max bound
        int32_t j = i - 1;

        while (j >= p) {
            if (metric.comparison_count++; array[j] > key) {
                // shift array elements to the right
                array[j + 1] = array[j];
                metric.swap_count += 1;
                j -= 1;
            } else {
                break;
            }
        }
        // replace first from the left shifted element
        array[j + 1] = key;
        metric.swap_count += 1;
    }
}

void Sorts::quick_sort(std::vector<int32_t> &array, SortMetric &metric) {
    quick_sort_impl(array, 0, (int32_t) array.size() - 1, metric);
}

void Sorts::hybrid_quick_sort(std::vector<int32_t> &array, SortMetric &metric, int32_t threshold) {
    hybrid_quick_sort_impl(array, 0, metric.n - 1, metric, threshold);
}

int32_t Sorts::qs_partition(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric) {
    int32_t x = array[r];
    int32_t i = p - 1;

    for (int32_t j = p; j <= r - 1; j++) {
        if (metric.comparison_count++; array[j] <= x) {
            i++;
            metric.swap_count += 1;
            std::swap(array[i], array[j]);
        }
    }
    metric.swap_count += 1;
    std::swap(array[i + 1], array[r]);

    return i + 1;
}

void Sorts::quick_sort_impl(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric) {
    if (p < r) {
        int32_t q = qs_partition(array, p, r, metric);
        quick_sort_impl(array, p, q - 1, metric);
        quick_sort_impl(array, q + 1, r, metric);
    }
}

void Sorts::hybrid_quick_sort_impl(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric,
                                   const int32_t &threshold) {
    if (p < r) {
        if (r - p > threshold) {
            int32_t q = qs_partition(array, p, r, metric);
            hybrid_quick_sort_impl(array, p, q - 1, metric, threshold);
            hybrid_quick_sort_impl(array, q + 1, r, metric, threshold);
        } else {
            insertion_sort(array, p, r, metric);
        }
    }
}

SortMetric Sorts::arr_sort(SortTask &task) {
    SortMetric metric{.n = task.count.value()};

    if (task.strategy == INSERTION) {
        Sorts::insertion_sort(task.input, 0, metric.n - 1, metric);
    } else if (task.strategy == QUICK) {
        Sorts::quick_sort(task.input, metric);
    } else if (task.strategy == QUICK_HYBRID) {
        Sorts::hybrid_quick_sort(task.input, metric, task.hybrid_sort_threshold);
    } else if (task.strategy == KMERGE) {
        Sorts::kmerge_sort(task.input, metric);
    } else if (task.strategy == DUAL_QUICK) {
        Sorts::dual_quick_sort(task.input, metric);
    } else if (task.strategy == MERGE) {
        Sorts::merge_sort(task.input, metric);
    }

    for (int32_t i = 0; i < metric.n - 1; i++) {
        if (task.input[i + 1] < task.input[i]) {
            std::cerr << "arr_sort: sorting algorithm failed" << std::endl;
            exit(1);
        }
    }
    return metric;
}

void Sorts::arr_print(const std::vector<int32_t> &array) {
    int32_t max_el = *std::max_element(std::begin(array), std::end(array));
    int32_t min_el = *std::min_element(std::begin(array), std::end(array));
    int32_t max_digit_len = static_cast<int32_t>(std::max(std::to_string(max_el).length(),
                                                          std::to_string(min_el).length()));

    for (int32_t val: array) {
        std::cout << std::setw(max_digit_len) << val << " ";
    }
    std::cout << std::endl;
}

void Sorts::kmerge_sort(std::vector<int32_t>& array, SortMetric &metric) {
    std::vector<std::vector<int32_t>> subvectors;
    std::vector<int32_t> candidate;

    for (auto num: array) {
        if (candidate.empty()) {
            candidate.push_back(num);
        } else {
            if (metric.comparison_count++; num < candidate.back()) {
                subvectors.push_back(candidate);
                candidate = {};
            }
            candidate.push_back(num);
        }
    }
    subvectors.push_back(candidate);

    auto result = divide(subvectors, 0, (int32_t) subvectors.size() - 1, metric);
    array = result;

}

std::vector<int32_t> Sorts::divide(const std::vector<std::vector<int32_t>> &subvector, int32_t left, int32_t right, SortMetric& metric) {
    if (left == right) {
        return subvector[left];
    }

    if (left + 1 == right) {
        return merge_two_lists(subvector[left], subvector[right], metric);
    }

    int32_t mid = (left + right) / 2;
    std::vector<int32_t> leftMerged = divide(subvector, left, mid, metric);
    std::vector<int32_t> rightMerged = divide(subvector, mid + 1, right, metric);

    return merge_two_lists(leftMerged, rightMerged, metric);
}

std::vector<int32_t> Sorts::merge_two_lists(std::vector<int32_t> leftVector, std::vector<int32_t> rightVector, SortMetric& metric) {
    std::vector<int32_t> result = {};

    int32_t l = 0;
    int32_t r = 0;
    int32_t ls = leftVector.size();
    int32_t rs = rightVector.size();

    while ((l < ls || r < rs)) {
        if (l == ls && r == rs) {
            break;
        }
        else if (l == ls && r < rs) {
            metric.swap_count += 1;
            result.push_back(rightVector[r]);
            r++;
        } else if (l < ls && r == rs) {
            metric.swap_count += 1;
            result.push_back(leftVector[l]);
            l++;
        } else {
            if (metric.comparison_count++; leftVector[l] < rightVector[r]) {
                metric.swap_count += 1;
                result.push_back(leftVector[l]);
                l++;
            } else {
                result.push_back(rightVector[r]);
                metric.swap_count += 1;
                r++;
            }
        }
    }
    return result;
}

void Sorts::dual_quick_sort(std::vector<int32_t> &array, SortMetric &metric) {
    dual_quick_sort_impl(array, 0, (int32_t) array.size() - 1, metric);
}

void Sorts::dual_quick_sort_impl(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric) {
    if (p < r) {
        auto pivot = dual_qs_partition(array, p, r, metric);
        dual_quick_sort_impl(array, p, pivot.first - 1, metric);
        dual_quick_sort_impl(array, pivot.first + 1, pivot.second - 1, metric);
        dual_quick_sort_impl(array, pivot.second + 1, r, metric);
    }
}

std::pair<int32_t, int32_t> Sorts::dual_qs_partition(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric) {
    std::pair<int32_t, int32_t> pivot = {};
    if (metric.comparison_count++; array[p] > array[r]) {
        metric.swap_count += 1;
        std::swap(array[p], array[r]);
    }

    int32_t j = p + 1;
    int32_t g = r - 1, k = p + 1, temp = array[p], q = array[r];
    while (k <= g) {

        if (metric.comparison_count++; array[k] < temp) {
            metric.swap_count += 1;
            std::swap(array[k], array[j]);
            j++;
        } else if (metric.comparison_count++; array[k] >= q) {
            while (metric.comparison_count++ && array[g] > q && k < g) {
                g--;
            }

            metric.swap_count += 1;
            std::swap(array[k], array[g]);
            g--;
            if (metric.comparison_count++; array[k] < temp) {
                metric.swap_count += 1;
                std::swap(array[k], array[j]);
                j++;
            }
        }
        k++;
    }
    j--;
    g++;

    metric.swap_count += 1;
    metric.swap_count += 1;
    std::swap(array[p], array[j]);
    std::swap(array[r], array[g]);

    pivot.first = j;
    pivot.second = g;

    return pivot;
}

void Sorts::merge_sort(std::vector<int32_t> &array, SortMetric &metric) {
    merge_sort_impl(array, 0, array.size() - 1, metric);
}

void Sorts::merge(std::vector<int32_t> &array, int32_t left, int32_t mid, int32_t right, SortMetric &metric) {
    std::vector<int> leftArray;
    std::vector<int> rightArray;

    int subarrayL = mid - left + 1;
    int subarrayR = right - mid;

    for (int i = 0; i < subarrayL; i++) {
        metric.swap_count += 1;
        leftArray.push_back(array[left + i]);
    }
    for (int j = 0; j < subarrayR; j++) {
        metric.swap_count += 1;
        rightArray.push_back(array[mid + 1 + j]);
    }

    int li = 0, ri = 0;
    int merged_i = left;

    while (li < subarrayL && ri < subarrayR) {
        if (metric.comparison_count++; leftArray[li] <= rightArray[ri]) {
            metric.swap_count += 1;
            array[merged_i] = leftArray[li];
            li++;
        } else {
            metric.swap_count += 1;
            array[merged_i] = rightArray[ri];
            ri++;
        }
        merged_i++;
    }

    while (li < subarrayL) {
        metric.swap_count += 1;
        array[merged_i] = leftArray[li];
        li++;
        merged_i++;
    }
    while (ri < subarrayR) {
        metric.swap_count += 1;
        array[merged_i] = rightArray[ri];
        ri++;
        merged_i++;
    }
}

void Sorts::merge_sort_impl(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric) {
    if (r > p) {

        int32_t mid = (p + r) / 2;
        merge_sort_impl(array, p, mid, metric);
        merge_sort_impl(array, mid + 1, r, metric);
        merge(array, p, mid, r, metric);
    }
}
