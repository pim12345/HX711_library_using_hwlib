#include "../library_code/hx711.hpp"
#include "hwlib.hpp"

int main( void ){
  hwlib::wait_ms(2000);
  int error = 0;
  auto SCK = hwlib::target::pin_out( hwlib::target::pins::d10 );
  auto DT  = hwlib::target::pin_in(  hwlib::target::pins::d6 );
  auto weegschaal = hx711(SCK, DT, 1, 20.64282166);

  int gain = weegschaal.get_gain();
  if (gain != 1){
    error++;
    hwlib::cout << "gain error 1" << hwlib::endl;
  }

  auto weegschaal2 = hx711(SCK, DT, 5, 20.64282166);
  weegschaal2.setup();
  gain = weegschaal2.get_gain();
  if (gain != 3){
    error++;
    hwlib::cout << "gain error 5" << hwlib::endl;
  }

  auto weegschaal3 = hx711(SCK, DT, -1, 20.64282166);
  weegschaal3.setup();
  gain = weegschaal3.get_gain();
  if (gain != 1){
    error++;
    hwlib::cout << "gain error -1" << hwlib::endl;
  }

  auto weegschaal4 = hx711(SCK, DT, 1, 20.64282166);
  if (weegschaal4.get_calibration_zero_point_number() != 0 ){
    error++;
    hwlib::cout << "error calibration zero point not zero. calibration is not set";
    hwlib::cout << weegschaal4.get_calibration_zero_point_number() << hwlib::endl;
  }


  auto weegschaal5 = hx711(SCK, DT, 1, 20.64282166);
  weegschaal5.calibration_set();
  if (weegschaal5.get_calibration_zero_point_number() == 0 ){
    error++;
    hwlib::cout << "error calibration zero point is zero. while it must be set. calibration is not set";
    hwlib::cout << weegschaal5.get_calibration_zero_point_number() << hwlib::endl;
  }

  hwlib::cout << "error total: " << error << hwlib::endl;
}
