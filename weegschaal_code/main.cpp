#include "hwlib.hpp"
#include "../library_code/hx711.hpp"
//#include <array>

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
    hwlib::wait_ms(4000);
    hwlib::cout << "begin" << '\n';

    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );

    auto weegschaal = hx711(SCK, DT);

    auto but_reset = hwlib::target::pin_in( hwlib::target::pins::d3 );


    auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    auto oled = hwlib::glcd_oled_i2c_128x64_buffered( i2c_bus, 0x3c );
    oled.clear();

    auto font    = hwlib::font_default_16x16();
    auto display = hwlib::terminal_from( oled, font );

    display << '\f' << "Starting" << '\n';
    display << "Please" << '\n' <<  "Wait....";
    oled.flush();
    weegschaal.setup();
    //hwlib::cout << "frist read 10:     " << weegschaal.read_avg_10() << hwlib::endl;
    weegschaal.calibration_set();
    //hwlib::cout << "cal number: " << weegschaal.get_calibration_number() << hwlib::endl;
    //hwlib::cout << "read_10 second na cal number:     ";
    //hwlib::cout << weegschaal.read_avg_10() << hwlib::endl;

    //int weegschaal_resultaat;
    for (;;){
      //weegschaal_resultaat = weegschaal.read();
    //hwlib::cout << weegschaal.read_avg_10() << hwlib::endl;
    but_reset.refresh();
    //hwlib::cout << but_reset.read() << hwlib::endl;
    if (but_reset.read() == 0){ // if button is pressed. The scale wil reset itself. (set weight to zero.).
      weegschaal.calibration_set();
    }

    //oled.clear();
    hwlib::cout << weegschaal.read() << hwlib::endl;
    display << '\f' << "Gewicht:" << '\n' << weegschaal.read_avg_10() << " g";
    oled.flush();

    //hwlib::cout << "read_10:     ";
    //hwlib::cout << weegschaal.read_avg_10() << hwlib::endl;


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
