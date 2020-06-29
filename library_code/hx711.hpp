#ifndef HX711_HPP
#define HX711_HPP

#include "hwlib.hpp"
#include <array>
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
  /// calibration number
  /// \details
  /// This number is the calibration number.
  /// If the function: "calibration_set" is runned. the calibration number will bring the scale to the correct zero point.
  /// The function: "calibration_set" must be runned in the main of the program en there must be no weight on the scale by calibration.
  int calibration_number = 0;



public:

   // \brief
   /// constructor of the hx711 chip
   /// \details
   /// This constructor initializes two data pins. The clock pin(SCK: HWlib pin_out) and the data pin(DT: HWlib pin_in).
   /// this wil be used as reference because otherwise it will not be affected the real world.
   /// with just a whole value.
  hx711(hwlib::pin_out & SCK, hwlib::pin_in  & DT ):
  SCK( SCK ),
  DT( DT ),
  calibration_number( 0 )// calibration level will be set to right number after calibration_set is runned.
  {}


    // \brief
   /// setup for hx711 chip.
   /// \details
   /// This function will communicate with te chip the first time. Because the chip expect to set a gain,
   /// (25 clock). the first time values will not be used.
    void setup();


    // \brief
   /// read weight without calibration function for hx711 class/chip.
   /// \details
   /// This function will read the weight of the hx711 chip without calibration.
   /// The hx711 will recuire the need of load cells.
   /// In this library the gain will always be 128.
    int read_no_calibration();



    // \brief
   /// read weight function for hx711 class/chip (with calibration).
   /// \details
   /// This function will read the weight of the hx711 chip.
   /// The hx711 will recuire the need of load cells.
   /// In this library the gain will always be 128.
    int read();



    // \brief
   /// 10 average read weight function for hx711 class/chip.
   /// \details
   /// This function will read ten times the weight of the hx711 chip.
   /// And will calulate the average of those ten reads, and return it.
   /// The hx711 will recuire the need of load cells.
   /// In this library the gain will always be 128.
    int read_avg_10();



    // \brief
   /// 100 average read weight function for hx711 class/chip.
   /// \details
   /// This function will read hunderd times the weight of the hx711 chip.
   /// And will calulate the average of those hunderd reads, and return it.
   /// The hx711 will recuire the need of load cells.
   /// In this library the gain will always be 128.
    int read_avg_100();



    // \brief
   /// Return calibration number used by the read fucntion.
   /// \details
   /// Return calibration number used by the read fucntion.
    int get_calibration_number();


    // \brief
   /// Set scale to zero function(calibration).
   /// \details
   /// This function will set the correct calibration number.
   /// So that the read function will give a correct number back by using the calibration number.
   /// This function will NEED to be runned first to ensure accurate measurements. 
    void calibration_set();

};

#endif // HX711_HPP
