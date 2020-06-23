#include "../library_code/hx711.hpp"
#include <vector>
#include <array>


int main( void ) {
    hwlib::wait_ms(2000);
    hwlib::cout << "begin" << '\n';
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );

    auto weegschaal = hx711(SCK, DT);
    DT.refresh();
    while(DT.read() == 1){
      DT.refresh();
      hwlib::cout << "test" << '\n';
    }
    for (;;){
      SCK.write(0);
      SCK.flush();
      SCK.write(1);
      SCK.flush();
      hwlib::wait_us(5);
    }







}
