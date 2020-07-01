#include "hwlib.hpp"
#include "../library_code/hx711.hpp"


int main( void ) {
    hwlib::wait_ms(2000);//wait for the console to get a connection from the arduino
    hwlib::cout << "begin" << '\n';

    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );

    auto weegschaal = hx711(SCK, DT, 1, 20.64282166);

    auto but_reset = hwlib::target::pin_in( hwlib::target::pins::d3 );
    auto but_switch_to_power = hwlib::target::pin_in( hwlib::target::pins::d4 );

    bool power = true; //change this to false to start the hx711 chip to a power down state after the calibration process stated by setup() and calibration_set() and

    auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    auto oled = hwlib::glcd_oled_i2c_128x64_buffered( i2c_bus, 0x3c );
    oled.clear(); // clear the oled screen because it will otherwise give a rondom pattron on the screen.

    auto font    = hwlib::font_default_16x16();
    auto display = hwlib::terminal_from( oled, font );

    display << '\f' << "Starting" << '\n';
    display << "Please" << '\n' <<  "Wait....";
    oled.flush();

    weegschaal.setup();
    weegschaal.calibration_set(); //set the scale to correct zero point

    for (;;){
    but_reset.refresh(); //refresh if button is pressed. If this function is not runned. The function will get the bufferd value of the button.
    if (but_reset.read() == 0){ // if button is pressed. The scale wil reset itself. (set weight to zero.).
      display << '\f' << "Calibrating" << '\n' << "Please " << '\n' << "Wait...";
      oled.flush();
      weegschaal.calibration_set(); // reset current weight on scale to zero point.
    }


    //hwlib::cout << "pounds: "<< weegschaal.read_pounds() << hwlib::endl;
    but_switch_to_power.refresh();
    if (but_switch_to_power.read() == 0){
      if(power == false){
        power = true;
      }
      else if (power == true){
        power = false;
      }
    hwlib::wait_ms(50);
    }
    if (power == true){
      weegschaal.power_up();
      hwlib::cout << weegschaal.read() << hwlib::endl;
      display << '\f' << "Gewicht:" << '\n' << weegschaal.read_avg_10() << " g" << '\n';
      display << weegschaal.read_pounds() << " lb";
      oled.flush();
    }
    else if(power == false){
      display << '\f' << "Power" << '\n' << "Down";
      oled.flush();
      weegschaal.power_down();
    }
    hwlib::wait_ms(20);

    }
}
