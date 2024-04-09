#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>

#include <iostream>
#include <random>
#include "common.hpp"
#include "Sorts.hpp"

std::pair<GenerateTask, SortTask> arg_parse(int32_t argc, char *argv[]) {
    namespace po = boost::program_options;

    GenerateTask generateTask = {};
    SortTask sortTask = {};
    po::options_description desc("benchmark options");
    po::variables_map vm;

    desc.add_options()
            ("help", "produce this message")
            ("mode,m", po::value<std::string>(), "value generation mode: rand, asc, desc")
            ("count,c", po::value<uint32_t>(), "number of values to generate")
            ("low,l", po::value<int32_t>()->default_value(0), "minimum value threshold")
            ("high,h", po::value<int32_t>()->default_value(100), "maximum value threshold")
            ("strategy", po::value<std::string>(), "array sorting strategy: insertion, quick, quick_hybrid")
            ("hybrid_threshold", po::value<std::int32_t>()->default_value(5), "quick sort into insertion sort transition value")
            ("k", po::value<uint32_t>()->default_value(1), "number of repeats");

    try {
        po::store(po::command_line_parser(argc, argv)
                          .options(desc).positional({}).run(),
                  vm);
        po::notify(vm);
    } catch (po::too_many_positional_options_error &error) {
        std::cerr << "benchmark: too many arguments. Run ./benchmark --help\n";
        exit(1);
    } catch (po::error_with_option_name &error) {
        std::cerr << "benchmark: invalid arguments. Run ./benchmark --help\n";
        exit(1);
    }

    if (vm.count("help") || argc == 1) {
        std::cout << desc << "\n";
        exit(0);
    }

    try {
        std::string mode = vm["mode"].as<std::string>();

        if (mode == "rand") {
            generateTask.mode = RANDOM;
        } else if (mode == "asc") {
            generateTask.mode = ASCENDING;
        } else if (mode == "desc") {
            generateTask.mode = DESCENDING;
        } else {
            throw boost::bad_any_cast();
        }
    } catch (boost::bad_any_cast &error) {
        std::cerr << "arr_gen: invalid arg for --mode\n";
        exit(1);
    }

    try {
        uint32_t count = vm["count"].as<uint32_t>();

        if (count > 0) {
            generateTask.count = count;
            sortTask.count = count;
        } else {
            throw boost::bad_any_cast();
        }
    } catch (boost::bad_any_cast &error) {
        std::cerr << "arr_gen: invalid arg for --count\n";
        exit(1);
    }

    try {
        generateTask.low = vm["low"].as<int32_t>();
    } catch (boost::bad_any_cast &error) {
        std::cerr << "arr_gen: invalid arg for --low\n";
        exit(1);
    }

    try {
        generateTask.high = vm["high"].as<int32_t>();
    } catch (boost::bad_any_cast &error) {
        std::cerr << "arr_gen: invalid arg for --high\n";
        exit(1);
    }

    if (generateTask.low > generateTask.high) {
        std::cerr << "arr_gen: high bound is less or equal than low bound\n";
        exit(1);
    }

    try {
        std::string strategy = vm["strategy"].as<std::string>();

        if (strategy == "insertion") {
            sortTask.strategy = INSERTION;
        } else if (strategy == "quick") {
            sortTask.strategy = QUICK;
        } else if (strategy == "quick_hybrid") {
            sortTask.strategy = QUICK_HYBRID;
        } else if (strategy == "kmerge") {
            sortTask.strategy = KMERGE;
        } else if (strategy == "dual_pivot") {
            sortTask.strategy = DUAL_QUICK;
        } else {
            throw boost::bad_any_cast();
        }
    } catch (boost::bad_any_cast &error) {
        std::cerr << "arr_sort: invalid arg for --mode\n";
        exit(1);
    }

    try {
        int32_t value = vm["hybrid_threshold"].as<int32_t>();

        if (value <= 0) {
            throw std::invalid_argument("");
        } else {
            sortTask.hybrid_sort_threshold = value;
        }
    } catch (boost::bad_any_cast &error) {
        std::cerr << "arr_sort: invalid arg for --hybrid_threshold\n";
        exit(1);
    } catch (std::invalid_argument &error) {
        std::cerr << "arr_sort: invalid arg for --hybrid_threshold\n";
        exit(1);
    }

    try {
        uint32_t k = vm["k"].as<uint32_t>();

        if (k > 0) {
            generateTask.k = k;
        } else {
            throw boost::bad_any_cast();
        }
    } catch (boost::bad_any_cast &error) {
        std::cerr << "benchmark: invalid arg for --k\n";
        exit(1);
    }
    return {generateTask, sortTask};
}

void generate_elements(const GenerateTask &generateTask, SortTask &sortTask) {
    sortTask.input = {};
    sortTask.input.reserve(generateTask.count);
    std::random_device rd;
    std::mt19937_64 gen64(rd());

    if (generateTask.low == generateTask.high) {
        for (int32_t i = 0; i < generateTask.count; i++) {
            sortTask.input.push_back(generateTask.low);
        }
    } else {
        for (int32_t i = 0; i < generateTask.count; i++) {
            sortTask.input.push_back(static_cast<int32_t>(gen64() % (generateTask.high - generateTask.low)) + generateTask.low);
        }
    }

    if (generateTask.mode == ASCENDING) {
        std::sort(sortTask.input.begin(), sortTask.input.end());
    } else if (generateTask.mode == DESCENDING) {
        std::sort(sortTask.input.begin(), sortTask.input.end(), std::greater{});
    }
}

int main(int argc, char *argv[]) {
    auto pair = arg_parse(argc, argv);
    GenerateTask generateTask = pair.first;
    SortTask sortTask = pair.second;
    uint64_t comparison_sum = 0;
    uint64_t swap_sum = 0;

    for (int i = 0; i < generateTask.k; i++) {
        generate_elements(generateTask, sortTask);
        SortMetric metric = Sorts::arr_sort(sortTask);
        comparison_sum += metric.comparison_count;
        swap_sum += metric.swap_count;
    }

    double comparison_avg = ((double) comparison_sum / generateTask.k);
    double swap_avg = ((double) swap_sum / generateTask.k);
    std::printf("%d;%.2f;%.2f;%.2f;%.2f\n", generateTask.count, comparison_avg, swap_avg, comparison_avg / generateTask.count, swap_avg / generateTask.count);

    return 0;
}
