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
  }

  for (int i=0; i<=24; i++){
    clock();
    DT.refresh();
    array_bits[i] = DT.read();

  }
  clock();
  
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
  //for (int j=0; j<=24; j++){
  //  hwlib::cout << array_bits[j] << hwlib::endl;
  //}
}



int hx711::read_no_calibration(){
  //uint32_t temp_read = 0;
  int array_bits [24] = {};
  int result = 0;

  DT.refresh();
  while(DT.read() == 1){
    DT.refresh();
  }


  for (int i=0; i<24; i++){
    clock();
    DT.refresh();
    array_bits[i] = DT.read();

    //temp_read = temp_read << 1;
    //temp_read = temp_read | DT.read();
  }

  clock();

  //if(temp_read<0){
  //  return 0;
  //}
  //if (temp_read > 0xFFFFFF){
  //  return 0xFFFFFF;
  //}

  //for converting binary to decimal number is used this tutorial for idea for code: https://nl.wikihow.com/Van-een-binair-getal-een-decimaal-getal-maken.

  for(int k=24; k>=0; k--){

    if(array_bits[k] == 1 && k == 0){ // 24th bit is 1 the read is negative. I used this site for inspiration: https://www.youtube.com/watch?v=ykkFk-2y6SE .
      int macht = pow(2, 24);
      result = result - (macht * 1);
    }
    if (array_bits[k] == 1){
      int macht = pow(2, (24-k-1));
      result += macht;
    }
  }
  //hwlib::cout << "result end :     " << result << hwlib::endl;
  //hwlib::cout << "cal number read function: calibration_number:  " << calibration_number << hwlib::endl;
  //hwlib::cout << "cal number read function: result:     " << result << hwlib::endl;
  //result = (result / 19122.10938);
  return result;


}

int hx711::read(){
  int result = read_no_calibration();
  result += calibration_number;
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
  return (sum / 10);

}


void hx711::calibration_set(){
  int result1 = read_no_calibration();
  int result2 = read_no_calibration();
  int result3 = read_no_calibration();
  int result4 = read_no_calibration();
  int result5 = read_no_calibration();
  int result6 = read_no_calibration();
  int result7 = read_no_calibration();
  int result8 = read_no_calibration();
  int result9 = read_no_calibration();
  int result10 = read_no_calibration();
  int sum = result1 + result2 + result3 + result4 + result5 + result6 + result7 + result8 + result9 + result10;
  int avg_no_calibration = (sum / 10);
  avg_no_calibration *= -1; // will make the number positive.
  calibration_number = avg_no_calibration; // The avarege of hunderd read will with no weight on the scale will set the 0 point of the scale.
}

int hx711::get_calibration_number(){
  return calibration_number;
}
