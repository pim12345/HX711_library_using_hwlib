#include "hx711.hpp"
/// @file



void hx711::power_down(){
  SCK.write(1);
  SCK.flush();
}



void hx711::power_up(){
  SCK.write(0);
  SCK.flush();
}



void hx711::clock(){
  SCK.write(1);
  SCK.flush();
  hwlib::wait_us(5);
  SCK.write(0);
  SCK.flush();
  hwlib::wait_us(1);
}



int hx711::read_no_calibration(){
  power_up(); // ensures that the hx711 is powered up, otherwise if the hx711 is powered down and the read is called it will get stuck because de datapin wil never go down.
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
  }

  for (int j = 1; j<=gain; j++){
    clock();
  }

  //for converting binary to decimal number is used this tutorial for idea for code: https://nl.wikihow.com/Van-een-binair-getal-een-decimaal-getal-maken.
  for(int k=24; k>=0; k--){

    if(array_bits[k] == 1 && k == 0){ // if 24th bit is 1 the read is negative. Then it is two complement. I used this site for inspiration: https://www.youtube.com/watch?v=ykkFk-2y6SE .
      int macht = pow(2, 24);
      result = result - (macht * 1);
    }
    if (array_bits[k] == 1){
      int macht = pow(2, (24-k-1));
      result += macht;
    }
  }
  return result;
}



void hx711::calibration_set(){
  // calculate averge of 100 readings and will make the weight of the scale with no weight on it zero.
  int sum = 0;
  read_no_calibration(); // first value is wird so this is othwise the calibartion is off.
  for (int i=1; i<=100; i++){
    sum += read_no_calibration();
    hwlib::cout << sum << hwlib::endl;
  }
  int avg_no_calibration = (sum / 100);
  avg_no_calibration *= -1; // will make the number positive.
  calibration_number = avg_no_calibration; // The avarege of hunderd read will with no weight on the scale will set the 0 point of the scale.
}



void hx711::setup(){
  if(gain > 3){
    gain = 3;
  }
  if (gain < 1){
    gain = 1;
  }
  DT.refresh();
  while(DT.read() == 1){
    DT.refresh();
  }

  for (int i=0; i<=24; i++){
    clock();
  }

  for (int j = 1; j<=gain; j++){
    clock();
  }

  DT.refresh();
  while(DT.read() == 1){
    DT.refresh();
  }

  for (int k=0; k<=24; k++){
    clock();
  }

  for (int l = 1; l<=gain; l++){
    clock();
  }

  DT.refresh();
  while(DT.read() == 1){
    DT.refresh();
  }

  for (int k=0; k<=24; k++){
    clock();
  }

  for (int l = 1; l<=gain; l++){
    clock();
  }
}



int hx711::read(){
  int result = read_no_calibration();
  result += calibration_number;
  if (calibration_weight_number == 0){
    return result;
  }
  result = (result / calibration_weight_number);
  return result;
}



int hx711::read_eco(){
  int result = read_no_calibration();
  power_down(); // the clock pin pulled high. Because after 60 microseconds the hx711 will go to sleep and it will wake up after the clock pin is pulled low.
  result += calibration_number;
  if (calibration_weight_number == 0){ // if calibration number is not given it wil give the result back. if the calibration weight number is not given, the result will not be accurate.
    return result;
  }
  result = (result / calibration_weight_number); //result converted to grams.
  return result;
}



int hx711::read_pounds(){ //result is by integer accurate beacause of the arduino can not handle good float values.
  int result = read_no_calibration();
  result += calibration_number;
  result = (result / calibration_weight_number);
  result *= 0.0022046; // 1 gram is 0.0022046 pounds.
  return result;
}



int hx711::read_avg_10(){
  int sum = 0;
  for (int i=1; i<=10; i++){
    sum+=read();
  }
    return (sum / 10);
}



int hx711::read_avg_100(){
  int sum = 0;
  for (int i=1; i<=100; i++){
    sum+=read();
  }
  return (sum / 100);
}



int hx711::read_avg_variable(int amount){
  // This function will calulate a averagere of given of read commando
  int sum = 0;
  if (amount < 0){
    amount = 0;
  }
  for (int i=1; i<=amount; i++){
    sum+=read();
  }
  return (sum / amount);
}



int hx711::get_calibration_number(){
  return calibration_number;
}



int hx711::get_gain(){
  return gain;
}
