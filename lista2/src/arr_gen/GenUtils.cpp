#include "GenUtils.hpp"


GenUtils::var_map GenUtils::collect_arg(int32_t argc, const char **argv) {
    namespace po = boost::program_options;

    po::options_description desc("arr_gen options");
    po::variables_map vm;

    desc.add_options()
            ("help", "produce this message")
            ("mode", po::value<std::string>(), "value generation mode: rand, asc, desc")
            ("count", po::value<int32_t>(), "number of values to generate")
            ("low", po::value<int32_t>()->default_value(0), "minimum value threshold")
            ("high", po::value<int32_t>()->default_value(100), "maximum value threshold");

    try {
        po::store(po::command_line_parser(argc, argv)
                          .options(desc)
                          .positional({})
                          .run(),
                  vm);
        po::notify(vm);
    } catch (po::too_many_positional_options_error &error) {
        std::cerr << "arr_gen: too many arguments. Run ./arr_gen --help\n";
        exit(1);
    } catch (po::error_with_option_name &error) {
        std::cerr << "arr_gen: invalid arguments. Run ./arr_gen --help\n";
        exit(1);
    }

    if (vm.count("help") || argc == 1) {
        std::cout << desc << "\n";
        exit(0);
    }
    return vm;
}

GenTask GenUtils::parse_arg(const var_map& vm) {
    GenTask task = {};

    try {
        std::string mode = vm["mode"].as<std::string>();

        if (mode == "rand") {
            task.strategy = RANDOM;
        } else if (mode == "asc") {
            task.strategy = ASCENDING;
        } else if (mode == "desc") {
            task.strategy = DESCENDING;
        } else {
            throw boost::bad_any_cast();
        }
    } catch (boost::bad_any_cast &error) {
        std::cerr << "arr_gen: invalid arg for --mode\n";
        exit(1);
    }

    try {
        int32_t count = vm["count"].as<int32_t>();

        if (count > 0) {
            task.count = count;
        } else {
            throw boost::bad_any_cast();
        }
    } catch (boost::bad_any_cast &error) {
        std::cerr << "arr_gen: invalid arg for --count\n";
        exit(1);
    }

    try {
        task.low = vm["low"].as<int32_t>();
    } catch (boost::bad_any_cast &error) {
        std::cerr << "arr_gen: invalid arg for --low\n";
        exit(1);
    }

    try {
        task.high = vm["high"].as<int32_t>();
    } catch (boost::bad_any_cast &error) {
        std::cerr << "arr_gen: invalid arg for --high\n";
        exit(1);
    }

    if (task.low > task.high) {
        std::cerr << "arr_gen: high bound is less or equal than low bound\n";
        exit(1);
    }

    return task;
}

std::unique_ptr<std::vector<int32_t>> GenUtils::generate_elements(const GenTask &task) {
    std::vector<int32_t> array;
    array.reserve(task.count);
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int32_t i = 0; i < task.count; i++) {
        array.push_back(static_cast<int32_t>(gen() % (task.high - task.low + 1)) + task.low);
    }

    switch (task.strategy) {
        case RANDOM:
            break;
        case ASCENDING:
            std::sort(array.begin(), array.end());
            break;
        case DESCENDING:
            std::sort(array.begin(), array.end(), std::greater{});
            break;
    }

    return std::make_unique<std::vector<int32_t>>(array);
}

void GenUtils::serialize_array(const std::unique_ptr<std::vector<int32_t>>& array) {
    std::cout << array->size() << " ";
    for (auto el: *array) {
        std::cout << el << " ";
    }
}
