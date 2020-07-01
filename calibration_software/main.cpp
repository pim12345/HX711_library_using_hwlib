#include "hwlib.hpp"
#include "../library_code/hx711.hpp"

int char_input_to_int(char input){
  if (input == 'a'){
    return 1000;
  }
  else if(input == 'b'){
    return 2000;
  }
  else if(input == 'c'){
    return 3000;
  }
  else if(input == 'd'){
    return 4000;
  }
  else if(input == 'e'){
    return 5000;
  }
  else if(input == 'f'){
    return 6000;
  }
  else if(input == 'g'){
    return 7000;
  }
  else if(input == 'h'){
    return 8000;
  }
  else if(input == 'i'){
    return 9000;
  }
  else if(input == 'j'){
    return 10000;
  }
  return 0;
}

int main( void ) {
    hwlib::wait_ms(2000);
    hwlib::cout << "Calibration software starting..." << hwlib::endl;
    hwlib::cout << "Please put no weight on the scale." << hwlib::endl;

    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );

    auto weegschaal = hx711(SCK, DT, 1);

    weegschaal.setup();

    weegschaal.calibration_set();

    char ans;
    hwlib::cout << "Please put a known weight on the scale. If known weight is placed on the scale, type: y in the console." << hwlib::endl;
    hwlib::cin >> ans;
    hwlib::cout << ans << hwlib::endl;
    while (ans != 'y'){
      hwlib::cin >> ans;
    }

    int weight_object = weegschaal.read_avg_100();
    hwlib::cout << "Press a for 1 kg  or 1000 g"<< hwlib::endl;
    hwlib::cout << "Press b for 2 kg  or 2000 g"<< hwlib::endl;
    hwlib::cout << "Press c for 3 kg  or 3000 g"<< hwlib::endl;
    hwlib::cout << "Press d for 4 kg  or 4000 g"<< hwlib::endl;
    hwlib::cout << "Press e for 5 kg  or 5000 g"<< hwlib::endl;
    hwlib::cout << "Press f for 6 kg  or 6000 g"<< hwlib::endl;
    hwlib::cout << "Press g for 7 kg  or 7000 g"<< hwlib::endl;
    hwlib::cout << "Press h for 8 kg  or 8000 g"<< hwlib::endl;
    hwlib::cout << "Press i for 9 kg  or 9000 g"<< hwlib::endl;
    hwlib::cout << "Press j for 10 kg or 10000 g"<< hwlib::endl;
    hwlib::cout << "Please input known weight: ";

    char known_weight_char;
    hwlib::cin >> known_weight_char;
    hwlib::cout << known_weight_char << hwlib::endl;

    int known_weight_grams = char_input_to_int(known_weight_char);
    int calibration_weight = (weight_object / known_weight_grams);

    if (calibration_weight <= 0){
      hwlib::cout << "Somthing did go wrong. Please try again." << hwlib::endl;
    }
    else{
      hwlib::cout << "Calibration weight number is: " << calibration_weight << hwlib::endl;
      hwlib::cout << "Please put this number in the constructor of the hx711 object."<< hwlib::endl;
    }
}
