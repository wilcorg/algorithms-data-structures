#include "BenchUtils.hpp"

BenchUtils::var_map BenchUtils::collect_arg(int32_t argc, const char **argv) {
    namespace po = boost::program_options;

    SortTask sortTask = {};
    po::options_description desc("benchmark options");
    po::variables_map vm;

    desc.add_options()
            ("help", "produce this message")
            ("mode", po::value<std::string>(), "value generation mode: rand, asc, desc")
            ("count", po::value<int32_t>(), "number of values to generate")
            ("low", po::value<int32_t>()->default_value(0), "minimum value threshold")
            ("high", po::value<int32_t>()->default_value(100), "maximum value threshold")
            ("strategy", po::value<std::string>(), "array sorting strategy: insertion, quick, quick_hybrid")
            ("present", po::bool_switch(), "present sorting algorithm")
            ("present_limit", po::value<int32_t>()->default_value(39), "max array size to present")
            ("hybrid_threshold", po::value<std::int32_t>()->default_value(5),
             "quick sort into insertion sort transition value")
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
    return vm;
}

BenchTask BenchUtils::parse_arg(const BenchUtils::var_map& vm) {
    auto genTask = GenUtils::parse_arg(vm);
    auto sortTask = SortUtils::parse_arg(vm);
    sortTask.count = genTask.count;

    uint32_t k;
    try {
        k = vm["k"].as<uint32_t>();

        if (k <= 0) {
            throw boost::bad_any_cast();
        }
    } catch (boost::bad_any_cast& error) {
        std::cerr << "arr_sort: invalid arg for --k\n";
        exit(1);
    }
    auto benchTask = BenchTask {genTask, sortTask, k};
    return benchTask;
}

