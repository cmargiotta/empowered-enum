#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <catch2/catch.hpp>

#include <cstddef>
#include <string_view>

#include <eenum.hpp>

eenum(cazzo, int, A = 1, B, C);

TEST_CASE("eenum basic usage", "[eenum]")
{
    cazzo::A;
}