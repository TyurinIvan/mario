#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "game.hpp"


TEST_CASE("Check collisions 1") {
  REQUIRE(OBJECTS::Collision(FloatRect(100, 180, 16, 16), "Pk0rt") == false);
}

TEST_CASE("Check collisions 2") {
  REQUIRE(OBJECTS::Collision(FloatRect(100, 250, 16, 16), "Pk0rt") == true);
}

TEST_CASE("Check many collisions") {
  REQUIRE(OBJECTS::Collision(FloatRect(100, 180, 16, 16), "0rt") == false);
  REQUIRE(OBJECTS::Collision(FloatRect(150, 0, 7, 16), "0r")     == true);
  REQUIRE(OBJECTS::Collision(FloatRect(400, 200, 16, 3), "Pkt")  == false);
  REQUIRE(OBJECTS::Collision(FloatRect(10, 10, 16, 16), "Pk0rt") == true);
  REQUIRE(OBJECTS::Collision(FloatRect(40, 110, 16, 16), "Prt")  == false);
  REQUIRE(OBJECTS::Collision(FloatRect(120, 131, 10, 16), "Prt") == false);
  REQUIRE(OBJECTS::Collision(FloatRect(110, 10, 16, 100), "k")   == false);
}