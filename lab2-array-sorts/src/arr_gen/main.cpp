#include "GenUtils.hpp"

int main(int argc, const char **argv) {
    const auto vm = GenUtils::collect_arg(argc, argv);
    const auto task = GenUtils::parse_arg(vm);
    const auto array = GenUtils::generate_elements(task);
    GenUtils::serialize_array(array);
    return 0;
}
