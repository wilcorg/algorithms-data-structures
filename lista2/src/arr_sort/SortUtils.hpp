#ifndef ARR_SORT_SORTUTILS_HPP
#define ARR_SORT_SORTUTILS_HPP

#include "SortsCommon.hpp"
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <iomanip>
#include <iostream>


class SortUtils {
public:
    typedef boost::program_options::variables_map var_map;
    static var_map collect_arg(int32_t argc, const char **argv);
    static SortTask parse_arg(const var_map& vm);
    static void arr_print(const SortTask& task);
    static void arr_print(const std::vector<int>& task);
};

#endif//ARR_SORT_SORTUTILS_HPP
