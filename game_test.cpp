#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "game.hpp"


TEST_CASE("Check collisions 1") {
  REQUIRE(OBJECTS::Collision(FloatRect(100, 180, 16, 16), "Pk0rt") == false);
}
