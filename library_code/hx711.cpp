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



int hx711::read(){
  uint32_t temp_read = 0;
  int array_bits [24] = {};
  //bool is_negative = false;
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
    //temp_read = DT.read();
    temp_read = temp_read << 1;
    temp_read = temp_read | DT.read();
    //temp = temp << (i-1);
    //bits = bits ^ temp;

  }
  clock();
  //clock();
  if(temp_read<0){
    return 0;
  }
  if (temp_read > 0xFFFFFF){
    return 0xFFFFFF;
  }
  hwlib::cout << temp_read << hwlib::endl;

  //for converting binary to decimal number is used this tutorial for idea for code: https://nl.wikihow.com/Van-een-binair-getal-een-decimaal-getal-maken.
  int result = 0;
  for(int k=0; k<24; k++){

    if(array_bits[k] == 1 && k < 8){
      int macht = pow((k+1), 2);
     result = result - (macht * 1);
     hwlib::cout << "result- " << result << hwlib::endl;
    }
    if (array_bits[k] == 1){
      int macht = pow((k+1), 2);
      result += (macht * 1);
      hwlib::cout << "result+ " << result << hwlib::endl;
    }
  }

  for(int j=0; j<24; j++){
  hwlib::cout << array_bits[j];
  }
  hwlib::cout << hwlib::endl;

  return result;


}


int hx711::read_avg_10(){
    int result1 = read();
    int result2 = read();
    int result3 = read();
    int result4 = read();
    int result5 = read();
    int result6 = read();
    int result7 = read();
    int result8 = read();
    int result9 = read();
    int result10 = read();
    int sum = result1 + result2 + result3 + result4 + result5 + result6 + result7 + result8 + result9 + result10;
    return (sum / 10);
}


int hx711::read_avg_100(){
  int result1 = read_avg_10();
  int result2 = read_avg_10();
  int result3 = read_avg_10();
  int result4 = read_avg_10();
  int result5 = read_avg_10();
  int result6 = read_avg_10();
  int result7 = read_avg_10();
  int result8 = read_avg_10();
  int result9 = read_avg_10();
  int result10 = read_avg_10();
  int sum = result1 + result2 + result3 + result4 + result5 + result6 + result7 + result8 + result9 + result10;
  return (sum / 100);

}
