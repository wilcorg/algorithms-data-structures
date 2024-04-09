#include <boost/program_options.hpp>

#include <iostream>
#include <vector>
#include <random>

enum Mode {
    RANDOM, ASCENDING, DESCENDING
};

typedef struct {
    Mode mode;
    uint32_t count;
    int32_t low;
    int32_t high;
} Task;

Task arg_parse(int32_t argc, char *argv[]);

void generate_elements(const Task &task);

void print_elements(uint32_t count, const std::vector<int32_t> &array);

Task arg_parse(int32_t argc, char *argv[]) {
    namespace po = boost::program_options;

    Task task = {};
    po::options_description desc("arr_gen options");
    po::variables_map vm;

    desc.add_options()
            ("help", "produce help message")
            ("mode,m", po::value<std::string>(), "value generation mode: rand, asc, desc")
            ("count,c", po::value<uint32_t>(), "number of values to generate")
            ("low,l", po::value<int32_t>()->default_value(0), "minimum value threshold")
            ("high,h", po::value<int32_t>()->default_value(100), "maximum value threshold");
    try {
        po::store(po::command_line_parser(argc, argv)
                          .options(desc).positional({}).run(),
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
    try {
        std::string mode = vm["mode"].as<std::string>();

        if (mode == "rand") {
            task.mode = RANDOM;
        } else if (mode == "asc") {
            task.mode = ASCENDING;
        } else if (mode == "desc") {
            task.mode = DESCENDING;
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

void generate_elements(const Task &task) {
    std::vector<int32_t> array = {};
    array.reserve(task.count);
    std::random_device rd;
    std::mt19937_64 gen64(rd());

    if (task.low == task.high) {
        for (int32_t i = 0; i < task.count; i++) {
            array.push_back(task.low);
        }
    } else {
        for (int32_t i = 0; i < task.count; i++) {
            array.push_back(static_cast<int32_t>(gen64() % (task.high - task.low)) + task.low);
        }
    }

    if (task.mode == ASCENDING) {
        std::sort(array.begin(), array.end());
    } else if (task.mode == DESCENDING) {
        std::sort(array.begin(), array.end(), std::greater{});
    }

    print_elements(task.count, array);
}

void print_elements(uint32_t count, const std::vector<int32_t> &array) {
    std::cout << count << " ";
    for (auto el: array) {
        std::cout << el << " ";
    }
}

int main(int argc, char *argv[]) {
    auto task = arg_parse(argc, argv);
    generate_elements(task);
    return 0;
}
