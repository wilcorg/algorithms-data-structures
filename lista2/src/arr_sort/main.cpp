#include "SortUtils.hpp"
#include "Sorts.hpp"


int main(int argc, const char **argv) {
    auto vm = SortUtils::collect_arg(argc, argv);
    auto task = SortUtils::parse_arg(vm);
    Sorts::arr_sort(task);

//    if (task.config.mode == BENCH) {
//        std::cout <<
//    }

//    if (metric.n < 40) {
//        Sorts::arr_print(task.input);
//    } else {
//        std::cout << "Total comparison count: " << metric.comparison_count << std::endl;
//        std::cout << "Total swap count: " << metric.swap_count << std::endl;
//    }

    return 0;
}
