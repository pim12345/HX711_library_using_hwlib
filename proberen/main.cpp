#include "../library_code/hx711.hpp"
//#include <vector>
#include <array>


int main( void ) {
  namespace target = hwlib::target;
  hwlib::wait_ms(2000);

   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );

   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

   i2c_bus.write_bit( 0x53 );



}
