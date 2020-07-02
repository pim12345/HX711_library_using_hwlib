# HX711_weegschaal_pim
ipass project hx711 library 
hx 711 library + code for scale + calibration software

Application for weighting scale. 

Readme: 
Before the use of the scale program is it important to use the calibration software for the accurate results
The demo code uses a hx711 chip and 4 times 3-wire load cells. And the glcd_oled by i2c protocol and two buttons

by using the library it is important to run first the setup code and after the calibration code

This library/democode use the hwlib library from Wouter van Ooijen (wouter@voti.nl) and uses the cmath library for power calulations

the demo hardware uses the hx711 with 4 times 3-wire load cells. the tutorial for connecting is used this:https://circuitjournal.com/50kg-load-cells-with-HX711 by Indrek Luuk
and the 3d-printed parts i used are made by patrick3345(under the Creative Commons - Attribution license.) From thingiverse, link: https://www.thingiverse.com/thing:2624188



 programmed by pim goes under the boost 1.0 license