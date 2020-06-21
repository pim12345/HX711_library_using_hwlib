#include "hwlib.hpp"
#include "../library_code/hx711.hpp"
#include <vector>
#include <array>
#include <iostream>
#include <ostream>


int main( void ) {
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d9 );
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d9 );

    auto weegschaal = hx711(SCK, DT);

}
