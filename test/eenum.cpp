#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <catch2/catch.hpp>

#include <cstddef>
#include <string_view>

#include <eenum.hpp>

eenum(test, int, A = 1, B, C);

TEST_CASE("eenum basic usage", "[eenum]")
{
    REQUIRE(test_values().size() == 3);
    REQUIRE(eenum_::extract_name("A = 1") == "A");
    REQUIRE(test_to_string(test::A) == "A");
    REQUIRE(string_to_test("A") == test::A);
}