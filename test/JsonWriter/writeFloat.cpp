// Copyright Benoit Blanchon 2014-2017
// MIT License
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!

#include <catch.hpp>
#include <limits>
#include <string>

#include <ArduinoJson/Serialization/JsonWriter.hpp>
#include <ArduinoJson/Serialization/StaticStringBuilder.hpp>

using namespace ArduinoJson::Internals;

void check(double input, const std::string& expected) {
  char output[1024];
  StaticStringBuilder sb(output, sizeof(output));
  JsonWriter<StaticStringBuilder> writer(sb);
  writer.writeFloat(input);
  REQUIRE(output == expected);
  REQUIRE(writer.bytesWritten() == expected.size());
}

TEST_CASE("JsonWriter::writeFloat()") {
  SECTION("NaN") {
    double nan = std::numeric_limits<double>::signaling_NaN();
    check(nan, "NaN");
  }

  SECTION("Infinity") {
    double inf = std::numeric_limits<double>::infinity();
    check(inf, "Infinity");
    check(-inf, "-Infinity");
  }

  SECTION("One decimal place") {
    check(0.0, "0.0");
    check(0.1, "0.1");
    check(0.9, "0.9");

    check(9.0, "9.0");
    check(9.1, "9.1");
    check(9.9, "9.9");
  }
}
