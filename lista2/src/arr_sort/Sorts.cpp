#include "Sorts.hpp"
#include "SortUtils.hpp"

void Sorts::arr_sort(SortTask& task) {
    switch (task.config.strategy) {
        case INSERTION:
            Sorts::insertion_sort(task, 0, task.count - 1);
            break;
        case QUICK:
            Sorts::quick_sort(task, 0, task.count - 1);
            break;
        case QUICK_HYBRID:
            Sorts::hybrid_quick_sort(task, 0, task.count - 1);
            break;
        case DP_QUICK:
            Sorts::dual_quick_sort(task, 0, task.count - 1);
            break;
        case MERGE:
            Sorts::merge_sort(task, 0, task.count - 1);
            break;
        case K_MERGE:
            Sorts::k_merge_sort(task);
            break;
    }

    for (int32_t i = 0; i < task.count - 1; i++) {
        if (task.array[i + 1] < task.array[i]) {
            std::cerr << "arr_sort: sorting algorithm failed" << std::endl;
            exit(1);
        }
    }

    if (task.config.is_present && task.count <= task.config.present_limit) {
        SortUtils::arr_print(task);
    }
}

void Sorts::insertion_sort(SortTask& task, int32_t p, int32_t r) {
    for (int32_t i = p + 1; i < r + 1; i++) {
        if (task.config.is_present && task.count <= task.config.present_limit) {
            SortUtils::arr_print(task);
        }

        // element to insert into left hand
        int32_t key = task.array[i];
        // left hand max bound
        int32_t j = i - 1;

        while (j >= p) {
            if (task.metric.comparison_count++; task.array[j] > key) {
                // shift array elements to the right
                task.array[j + 1] = task.array[j];
                task.metric.swap_count += 1;
                j -= 1;
            } else {
                break;
            }
        }
        // replace first from the left shifted element
        task.array[j + 1] = key;
        task.metric.swap_count += 1;
    }
}

int32_t Sorts::qs_partition(SortTask& task, int32_t p, int32_t r) {
    int32_t x = task.array[r];
    int32_t i = p - 1;

    for (int32_t j = p; j <= r - 1; j++) {
        if (task.metric.comparison_count++; task.array[j] <= x) {
            i++;
            task.metric.swap_count += 1;
            std::swap(task.array[i], task.array[j]);
        }
    }
    task.metric.swap_count += 1;
    std::swap(task.array[i + 1], task.array[r]);

    return i + 1;
}

void Sorts::quick_sort(SortTask& task, int32_t p, int32_t r) {
    if (p < r) {
        int32_t q = qs_partition(task, p, r);
        if (task.config.is_present && task.count <= task.config.present_limit) {
            SortUtils::arr_print(task);
        }
        quick_sort(task, p, q - 1);
        quick_sort(task, q + 1, r);
    }
}

void Sorts::hybrid_quick_sort(SortTask& task, int32_t p, int32_t r) {
    if (p < r) {
        if (r - p > task.config.hybrid_sort_threshold) {
            if (task.config.is_present && task.count <= task.config.present_limit) {
                SortUtils::arr_print(task);
            }
            int32_t q = qs_partition(task, p, r);
            hybrid_quick_sort(task, p, q - 1);
            hybrid_quick_sort(task, q + 1, r);
        } else {
            insertion_sort(task, p, r);
        }
    }
}

void Sorts::k_merge_sort(SortTask& task) {
    std::vector<std::vector<int32_t>> subvectors;
    std::vector<int32_t> candidate;

    for (auto num: task.array) {
        if (candidate.empty()) {
            candidate.push_back(num);
        } else {
            if (task.metric.comparison_count++; num < candidate.back()) {
                subvectors.push_back(candidate);
                candidate = {};
            }
            candidate.push_back(num);
        }
    }
    subvectors.push_back(candidate);

    auto result = kms_divide(task, subvectors, 0, (int32_t) subvectors.size() - 1);
    task.array = result;
}

std::vector<int32_t>
Sorts::kms_divide(SortTask& task, const std::vector<std::vector<int32_t>>& subvector, int32_t left, int32_t right) {
    if (left == right) {
        return subvector[left];
    }

    if (left + 1 == right) {
        return kms_merge(task, subvector[left], subvector[right]);
    }

    int32_t mid = (left + right) / 2;
    std::vector<int32_t> leftMerged = kms_divide(task, subvector, left, mid);
    std::vector<int32_t> rightMerged = kms_divide(task, subvector, mid + 1, right);

    return kms_merge(task, leftMerged, rightMerged);
}

std::vector<int32_t>
Sorts::kms_merge(SortTask& task, std::vector<int32_t> leftVector, std::vector<int32_t> rightVector) {
    std::vector<int32_t> result = {};

    int32_t l = 0;
    int32_t r = 0;
    auto ls = (int32_t) leftVector.size();
    auto rs = (int32_t) rightVector.size();

    while ((l < ls || r < rs)) {
        if (l == ls && r == rs) {
            break;
        } else if (l == ls && r < rs) {
            task.metric.swap_count += 1;
            result.push_back(rightVector[r]);
            r++;
        } else if (l < ls && r == rs) {
            task.metric.swap_count += 1;
            result.push_back(leftVector[l]);
            l++;
        } else {
            if (task.metric.comparison_count++; leftVector[l] < rightVector[r]) {
                task.metric.swap_count += 1;
                result.push_back(leftVector[l]);
                l++;
            } else {
                result.push_back(rightVector[r]);
                task.metric.swap_count += 1;
                r++;
            }
        }
    }
    SortUtils::arr_print(result);
    return result;
}

void Sorts::dual_quick_sort(SortTask& task, int32_t p, int32_t r) {
    if (p < r) {
        auto pivot = dual_qs_partition(task, p, r);
        if (task.config.is_present && task.count <= task.config.present_limit) {
            SortUtils::arr_print(task);
        }
        dual_quick_sort(task, p, pivot.first - 1);
        dual_quick_sort(task, pivot.first + 1, pivot.second - 1);
        dual_quick_sort(task, pivot.second + 1, r);
    }
}

std::pair<int32_t, int32_t>
Sorts::dual_qs_partition(SortTask& task, int32_t p, int32_t r) {
    std::pair<int32_t, int32_t> pivot = {};
    if (task.metric.comparison_count++; task.array[p] > task.array[r]) {
        task.metric.swap_count += 1;
        std::swap(task.array[p], task.array[r]);
    }

    int32_t j = p + 1;
    int32_t g = r - 1, k = p + 1, temp = task.array[p], q = task.array[r];
    while (k <= g) {

        if (task.metric.comparison_count++; task.array[k] < temp) {
            task.metric.swap_count += 1;
            std::swap(task.array[k], task.array[j]);
            j++;
        } else if (task.metric.comparison_count++; task.array[k] >= q) {
            while (task.metric.comparison_count++ && task.array[g] > q && k < g) {
                g--;
            }

            task.metric.swap_count += 1;
            std::swap(task.array[k], task.array[g]);
            g--;
            if (task.metric.comparison_count++; task.array[k] < temp) {
                task.metric.swap_count += 1;
                std::swap(task.array[k], task.array[j]);
                j++;
            }
        }
        k++;
    }
    j--;
    g++;

    task.metric.swap_count += 1;
    task.metric.swap_count += 1;
    std::swap(task.array[p], task.array[j]);
    std::swap(task.array[r], task.array[g]);

    pivot.first = j;
    pivot.second = g;

    return pivot;
}


void Sorts::ms_merge(SortTask& task, int32_t left, int32_t mid, int32_t right) {
    std::vector<int> leftArray;
    std::vector<int> rightArray;

    int subarrayL = mid - left + 1;
    int subarrayR = right - mid;

    for (int i = 0; i < subarrayL; i++) {
        task.metric.swap_count += 1;
        leftArray.push_back(task.array[left + i]);
    }
    for (int j = 0; j < subarrayR; j++) {
        task.metric.swap_count += 1;
        rightArray.push_back(task.array[mid + 1 + j]);
    }

    int li = 0, ri = 0;
    int merged_i = left;

    while (li < subarrayL && ri < subarrayR) {
        if (task.metric.comparison_count++; leftArray[li] <= rightArray[ri]) {
            task.metric.swap_count += 1;
            task.array[merged_i] = leftArray[li];
            li++;
        } else {
            task.metric.swap_count += 1;
            task.array[merged_i] = rightArray[ri];
            ri++;
        }
        merged_i++;
    }

    while (li < subarrayL) {
        task.metric.swap_count += 1;
        task.array[merged_i] = leftArray[li];
        li++;
        merged_i++;
    }
    while (ri < subarrayR) {
        task.metric.swap_count += 1;
        task.array[merged_i] = rightArray[ri];
        ri++;
        merged_i++;
    }
}

void Sorts::merge_sort(SortTask& task, int32_t p, int32_t r) {
    if (r > p) {
        int32_t mid = (p + r) / 2;

        merge_sort(task, p, mid);
        merge_sort(task, mid + 1, r);
        ms_merge(task, p, mid, r);

        if (task.config.is_present && task.count <= task.config.present_limit) {
            SortUtils::arr_print(task);
        }
    }
}
