#include "battery.h"

// IMPORTNAT : AIM IS TO DO COMPUTATIONS WITHOUT USING FLOATING TYPE DATA, 
//             because its computationally costly
//

void batteryVoltageCheck(int printInfo)
{
  int s;
  int adcCount;
  int voltageOfBatteryIn_microVolt;

  // Get average value
  adcCount = 0;
  for(s=1; s<= 5; s++)
    {
      adcCount += analogRead(BATTERY_VOLTAGE_CHECK_PIN_NO);
      delayMicroseconds(2);
    }
    adcCount = adcCount / (s-1);


  voltageOfBatteryIn_microVolt = adcCount * adcCountToMicoVoltVolt;

 if(printInfo == 1)
    {
      DUMP_L2_ab("\r\n adcCount = ", adcCount);
      DUMP_L2_ab("\r\n Battery Voltage (uV) = ", voltageOfBatteryIn_microVolt);
    }

  if(voltageOfBatteryIn_microVolt < BATTERY_LOW_VOLTAGE_CUTOFF)
    {
        motionStop();
        digitalWrite(IR_ON_PIN_NO,         LOW); // HIGH = ON;

        DUMP_L1_a ("\r\n ###########  LOW BATTERY ###########");
        DUMP_L1_ab("\r\n adcCount = ", adcCount);
        DUMP_L1_ab("\r\n Battery Voltage (uV) = ", voltageOfBatteryIn_microVolt);

        hang(" LOW BATTERY ");
    }
  
}



//// OLD/ Previous inefficient version
//// Kept foe Acedamic use:
////
//float batteryVoltageCheck(int printInfo)
//{
//   //
//   // Voltage Divider formula:
//   //
//   // Vout = Vin*R2/(R1+R2)
//   // Vin  = Vout*(R1+R2)/R2
//   //
//
//  int adcCount = analogRead(BATTERY_VOLTAGE_CHECK_PIN_NO);
//  float voltageOfBattery;
//
//  voltageOfBattery = adcCount * adcCountToMicoVoltVolt;
//
// if(printInfo == 1)
//    {
//      DUMP_L2_ab("\r\n adcCount = ", adcCount);
//      DUMP_L2_ab("\r\n voltageDividerRatio = ", voltageDividerRatio);
//      DUMP_L2_ab("\r\n adcCountToMicoVoltVolt = ", adcCountToMicoVoltVolt);
//      DUMP_L2_ab("\r\n Battery Voltage = ", voltageOfBattery);
//    }
//
//  if(voltageOfBattery < BATTERY_LOW_VOLTAGE_CUTOFF)
//    {
//        motionStop();
//        digitalWrite(IR_ON_PIN_NO,         LOW); // HIGH = ON;
//
//        DUMP_L1_a ("\r\n ###########  LOW BATTERY ###########");
//        DUMP_L1_ab("\r\n adcCount = ", adcCount);
//        DUMP_L1_ab("\r\n voltageDividerRatio = ", voltageDividerRatio);
//        DUMP_L1_ab("\r\n adcCountToMicoVoltVolt = ", adcCountToMicoVoltVolt);
//        DUMP_L1_ab("\r\n Battery Voltage = ", voltageOfBattery);
//
//        DUMP_L1_a ("\r\n ###########  LOW BATTERY ###########");
//        DUMP_L1_ab("\r\n adcCount = ", adcCount);
//        DUMP_L1_ab("\r\n voltageDividerRatio = ", voltageDividerRatio);
//        DUMP_L1_ab("\r\n adcCountToMicoVoltVolt = ", adcCountToMicoVoltVolt);
//        DUMP_L1_ab("\r\n Battery Voltage = ", voltageOfBattery);
//
//        hang();
//    }
//
//  return voltageOfBattery;
//}
/////////////////////////////////////////////////////////////////////////
