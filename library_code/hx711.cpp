#include "hx711.hpp"


void hx711::clock(){
  SCK.write(1);
  SCK.flush();
  hwlib::wait_us(5);
  SCK.write(0);
  SCK.flush();
  hwlib::wait_us(1);
}

int hx711::read_bit(uint32_t bit, int position){
  int x = 0;
  if (bit & (1 << position)){
    x =1;
  }
  return x;
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
  //if(temp_read<0){
  //  return 0;
  //}
  //if (temp_read > 0xFFFFFF){
  //  return 0xFFFFFF;
  //}
  //hwlib::cout << temp_read << hwlib::endl;

  hwlib::cout << "bit before: "<< hwlib::endl;
  for(int g=0; g<24; g++){
  hwlib::cout << array_bits[g];
  }
  hwlib::cout << hwlib::endl;

  //for converting binary to decimal number is used this tutorial for idea for code: https://nl.wikihow.com/Van-een-binair-getal-een-decimaal-getal-maken.
  int result = 0;
  bool is_negative = false;
  hwlib::cout << "bit pos: temp:  " << read_bit(temp_read, 23) << hwlib::endl;
  if (read_bit(temp_read, 23) == 1){
    is_negative = true;
    temp_read = ~temp_read; //invert all bits for conversion from two complement to decimal.
    //temp_read++;// add one to binary number for converting two complement to binary
  }
  hwlib::cout << "final ans1:       " << temp_read << hwlib::endl;



  for(int k=24; k>=0; k--){

    if(array_bits[k] == 1 && k == 0){
     int macht = pow(2, 24);
     result = result - (macht * 1);
     //hwlib::cout << "result- " << result << hwlib::endl;
    }
    if (array_bits[k] == 1){
      //hwlib::cout << "pow: " << (2) <<  "  " << (24-k-1) << hwlib::endl;
      int macht = pow(2, (24-k-1));
      //hwlib::cout << "macht:     " << macht << hwlib::endl;
      result += macht;
      //hwlib::cout << "result+ " << result << hwlib::endl;
    }
  }

  //for(int j=0; j<24; j++){
  //hwlib::cout << array_bits[j];
  //}
  //hwlib::cout << hwlib::endl;
  hwlib::cout << "result end :     " << result << hwlib::endl;
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
