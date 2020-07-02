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
  /// calibration number(for scale to set to zero point)
  /// \details
  /// This number is the calibration number.
  /// If the function: calibration_set is runned. the calibration number will bring the scale to the correct zero point.
  /// The function: calibration_set must be runned in the main of the program en there must be no weight on the scale by calibration.
  /// will be zero if the function: calibration_set is not runned.
  int calibration_zero_point_number = 0;



  /// \brief
  /// weight calibration number(for accurate weight in grams)
  /// \details
  /// This number is used for calibration for accurate weight calculation.
  /// To get this number you need to place a object of a known weight on your scale.
  /// And read the value of the read. And divide by the known weight of the value and set the calibration_weight_number in de intiizer list.
  /// Or the calibration software must be runned.
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
  calibration_zero_point_number( 0 ),// calibration_zero_point_number will be set to right number after calibration_set function is runned. or the setup function.
  calibration_weight_number( calibration_weight_number )
  {}


   /// \brief
   /// Power down command for hx711 chip
   /// \details
   /// Power down command for the hx711 chip.
   /// This is used if the hx711 chip is not used to save energy.
   /// This will pull the clock pin high and after 60 microseconds the hx711 will power power_down
   /// Until the clock pin will pulled low.(function power_up).
   /// Please note: after a power down command, and it is given a power up command. The hx711 chip is reset and the gain is 128.
   void power_down();



   /// \brief
   /// Power up command for hx711 chip
   /// \details
   /// Power down command for the hx711 chip.
   /// This is used if the hx711 chip if the hx711 is power_down and the hx711 must be used again.
   /// This will pull the clock pin low. And the hx711 will power up.
   /// This command must only be given after a power_down command.
   /// Please note: after a power down command, and it is given a power up command. The hx711 chip is reset and the gain is 128.
   void power_up();



   /// \brief
   /// setup for hx711 chip.
   /// \details
   /// This function will communicate with te chip the first time. Because the chip expect to set a gain,
   /// The first time values will not be used. Because of experience the fist values are not very accurate.
   /// The setup fucntion will also run the set calibration function to set the scale to the correct zero point
   /// It is import that there is no weight on the scale by the setup. Otherwise the calibration is not accurate.
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
    /// Energy efficent read weight function for hx711 class/chip (with calibration).
    /// \details
    /// This function will read the weight of the hx711 chip in grams
    /// And than will power down the hx711 chip.
    /// The hx711 will recuire the need of load cells.
    /// After the hx711 power down and it is later powered up.
    /// The gain will be reset to 128.
    /// this function uses the calibration given in the constructor.
    int read_eco();



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
    /// if a amount is zero or negaitive the function will give zero back.
    int read_avg_variable(int amount);



   /// \brief
   /// Return calibration_zero_point_number used by the read fucntion.
   /// \details
   /// This function will return in integer the number of the calibration. (calibration_number).
    int get_calibration_zero_point_number();



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
   /// This function will get the gain of the class.
   /// the gain is has 3 options.
   /// option 1: gain = 1. The gain is 128.
   /// option 2: gain = 2. The gain is 32.
   /// option 3: gain = 3. The gain is 64.
    int get_gain();

};


#endif // HX711_HPP
