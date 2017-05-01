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

  SECTION("Zero") {
    check(0, "0.0");
  }
}
