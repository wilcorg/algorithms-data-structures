#include "SortUtils.hpp"

SortUtils::var_map SortUtils::collect_arg(int32_t argc, const char** argv) {
    namespace po = boost::program_options;

    po::options_description desc("arr_sort options");
    po::variables_map vm;

    desc.add_options()
            ("help", "produce this message")
            ("strategy", po::value<std::string>(), "array sorting strategy: insertion, quick, quick_hybrid, dp_quick, ms_merge, k_merge")
            ("present", po::bool_switch(), "present sorting algorithm")
            ("present_limit", po::value<int32_t>()->default_value(39), "max array size to present")
            ("hybrid_threshold", po::value<int32_t>()->default_value(5));

    try {
        po::store(po::command_line_parser(argc, argv)
                          .options(desc)
                          .positional({})
                          .run(),
                  vm);
        po::notify(vm);
    } catch (po::too_many_positional_options_error& error) {
        std::cerr << "arr_sort: too many arguments. Run ./arr_sort --help\n";
        exit(1);
    } catch (po::error_with_option_name& error) {
        std::cerr << "arr_sort: invalid arguments. Run ./arr_sort --help\n";
        exit(1);
    }

    if (vm.count("help") || argc == 1) {
        std::cout << desc << "\n";
        exit(0);
    }
    return vm;
}

SortTask SortUtils::parse_arg(const SortUtils::var_map& vm) {
    SortConfig config;
    try {
        auto strategy = vm["strategy"].as<std::string>();

        if (strategy == "insertion") {
            config.strategy = INSERTION;
        } else if (strategy == "quick") {
            config.strategy = QUICK;
        } else if (strategy == "quick_hybrid") {
            config.strategy = QUICK_HYBRID;
        } else if (strategy == "dp_quick") {
            config.strategy = DP_QUICK;
        } else if (strategy == "merge") {
            config.strategy = MERGE;
        } else if (strategy == "k_merge") {
            config.strategy = K_MERGE;
        } else {
            throw boost::bad_any_cast();
        }
    } catch (boost::bad_any_cast& error) {
        std::cerr << "arr_sort: invalid arg for --strategy\n";
        exit(1);
    }

    config.is_present = vm["present"].as<bool>();

    try {
        auto value = vm["hybrid_threshold"].as<int32_t>();

        if (value <= 0) {
            throw boost::bad_any_cast();
        } else {
            config.hybrid_sort_threshold = value;
        }
    } catch (boost::bad_any_cast& error) {
        std::cerr << "arr_sort: invalid arg for --hybrid_threshold\n";
        exit(1);
    }

    try {
        auto value = vm["present_limit"].as<int32_t>();

        if (value <= 0) {
            throw boost::bad_any_cast();
        } else {
            config.present_limit = value;
        }
    } catch (boost::bad_any_cast& error) {
        std::cerr << "arr_sort: invalid arg for --present_limit\n";
        exit(1);
    }

    // array's length & array itself parsing
    std::string raw_input;
    boost::char_separator<char> sep(" ");
    std::getline(std::cin, raw_input);
    typedef boost::tokenizer<boost::char_separator<char>> char_tokenizer;
    char_tokenizer tokens(raw_input, sep);

    int32_t count;
    try {
        if (int32_t value = std::stoi(*tokens.begin()); value > 0) {
            count = value;
        } else {
            std::cerr << "arr_sort: non-positive array element count number\n";
            exit(1);
        }
    } catch (std::invalid_argument& error) {
        std::cerr << "arr_sort: wrong token: " << *tokens.begin() << "\n";
        exit(1);
    }

    SortTask task = {.count = count, .config = config};

    if (std::distance(tokens.begin(), tokens.end()) != count + 1) {
        std::cerr << "arr_sort: array element count is different from provided array\n";
        exit(1);
    }

    for (char_tokenizer::iterator it = ++tokens.begin(); it != tokens.end(); ++it) {
        try {
            task.array.push_back(std::stoi(*it));
            task.max_el_width = std::max(task.max_el_width, (int32_t) (*it).length());
        } catch (std::invalid_argument& error) {
            std::cerr << "arr_sort: wrong token: " << *it << "\n";
            exit(1);
        }
    }

    return task;
}

void SortUtils::arr_print(const SortTask& task) {
    for (int32_t val: task.array) {
        std::cout << std::setw(task.max_el_width) << val << " ";
    }
    std::cout << std::endl;
}

void SortUtils::arr_print(const std::vector<int>& array) {
    for (auto val: array) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}
