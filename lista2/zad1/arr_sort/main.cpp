#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>

#include <iostream>
#include <random>
#include <exception>
#include <optional>
#include "common.hpp"
#include "Sorts.hpp"

Task arg_parse(int32_t argc, char *argv[]);

Task arg_parse(int32_t argc, char *argv[]) {
    namespace po = boost::program_options;

    Task task = {};
    po::options_description desc("arr_sort options");
    po::variables_map vm;

    desc.add_options()
            ("help", "produce this message")
            ("strategy", po::value<std::string>(), "array sorting strategy: insertion, quick, quick_hybrid")
            ("hybrid_threshold", po::value<std::int32_t>()->default_value(5), "quick sort into insertion sort transition value");

    try {
        po::store(po::command_line_parser(argc, argv)
                          .options(desc).positional({}).run(),
                  vm);
        po::notify(vm);
    } catch (po::too_many_positional_options_error &error) {
        std::cerr << "arr_sort: too many arguments. Run ./arr_sort --help\n";
        exit(1);
    } catch (po::error_with_option_name &error) {
        std::cerr << "arr_sort: invalid arguments. Run ./arr_sort --help\n";
        exit(1);
    }

    if (vm.count("help") || argc == 1) {
        std::cout << desc << "\n";
        exit(0);
    }

    try {
        std::string strategy = vm["strategy"].as<std::string>();

        if (strategy == "insertion") {
            task.strategy = INSERTION;
        } else if (strategy == "quick") {
            task.strategy = QUICK;
        } else if (strategy == "quick_hybrid") {
            task.strategy = QUICK_HYBRID;
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
            task.hybrid_sort_threshold = value;
        }
    } catch (boost::bad_any_cast &error) {
        std::cerr << "arr_sort: invalid arg for --hybrid_threshold\n";
        exit(1);
    } catch (std::invalid_argument &error) {
        std::cerr << "arr_sort: invalid arg for --hybrid_threshold\n";
        exit(1);
    }

    std::string raw_input;
    boost::char_separator<char> sep(" ");
    std::getline(std::cin, raw_input);
    boost::tokenizer<boost::char_separator<char>> tokens(raw_input, sep);

    for (const auto &token: tokens) {
        try {
            int32_t value = std::stoi(token);
            if (task.count.has_value()) {
                task.input.push_back(value);
            } else {
                task.count = std::optional<int32_t>(value);
            }
        } catch (std::exception &error) {
            std::cerr << "arr_sort: invalid token: " << token << "\n";
            exit(1);
        }
    }

    return task;
}

int main(int argc, char *argv[]) {
    auto task = arg_parse(argc, argv);
    SortMetric metric = Sorts::arr_sort(task);

    if (metric.n < 40) {
        Sorts::arr_print(task.input);
    } else {
        std::cout << "Total comparison count: " << metric.comparison_count << std::endl;
        std::cout << "Total swap count: " << metric.swap_count << std::endl;
    }

    return 0;
}
