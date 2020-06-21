#ifndef HX711_HPP
#define HX711_HPP
#include "hwlib.hpp"

class hx711 {
protected:
  hwlib::pin_out & SCK;
  hwlib::pin_in  & DT;

public:
  hx711(hwlib::pin_out & SCK, hwlib::pin_in  & DT ):
  SCK( SCK ),
  DT( DT )
  {}

    void read();
    

};





#endif // HX711_HPP
