//#include "hwlib.hpp"
#include "../library_code/hx711.hpp"
#include <vector>
#include <array>
//#include <iostream>
//#include <ostream>


int main( void ) {
    hwlib::cout << "begin" << '\n';
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );

    auto weegschaal = hx711(SCK, DT);
    for (;;){
    SCK.write(0);
    SCK.flush();
    hwlib::wait_ms(1);
    DT.refresh();
    hwlib::cout << DT.read() << '\n';
    while(DT.read() == 1){
      DT.refresh();
      hwlib::cout << DT.read() << '\n';
    }
      for (int i=0; i<25; i++){
        SCK.write(1);
        SCK.flush();
        SCK.write(0);
        SCK.flush();
        DT.refresh();
        hwlib::cout << DT.read() << '\n';
        //hwlib::wait_us();
        hwlib::wait_us(1);
      }
      SCK.write(1);
      SCK.flush();
      SCK.write(0);
      SCK.flush();
      //hwlib::
    }
    }
