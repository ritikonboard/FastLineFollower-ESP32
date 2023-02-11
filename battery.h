#ifndef _BATTERY_H_
    #define _BATTERY_H_


    #include "hal.h"
    #include "debug.h"
    #include "motor.h"
    #include "QTRSensors.h"
    #include "utils.h"
    
// IMPORTNAT : AIM IS TO DO COMPUTATIONS WITHOUT USING FLOATING TYPE DATA, 
//             because its computationally costly
//
//    Analog Input:
//    For analog inputs, the RP2040 device has a 12-bit ADC
//    The standard Arduino calls can be used to read 
//    their values (with 3.3V nominally reading as 4095).
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//       Voltage Divider formula:
//       
//       Vout = Vin*R2/(R1+R2)
//       Vin  = Vout*(R1+R2)/R2
//    const float voltageDividerRatio = (R7_OHM_POSITIVE + R8_OHM_GROUND) / R8_OHM_GROUND ;
//                                    = (10000           + 5100        ) / 5100
//                                    = 2.960784314
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//         3.3V is 4095 count
//         OR
//         4095 count is 3.3V
//            1 count is 3.3/4095 V
//            n count is (n* 3.3)/4095 V
//
//        Vout from Voltage divider:
//
//        Vout = (n* 3.3)/4095 V 
//                Where n is count from ADC
//
//        Battery Voltage = Vin  = Vout*(R1+R2)/R2
//                               = (n * 3.3)/4095 x (R1+R2)/R2
//                               =  n * 3.3 /4095 x (10000 + 5100) / 5100    
//                               =  n * 2.38598 mV
//                               =  n * 2386 uV
//                         
//
//    In other words:
//    const float adcCountToVolt =  ANALOG_REFERENCE_VOLTAGE / (pow(2, ANALOG_READ_RESOLUTION) -1)* voltageDividerRatio;
//    // vin = count * 3.3 / (pow2(analogReadResolution) -1)* voltageDividerRatio;
//    // vin = count * 3.3 / 4095 * 2.960784314
//           = count * 2.385 mV
//           = (count * 2385) /1000 mV
//
//



    // https://www.rcuniverse.com/forum/rc-car-general-discussions-179/10881201-what-should-my-lipo-cutoff.html
    #define BATTERY_LOW_VOLTAGE_CUTOFF      6400000   // SIX POINT FIVE Volt: Should NOT change, until you know, what you are doing!
    const int adcCountToMicoVoltVolt = 2386; // CONSTANT: NEVER CHANGE
    void batteryVoltageCheck(int printInfo);

#endif // _BATTERY_H_
