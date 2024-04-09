#include "Sorts.hpp"

void Sorts::insertion_sort(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric) {
    for (int32_t i = p + 1; i < r + 1; i++) {
        arr_print(array);

        // element to insert into left hand
        int32_t key = array[i];
        // left hand max bound
        int32_t j = i - 1;

        while (j >= p) {
            metric.comparison_count += 1;
            if (array[j] > key) {
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
        metric.comparison_count += 1;
        if (array[j] <= x) {
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
        arr_print(array);
        quick_sort_impl(array, p, q - 1, metric);
        quick_sort_impl(array, q + 1, r, metric);
    }
}

void Sorts::hybrid_quick_sort_impl(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric,
                                   const int32_t &threshold) {
    if (p < r) {
        if (r - p > threshold) {
            int32_t q = qs_partition(array, p, r, metric);
            arr_print(array);
            hybrid_quick_sort_impl(array, p, q - 1, metric, threshold);
            hybrid_quick_sort_impl(array, q + 1, r, metric, threshold);
        } else {
            insertion_sort(array, p, r, metric);
        }
    }
}

SortMetric Sorts::arr_sort(Task &task) {
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

void Sorts::kmerge_sort(std::vector<int32_t> &array, SortMetric &metric) {
    std::vector<std::vector<int32_t>> subvectors;
    std::vector<int32_t> candidate;

    for (auto num: array) {
        if (candidate.empty()) {
            candidate.push_back(num);
        } else {
            metric.comparison_count += 1;
            if (num < candidate.back()) {
                subvectors.push_back(candidate);
                candidate = {};
            }
            candidate.push_back(num);
        }
    }
    subvectors.push_back(candidate);

    array = divide(subvectors, 0, (int32_t) subvectors.size(), metric);
}

std::vector<int32_t> Sorts::divide(std::vector<std::vector<int32_t>> &subvector, int32_t left, int32_t right, SortMetric& metric) {
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

std::vector<int32_t> Sorts::merge_two_lists(std::vector<int32_t> &leftVector, std::vector<int32_t> &rightVector, SortMetric& metric) {
    std::vector<int32_t> result = {};

    while (leftVector.size() + rightVector.size() != 0) {
        if (leftVector.empty()) {
            metric.swap_count += 1;
            result.push_back(rightVector.front());
            rightVector.erase(rightVector.begin());
        } else if (rightVector.empty()) {
            metric.swap_count += 1;
            result.push_back(leftVector.front());
            leftVector.erase(leftVector.begin());
        } else {
            metric.comparison_count += 1;
            if (leftVector.front() < rightVector.front()) {
                metric.swap_count += 1;
                result.push_back(leftVector.front());
                leftVector.erase(leftVector.begin());
            } else {
                metric.swap_count += 1;
                result.push_back(rightVector.front());
                rightVector.erase(rightVector.begin());
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
        arr_print(array);
        dual_quick_sort_impl(array, p, pivot.first - 1, metric);
        dual_quick_sort_impl(array, pivot.first + 1, pivot.second - 1, metric);
        dual_quick_sort_impl(array, pivot.second + 1, r, metric);
    }
}

std::pair<int32_t, int32_t> Sorts::dual_qs_partition(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric) {
    std::pair<int32_t, int32_t> pivot = {};
    metric.swap_count += 1;
    if (array[p] > array[r]) {
        std::swap(array[p], array[r]);
    }

    int32_t j = p + 1;
    int32_t g = r - 1, k = p + 1, temp = array[p], q = array[r];
    while (k <= g) {

        metric.comparison_count += 1;
        if (array[k] < temp) {
            std::swap(array[k], array[j]);
            j++;
            metric.comparison_count -= 1;
        } else if (array[k] >= q) {
            while (array[g] > q && k < g) {
                metric.comparison_count += 1;
                g--;
            }
            metric.comparison_count -= 1;

            metric.swap_count += 1;
            std::swap(array[k], array[g]);
            g--;
            metric.comparison_count += 1;
            if (array[k] < temp) {
                metric.swap_count += 1;
                std::swap(array[k], array[j]);
                j++;
            }
        }
        k++;
        metric.comparison_count += 1;
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
