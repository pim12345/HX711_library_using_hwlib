#ifndef HX711_HPP
#define HX711_HPP
#include "hwlib.hpp"
#include "array"

class hx711 {
protected:
  hwlib::pin_out & SCK;
  hwlib::pin_in  & DT;
  void clock();

public:
  hx711(hwlib::pin_out & SCK, hwlib::pin_in  & DT ):
  SCK( SCK ),
  DT( DT )
  {}

    void setup();
    void read();
    void test();

};





#endif // HX711_HPP
