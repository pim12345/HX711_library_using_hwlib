#ifndef HX711_HPP
#define HX711_HPP

#include "hwlib.hpp"// is used for pin manimpulations.
#include <array> // is used for saving bits from the hx711 chip.
#include <cmath> //is used for squared calulations
/// @file

/// \brief
/// HX711 CLASS
/// \details
/// This is a class that implements the reading of a hx711 chip.
/// Hx711 datasheet: https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf
/// The class wil ask for 2 wires in the constructor:
/// The data pin is the DT_pin (hwlib pin_in)
/// And the clock pin SCK (hwlib pin_out).
/// To get the accurate reading it is important to run the setup function first
class hx711 {
protected:

  /// \brief
  /// Clock pin.
  /// \details
  /// This is the clock pin/wire of the hx711 chip. The pin location is assigned in the main of any program.
  /// The clock will be created in the private functon: clock().
  hwlib::pin_out & SCK;



  /// \brief
  /// Data pin.
  /// \details
  /// This is the data pin/wire of the hx711 chip. The pin location is assigned in the main of any program.
  /// The data wire will be used by the read 's function's.
  hwlib::pin_in  & DT;



  /// \brief
  /// clock function
  /// \details
  /// This function will create a clock that will be used to communicate with te hx711 chip.
  /// The clock high times will be around 11.5 microsecond. (tested on arduino DUE).
  /// The clock low times wille around 9 microsecond. (tested on arduino DUE).
  void clock();



  /// \brief
  /// The gain of the hx711 chip
  /// \details
  /// This value will set the gain of the readings of the hx711 chip.
  /// The value must be set in the constructer of het hx711 class.
  /// If no value is given in the constructor. the value will be 1(gain of 128).
  /// 3 options will be given.
  /// option 1: gain = 1. The gain is 128.
  /// option 2: gain = 2. The gain is 32.
  /// option 3: gain = 3. The gain is 64.
  /// if an other value will be given it will be corrected in the setup function.
  int gain;



  /// \brief
  /// calibration number(for scale to set to zero)
  /// \details
  /// This number is the calibration number.
  /// If the function: calibration_set is runned. the calibration number will bring the scale to the correct zero point.
  /// The function: calibration_set must be runned in the main of the program en there must be no weight on the scale by calibration.
  /// will be zero if the function: calibration_set is not runned.
  int calibration_number = 0;



  /// \brief
  /// weight calibration number
  /// \details
  /// This number is used for calibration for accurate weight calculation.
  /// To get this number you need to place a object of a known weight on your scale.
  /// and read the value of the read. And divide by the known weight of the value and set the calibration_weight_number in de intiizer list
  int calibration_weight_number;



public:

   /// \brief
   /// constructor of the hx711 chip
   /// \details
   /// This constructor initializes two data pins. The clock pin(SCK: HWlib pin_out) and the data pin(DT: HWlib pin_in).
   /// this wil be used as reference because otherwise it will not be affected the real world.
   /// with just a whole value.
  hx711(hwlib::pin_out & SCK, hwlib::pin_in & DT, int gain = 1, int calibration_weight_number = 0 ):
  SCK( SCK ),
  DT( DT ),
  gain( gain ),
  calibration_number( 0 ),// calibration level will be set to right number after calibration_set function is runned.
  calibration_weight_number( calibration_weight_number )
  {}



   /// \brief
   /// setup for hx711 chip.
   /// \details
   /// This function will communicate with te chip the first time. Because the chip expect to set a gain,
   /// (25 clock). the first time values will not be used.
    void setup();



   /// \brief
   /// Read weight without calibration function for hx711 class/chip.
   /// \details
   /// This function will read the weight of the hx711 chip without calibration.
   /// The hx711 will recuire the need of load cells.
   /// In this library the gain will always be 128.
    int read_no_calibration();



   /// \brief
   /// Read weight function for hx711 class/chip (with calibration).
   /// \details
   /// This function will read the weight of the hx711 chip in grams.
   /// The hx711 will recuire the need of load cells.
   /// The gain wil be set in the constructer.
   /// this function uses the calibration given in the constructor.
    int read();



    /// \brief
    /// Read weight in pounds function for hx711 class/chip (with calibration).
    /// \details
    /// This function will read the weight of the hx711 chip in ponds.
    /// The hx711 will recuire the need of load cells.
    /// In this library the gain will always be 128.
    /// Please note that a lot of emmbedded systems can't handle float conversions well,
    /// PLease note that the weight given is a integer. So it will be no decimal numbers.
    int read_pounds();



   /// \brief
   /// 10 average read weight function for hx711 class/chip.
   /// \details
   /// This function will read ten times the weight of the hx711 chip.
   /// And will calulate the average of those ten reads, and return it.
   /// The hx711 will recuire the need of load cells.
   /// The gain wil be set in the constructer.
    int read_avg_10();



   /// \brief
   /// 100 average read weight function for hx711 class/chip.
   /// \details
   /// This function will read hunderd times the weight of the hx711 chip.
   /// And will calulate the average of those hunderd reads, and return it.
   /// The hx711 will recuire the need of load cells.
   /// The gain wil be set in the constructer.
    int read_avg_100();



    /// \brief
    /// Calulate the avagere of given amount of reads
    /// \details
    /// This function will calulate a average of a given amount of reads given by as a argument.
    /// Please note: the time that the function will take will increase with more and more reads.
    int read_avg_variable(int amount);



   /// \brief
   /// Return calibration number used by the read fucntion.
   /// \details
   /// This function will return in integer the number of the calibration. (calibration_number).
    int get_calibration_number();



   /// \brief
   /// Set scale to zero function(calibration).
   /// \details
   /// This function will set the correct calibration number.
   /// So that the read function will give a correct number back by using the calibration number.
   /// This function will NEED to be runned first to ensure accurate measurements.
    void calibration_set();



   /// \brief
   /// Function to get the gain of the the class.
   /// \details
   /// This function will get the gain of the class
    int get_gain();

};


class hx711_display : public hx711 {
private:
  //hx711 scale;
  hwlib::pin_oc & scl;
  hwlib::pin_oc & sda;

public:
  hx711_display(hwlib::pin_out & SCK, hwlib::pin_in & DT, hwlib::pin_oc & scl, hwlib::pin_oc & sda ):
  hx711( SCK, DT ),
  scl( scl ),
  sda( sda )
  {}

    void setup(){

    }


};

#endif // HX711_HPP
