#include "hwlib.hpp"
#include "../library_code/hx711.hpp"
#include <vector>
#include <array>

//void display(auto oled, int result){
//  oled.clear();
//  auto font    = hwlib::font_default_8x8();
//  auto display = hwlib::terminal_from( oled, font );
//
// display << result << '\n';
//
//
//}

int main( void ) {
    hwlib::wait_ms(2000);
    hwlib::cout << "begin" << '\n';
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );

    auto weegschaal = hx711(SCK, DT);

    //auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    //auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

    //auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

    //auto oled = hwlib::glcd_oled( i2c_bus, 0x3c );
    //oled.clear();



    weegschaal.setup();
    //int weegschaal_resultaat;
    for (;;){
      //weegschaal_resultaat = weegschaal.read();
    //hwlib::cout << weegschaal.read_avg_10() << hwlib::endl;
    weegschaal.read_avg_10();


    //oled.clear();
      //auto font    = hwlib::font_default_8x8();
      //auto display = hwlib::terminal_from( oled, font );

     //display << result << '\n';

    //display(oled, result);



        //for (int j=0; j<=24; j++){
      //  hwlib::cout << weegschaal_resultaat[j];
      //}
      //hwlib::cout << hwlib::endl;
      //hwlib::wait_ms(200);
    }
}
