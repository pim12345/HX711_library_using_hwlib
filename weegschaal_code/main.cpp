#include "hwlib.hpp"
#include "../library_code/hx711.hpp"
#include <vector>
#include <array>


int main( void ) {
    hwlib::wait_ms(2000);
    hwlib::cout << "begin" << '\n';
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );

    auto weegschaal = hx711(SCK, DT);

    weegschaal.setup();

    for (;;){
      weegschaal.read();
      hwlib::wait_ms(200);
    }
}
