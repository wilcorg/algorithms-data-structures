#include "Sorts.hpp"

void Sorts::insertion_sort(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric) {
    for (int32_t i = p + 1; i < r + 1; i++) {
        if (metric.n < 40) {
            arr_print(array);
        }

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
        if (metric.n < 40) {
            arr_print(array);
        }
        quick_sort_impl(array, p, q - 1, metric);
        quick_sort_impl(array, q + 1, r, metric);
    }
}

void Sorts::hybrid_quick_sort_impl(std::vector<int32_t> &array, int32_t p, int32_t r, SortMetric &metric,
                                   const int32_t &threshold) {
    if (p < r) {
        if (metric.n < 40) {
            arr_print(array);
        }

        if (r - p > threshold) {
            int32_t q = qs_partition(array, p, r, metric);
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
