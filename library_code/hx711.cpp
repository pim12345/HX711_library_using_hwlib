#include "hx711.hpp"


void clock(){
  SCK.write(1);
  SCK.flush();

  SCK.write(0);
  SCK.flush();
}


void hx711::setup(){
  DT.refresh();
  while(DT.read() == 1){
    DT.refresh();
    hwlib::cout << "test" << '\n';
  }
  //SCK.write(0);
  //SCK.flush();
  for (int i=0; i<=24; i++){
    SCK.write(1);
    SCK.flush();
    //hwlib::wait_us(4);
    SCK.write(0);
    SCK.flush();
    DT.refresh();
    hwlib::cout << "DT:    " << DT.read() << '\n';
    //SCK.write(1);
    //SCK.flush();
    //SCK.write(0);
    //SCK.flush();
    //DT.refresh();
    //hwlib::cout << "DT2:   " << DT.read() << '\n';
    //hwlib::wait_us(0.2);
    //DT.refresh();
    //hwlib::cout << "DT3:   " << DT.read() << '\n';

    //DT.refresh();
    //hwlib::cout << "DT4:   " << DT.read() << '\n';

  }
  SCK.write(1);
  SCK.flush();
  //hwlib::wait_us(4);
  //SCK.write(0);
  //SCK.flush();

}


void hx711::read(){


}
