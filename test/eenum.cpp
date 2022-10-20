#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <catch2/catch.hpp>

#include <cstddef>
#include <string_view>

#include <eenum.hpp>

eenum(test, int, A = 1, B, C);

TEST_CASE("eenum metadata generation", "[eenum]")
{
    REQUIRE(test_values().size() == 3);
    REQUIRE(eenum_::extract_name("A = 1") == "A");
}

TEST_CASE("eenum usage", "[eenum]")
{
    REQUIRE(test_values().size() == 3);
    REQUIRE(eenum_::extract_name("A = 1") == "A");

    test t;
    t = test::data::A;

    test t1 {"A"};

    REQUIRE(t.to_string() == "A");
    REQUIRE(t1 == test::data::A);

    t = test::data::B;
    REQUIRE(t.to_string() == "B");

    t = test::data::C;
    REQUIRE(t.to_string() == "C");
}