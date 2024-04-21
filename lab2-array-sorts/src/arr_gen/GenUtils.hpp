#ifndef ARR_GEN_GENUTILS_HPP
#define ARR_GEN_GENUTILS_HPP

#include "GenCommon.hpp"

#include <boost/program_options.hpp>
#include <iostream>
#include <random>
#include <memory>

class GenUtils {
public:
    typedef boost::program_options::variables_map var_map;
    static var_map collect_arg(int32_t argc, const char **argv);
    static GenTask parse_arg(const var_map&);
    static std::unique_ptr<std::vector<int32_t>> generate_elements(const GenTask& task);
    static void serialize_array(const std::unique_ptr<std::vector<int32_t>>& array);
};

#endif //ARR_GEN_GENUTILS_HPP
