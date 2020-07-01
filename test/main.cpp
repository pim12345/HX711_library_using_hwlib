#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../library_code/hx711.hpp"
#include "hwlib.hpp"



TEST_CASE("gain check"){
  //auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
  //auto DT = hwlib::target::pin_in( hwlib::pins::d6 );
  auto weegschaal = hx711(SCK, DT, 1, 20.64282166);
  int gain = hx711::get_gain();
  REQUIRE( gain == 2 );
}
