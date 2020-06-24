#include "hx711.hpp"


void hx711::clock(){
  SCK.write(1);
  SCK.flush();
  hwlib::wait_us(5);
  SCK.write(0);
  SCK.flush();
  hwlib::wait_us(1);
}



//int bin_to_decimal(){


//}



void hx711::setup(){
  int array_bits [25];
  DT.refresh();
  while(DT.read() == 1){
    DT.refresh();
    //hwlib::cout << "test" << '\n';

  }

  for (int i=0; i<=24; i++){
    clock();
    DT.refresh();
    array_bits[i] = DT.read();

  }
  clock();
  //for (int j=0; j<=24; j++){
  //  hwlib::cout << array_bits[j] << hwlib::endl;
  //}
}



int * hx711::read(){
  static int array_bits [24];
  //uint32_t bits = 0;
  //uint32_t temp = 0;
  DT.refresh();
  while(DT.read() == 1){
    DT.refresh();

  }

  for (int i=0; i<24; i++){
    clock();
    DT.refresh();
    array_bits[i] = DT.read();
    //temp = DT.read();
    //temp = temp << (i-1);
    //bits = bits ^ temp;

  }
  clock();
  int result = 0;
  for(int k=0; k<24; k++){
    if (array_bits[k] == 1){
      int macht = pow((k+1), 2);
      result += (macht * 1);
    }

  }
  hwlib::cout << result << hwlib::endl;


  //uint24_t value = 0;
  //for (unsigned int i=0; i<=24; i++){
  //  uint24_t temp = array_bits[i];
  //  value = value << 1;
  //  value =
  //}
  return array_bits;
  //hwlib::cout << hwlib::hex(24) << hwlib::endl;

}


void hx711::test(){
  clock();
}
