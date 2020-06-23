#include "hx711.hpp"


void hx711::clock(){
  SCK.write(1);
  SCK.flush();
  hwlib::wait_us(5);
  SCK.write(0);
  SCK.flush();
  hwlib::wait_us(1);
}


void hx711::setup(){
  int array_bits [25];
  DT.refresh();
  while(DT.read() == 1){
    DT.refresh();
    hwlib::cout << "test" << '\n';

  }

  for (int i=0; i<=24; i++){
    clock();
    DT.refresh();
    array_bits[i] = DT.read();

  }
  clock();
  for (int j=0; j<=24; j++){
    hwlib::cout << array_bits[j] << hwlib::endl;
  }
}



void hx711::read(){
  int array_bits [25];
  DT.refresh();
  while(DT.read() == 1){
    DT.refresh();

  }

  for (int i=0; i<=24; i++){
    clock();
    DT.refresh();
    array_bits[i] = DT.read();

  }
  clock();
  for (int j=0; j<=24; j++){
    hwlib::cout << array_bits[j];
  }
  //hwlib::cout << hwlib::hex(24) << hwlib::endl;
  hwlib::cout << hwlib::endl;



}


void hx711::test(){
  clock();
}
