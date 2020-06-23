#include "hwlib.hpp"
#include "../library_code/hx711.hpp"
#include <vector>
#include <array>


int main( void ) {
    hwlib::wait_ms(2000);
    hwlib::cout << "begin" << '\n';
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );

    //auto weegschaal = hx711(SCK, DT);
    DT.refresh();
    while(DT.read() == 1){
      DT.refresh();
      hwlib::cout << "test" << '\n';
    }
    //SCK.write(0);
    //SCK.flush();
    for (int i=0; i<=24; i++){
      SCK.write(1);
      SCK.flush();
      //hwlib::wait_us(4);
      SCK.write(0);
      SCK.flush();
      DT.refresh();
      hwlib::cout << "DT:    " << DT.read() << '\n';
      //SCK.write(1);
      //SCK.flush();
      //SCK.write(0);
      //SCK.flush();
      //DT.refresh();
      //hwlib::cout << "DT2:   " << DT.read() << '\n';
      //hwlib::wait_us(0.2);
      //DT.refresh();
      //hwlib::cout << "DT3:   " << DT.read() << '\n';

      //DT.refresh();
      //hwlib::cout << "DT4:   " << DT.read() << '\n';

    }
    SCK.write(1);
    SCK.flush();
    //hwlib::wait_us(4);
    //SCK.write(0);
    //SCK.flush();



    }
