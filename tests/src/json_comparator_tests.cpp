// Copyright 2013 Daniel Parker
// Distributed under Boost license

#include <jsoncons/json.hpp>
#include <jsoncons/json_encoder.hpp>
#include <catch/catch.hpp>
#include <sstream>
#include <vector>
#include <utility>
#include <ctime>

using namespace jsoncons;

TEST_CASE("test_object_equals_basic")
{
    json o1;
    o1["a"] = 1;
    o1["b"] = 2;
    o1["c"] = 3;

    json o2;
    o2["c"] = 3;
    o2["a"] = 1;
    o2["b"] = 2;

    CHECK(o1 == o2);
    CHECK(o2 == o1);
    CHECK_FALSE((o1 != o2));
    CHECK_FALSE((o2 != o1));
}

TEST_CASE("test_object_equals_diff_vals")
{
    json o1;
    o1["a"] = 1;
    o1["b"] = 2;
    o1["c"] = 3;

    json o2;
    o2["a"] = 1;
    o2["b"] = 4;
    o2["c"] = 3;

    CHECK_FALSE((o1 == o2));
    CHECK_FALSE((o2 == o1));
    CHECK(o1 != o2);
    CHECK(o2 != o1);
}

TEST_CASE("test_object_equals_diff_el_names")
{
    json o1;
    o1["a"] = 1;
    o1["b"] = 2;
    o1["c"] = 3;

    json o2;
    o2["d"] = 1;
    o2["e"] = 2;
    o2["f"] = 3;

    CHECK_FALSE((o1 == o2));
    CHECK_FALSE((o2 == o1));
    CHECK(o1 != o2);
    CHECK(o2 != o1);
}

TEST_CASE("test_object_equals_diff_sizes")
{
    json o1;
    o1["a"] = 1;
    o1["b"] = 2;
    o1["c"] = 3;

    json o2;
    o2["a"] = 1;
    o2["b"] = 2;

    CHECK_FALSE((o1 == o2));
    CHECK_FALSE((o2 == o1));
    CHECK(o1 != o2);
    CHECK(o2 != o1);
}

TEST_CASE("test_object_equals_subtle_offsets")
{
    json o1;
    o1["a"] = 1;
    o1["b"] = 1;

    json o2;
    o2["b"] = 1;
    o2["c"] = 1;

    CHECK_FALSE((o1 == o2));
    CHECK_FALSE((o2 == o1));
    CHECK(o1 != o2);
    CHECK(o2 != o1);
}

TEST_CASE("test_object_equals_empty_objects")
{
    json def_constructed_1;
    json def_constructed_2;
    json parsed_1 = json::parse("{}");
    json parsed_2 = json::parse("{}");
    json type_constructed_1 = json(json_object_arg);
    json type_constructed_2 = json(json_object_arg);

    CHECK(def_constructed_1 == def_constructed_1);
    CHECK(parsed_1 == parsed_2);
    CHECK(type_constructed_1 == type_constructed_2);

    CHECK(def_constructed_1 == parsed_1);
    CHECK(def_constructed_1 == type_constructed_1);
    CHECK(parsed_1 == type_constructed_1);
}

TEST_CASE("test_object_equals_empty_arrays")
{
    json parsed_1 = json::parse("[]");
    json parsed_2 = json::parse("[]");
    json type_constructed_1(json_array_arg);
    json type_constructed_2(json_array_arg);

    CHECK(parsed_1 == parsed_2);
    CHECK(type_constructed_1 == type_constructed_2);

    CHECK(parsed_1 == type_constructed_1);
}

TEST_CASE("test_empty_object_equal")
{
    CHECK(json() == json(json_object_arg));
    CHECK(json(json_object_arg) == json());
}

TEST_CASE("test_string_not_equals_empty_object")
{
    json o1("42");
    json o2;

    CHECK(o1 != o2);
    CHECK(o2 != o1);
}

TEST_CASE("test_byte_strings_equal")
{
    json o1(byte_string({'1','2','3','4','5','6','7','8','9'}));
    json o2(byte_string{'1','2','3','4','5','6','7','8','9'});
    json o3(byte_string{'1','2','3','4','5','6','7','8'});

    CHECK(o1 == o2);
    CHECK(o2 == o1);
    CHECK(o3 != o1);
    CHECK(o2 != o3);
}

TEST_CASE("json json_pointer_arg")
{
    json val1 = json::parse(R"(
{ "names" : [ "a", "b", "c", "d" ] }
    )");

    json val2 = json::parse(R"(
{ "names" : [ "a", "b" ] }
    )");

    SECTION("test ==")
    {
        json lhs(json_pointer_arg, &val1);

        json rhs(json_pointer_arg, &val1);

        CHECK(lhs == rhs);
        CHECK(lhs == val1);
        CHECK(lhs != val2);
        CHECK(val2 != rhs);
    }
    SECTION("test <")
    {
        json lhs(json_pointer_arg, &val1);

        json rhs(json_pointer_arg, &val1);

        CHECK_FALSE(lhs < rhs);
        CHECK_FALSE(rhs < lhs);
        CHECK(val2 < lhs);
        CHECK_FALSE(lhs < val2);
        CHECK(lhs > val2);
        CHECK_FALSE(val2 > lhs);
    }
}
