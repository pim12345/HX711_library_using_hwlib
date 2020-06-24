#ifndef HX711_HPP
#define HX711_HPP
#include "hwlib.hpp"
#include <array>
#include <cmath>
class hx711 {
protected:
  hwlib::pin_out & SCK;
  hwlib::pin_in  & DT;
  void clock();
  int bin_to_decimal();

public:
  hx711(hwlib::pin_out & SCK, hwlib::pin_in  & DT ):
  SCK( SCK ),
  DT( DT )
  {}

    void setup();
    int * read();
    void test();

};





#endif // HX711_HPP
