#include <type_traits>
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <catch2/catch.hpp>

#include <cstddef>
#include <string_view>

#include <eenum.hpp>

eenum(test, int, A = 1, B, C);

template<typename T>
concept assignable_to_underlying_type = requires(T e)
{
    e = std::underlying_type<T> {};
};

template<typename T>
concept underlying_type_assignable_to_enum = requires(std::underlying_type_t<T> e)
{
    e = T {};
};

TEST_CASE("eenum metadata generation", "[eenum]")
{
    REQUIRE(test_values().size() == 3);
    REQUIRE(eenum_::extract_name("A = 1") == "A");
}

TEST_CASE("eenum type safety", "[eenum]")
{
    REQUIRE(!assignable_to_underlying_type<test>);
    REQUIRE(!underlying_type_assignable_to_enum<test>);
}

TEST_CASE("eenum usage", "[eenum]")
{
    test t;
    t = test::A;

    std::string name = t;

    REQUIRE(t.to_string() == "A");
    REQUIRE(t == test::A);
    REQUIRE(name == "A");

    t = "B";
    REQUIRE(t.to_string() == "B");
    REQUIRE(t == test::B);

    t = test::C;
    REQUIRE(t.to_string() == "C");
    REQUIRE(t == test::C);
}