#include "include/Sorts.hpp"
#include "include/GenUtils.hpp"
#include "BenchUtils.hpp"
#include <random>


int main(int argc, const char *argv[]) {
    auto benchTask = BenchUtils::parse_arg(BenchUtils::collect_arg(argc, argv));

    for (int i = 0; i < benchTask.k; i++) {
        benchTask.sortTask.array = *GenUtils::generate_elements(benchTask.genTask).release();
        Sorts::arr_sort(benchTask.sortTask);
    }

    double comparison_avg = ((double) benchTask.sortTask.metric.comparison_count / benchTask.k);
    double swap_avg = ((double) benchTask.sortTask.metric.swap_count / benchTask.k);
    std::printf("%d;%.2f;%.2f;%.2f;%.2f\n", benchTask.genTask.count, comparison_avg, swap_avg,
                comparison_avg / benchTask.genTask.count, swap_avg / benchTask.genTask.count);

    return 0;
}
