#ifndef BENCHMARK_BENCHUTILS_HPP
#define BENCHMARK_BENCHUTILS_HPP

#include "BenchCommon.hpp"
#include "include/SortUtils.hpp"
#include "include/GenUtils.hpp"
#include <boost/program_options.hpp>
#include <iostream>

class BenchUtils {
public:
    typedef boost::program_options::variables_map var_map;
    static var_map collect_arg(int32_t argc, const char **argv);
    static BenchTask parse_arg(const var_map& vm);
};

#endif //BENCHMARK_BENCHUTILS_HPP
