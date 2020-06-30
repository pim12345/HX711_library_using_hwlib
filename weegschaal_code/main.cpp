#include "hwlib.hpp"
#include "../library_code/hx711.hpp"

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
    hwlib::wait_ms(2000);//wait for the console to get a connection from the arduino
    hwlib::cout << "begin" << '\n';

    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );

    auto weegschaal = hx711(SCK, DT, 1, 20.64282166);

    auto but_reset = hwlib::target::pin_in( hwlib::target::pins::d3 );
    auto but_switch_to_pounds = hwlib::target::pin_in( hwlib::target::pins::d4 );
    bool show_pounds = false; //change this to true if by start if the scale must show pounds instead of grams.

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
    weegschaal.calibration_set(); //set the scale to correct zero point
    for (;;){

    but_reset.refresh(); //refresh if button is pressed. If this function is not runned. The function will get the bufferd value of the button.
    //hwlib::cout << "button:  " << but_reset.read() << hwlib::endl;
    if (but_reset.read() == 0){ // if button is pressed. The scale wil reset itself. (set weight to zero.).
      display << '\f' << "Calibrating" << '\n' << "Please " << '\n' << "Wait...";
      oled.flush();
      weegschaal.calibration_set(); // reset current weight on scale to zero point.
    }


    //hwlib::cout << "pounds: "<< weegschaal.read_pounds() << hwlib::endl;
    but_switch_to_pounds.refresh();
    if (but_switch_to_pounds.read() == 0){
      if(show_pounds == false){
        show_pounds = true;
      }
      else if (show_pounds == true){
        show_pounds = false;
      }
    hwlib::wait_ms(50);
    }
    if (show_pounds == false){
      hwlib::cout << weegschaal.read() << hwlib::endl;
      display << '\f' << "Gewicht:" << '\n' << weegschaal.read_avg_10() << " g";
      oled.flush();
    }
    else if(show_pounds == true){
      display << '\f' << "Gewicht:" << '\n' << weegschaal.read_pounds() << " lb";
      oled.flush();
    }
    hwlib::wait_ms(20);

    }
}
