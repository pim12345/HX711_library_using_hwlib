#include "hwlib.hpp"
#include "../library_code/hx711.hpp"
#include <array>
#include <string>

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
    hwlib::cout << "Calibration software starting..." << hwlib::endl;
    hwlib::cout << "Please put no weight on the scale." << hwlib::endl;

    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );

    auto weegschaal = hx711(SCK, DT);

    auto but_reset = hwlib::target::pin_in( hwlib::target::pins::d3 );

    weegschaal.setup();

    weegschaal.calibration_set();

    char ans;
    hwlib::cout << "Please put a known weight on the scale. If known weight is placed on the scale, type: yes in the console." << hwlib::endl;
    hwlib::cin >> ans;

    while (ans != 'y' || ans != 'Y'){
      hwlib::cin >> ans;
    }

    int weight_object = weegschaal.read_avg_100();
    hwlib::cout << "Please input known weight in grams: ";
    char known_weight_grams;
    hwlib::cin >>known_weight_grams;

    int calibration_weight = (weight_object / known_weight_grams);

    hwlib::cout << "Calibration weight number is: " << calibration_weight << hwlib::endl;
    hwlib::cout << "Please put this number in the constructor of the hwlib object.";
}
