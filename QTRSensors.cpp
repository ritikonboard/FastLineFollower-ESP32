#include "QTRSensors.h"

bool isCalibrated = false;

       int calMin[8];
const  int calMax = MAX_TIME;

extern const char *dec2binStr[];
             char  displayStr[120];

void getSensorArrayValues(int result[], unsigned char * sensorByte, bool print)
{
// QTR-8RC line detector (IR LINE TRACKER)
//
// REFERENCE:
//
// https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html#gae895be2d3c5af5df460150eafe7858a4
//
// https://shop.mchobby.be/en/motor-robotic/497-detecteur-de-ligne-ir-line-tracker-3232100004979-pololu.html

    int8_t index;    
    register int time;    

    uint16_t doubleByte, doubleBytePrevious, changedBits;

    // On RPi Pico GPIO mArk the pins of interest by "1"
    //
    //       D1, D2, D3, D4, D5, D6, D7, D8
    //        9,  8,  7,  6,  5,  4,  3,  2
    //
    //       0000-0011-1111-1100
    //          0    3    F    C

    const uint16_t mask_PhotoDiodeAndCapPins = 0x03FC;
    bool ValidData;

    ValidData = true;
    do{

                        // STEP: Charge the capacitors of the ALL sensors, by applying a voltage to the OUT pin
                        gpio_set_dir_out_masked(mask_PhotoDiodeAndCapPins); // Switch all GPIOs in "mask" as OUTPUT
                        gpio_set_mask(mask_PhotoDiodeAndCapPins);           // Drive high every GPIO appearing in mask
                        delayMicroseconds(DELAY_10nF_CAPACITOR_CHARGE_uS);  // This will DIScharge all the Capacitors

                        // STEP: Switch ON IR LEDs
                        digitalWrite(IR_ON_PIN_NO, HIGH);  // HIGH = ON


                        // This loop consumes some time! (so some delay above can be reduced! if it is required)
                        for(index=0; index <= 7; index++)  // Initialize result array
                            result[index] =  MAX_TIME;     // Assume all Black

                        // STEP: Count the time taken by photodiode to Charge the capacitor :
                        //       White charges fast: Lower count
                        //       Black charges slow: High cout or MAX
                        //       In other words:
                        //         Increment time until this pin gets low again,
                        //         If its taking too much time, stop incrementing time, assume it as black

                        gpio_set_dir_in_masked(mask_PhotoDiodeAndCapPins); // Switch all GPIOs in "mask" as INPUT
                        doubleByte = gpio_get_all(); // READ All input pins

                        doubleBytePrevious = doubleByte = doubleByte & mask_PhotoDiodeAndCapPins; // Keep only pins of interest, Zero-out others
                       
                        time = 0;
                        while (time < MAX_TIME)
                        {
                            time++;

                            doubleByte = gpio_get_all() & mask_PhotoDiodeAndCapPins;

                            if( doubleByte == doubleBytePrevious)
                                continue;
                            if(time < MIN_TIME)
                            {
                                ValidData = false;
                                break;
                            }

                            changedBits = doubleByte ^ doubleBytePrevious; // XOR: All changed bits becoms 1, unchanged bits becomes 0

                            index =7;
                            while(changedBits) // For all changed bits: Save the result
                            {
                                if(changedBits & 0x0004)
                                {
                                   // STEP: Save Result for the n'th sensor:
                                   result[index] = time;
                                }
                                changedBits = changedBits >> 1;
                                index--;
                            }

                            doubleBytePrevious = doubleByte;
                        }
                        if(ValidData==true)
                            break;
    } while(1); // do while ValidData 

    // Black is the HIGHER VALUE so Black is One
    // BLACK is ONE (White is Zero)
    *sensorByte = 0; // Assume all are black
	for(index =7; index >=0;  index--)
	{
	    if(result[index] == MAX_TIME)
	    {
	       *sensorByte = *sensorByte | ( 1 << index);
	    }
	}

    // STEP: Switch OFF IR LEDs
    digitalWrite(IR_ON_PIN_NO, LOW);

    // IMPORTANT: 
    // Keep the cps on charging for next use
    // Making the pins as o/p will introduce less noise in uC !
    // STEP: Charge the capacitors of the ALL sensors, by applying a voltage to the OUT pin
    gpio_set_dir_out_masked(mask_PhotoDiodeAndCapPins); // Switch all GPIOs in "mask" as OUTPUT
    gpio_set_mask(mask_PhotoDiodeAndCapPins);           // Drive high every GPIO appearing in mask

    // STEP: Display Result, if required
    if(print)
    {   
        sprintf(displayStr,"\r\nD8:%4d D7:%4d D6:%4d D5:%4d D4:%4d D3:%4d D2:%4d D1:%4d  %s", 
                result[7], result[6], result[5], result[4], 
                result[3], result[2], result[1], result[0],
                dec2binStr[*sensorByte] );

        DUMP_SA_a(displayStr);        
    }

}
//////////////////////////////////////////////////////////////////////////////////////
//
//  Calibrating your sensors can lead to substantially more reliable sensor readings
//  During this calibration phase, you will need to expose each of your reflectance
//  sensors to the lightest and darkest readings they will encounter.
//  For example, if you have made a line follower, you will want to slide it across
//  the line during the calibration phase so the each sensor can get a reading of how
//  dark the line is and how light the ground is.

// This method reads the sensors multiple times and uses the results for calibration.
// The sensor values are not returned; instead, the (maximum and) minimum values found
// over time are stored
//////////////////////////////////////////////////////////////////////////////////////
void performCalibration(bool print)
{
       const  int noSamples     = 20;
       const  int motor_speed_during_calibration   = 12000;
       const  int samplingDelay = 25;

              int samples[8];
    unsigned char sensorByte;
    
    int i, j;
    for(j=0; j<=7; j++)
    {
        calMin[j] = MAX_TIME;
    }

    DUMP_SA_a("\r\n performCalibration()");

        DUMP_MO_a("\r\n Turn Left");
        moveMotors(motor_speed_during_calibration, -motor_speed_during_calibration, print);
        for(i=0; i<= noSamples; i++)
        {
            getSensorArrayValues(&samples[0], &sensorByte, print);
        
            for(j=0; j<= 7; j++) // For all 8 Sensors in the QTR Sensor Array
            {
                if( samples[j] < calMin[j] && samples[j] > MIN_ALLOWED_READING) // if currently acquired sensor value is lower than calMin
                    calMin[j] = samples[j]; // then save it                       
            }
            delay(samplingDelay);
        }        

        DUMP_MO_a("\r\n STOP Both Motors");
        moveMotors(0, 0, print);
        delay(1500);

        DUMP_MO_a("\r\n Turn Right");
        moveMotors(-motor_speed_during_calibration, motor_speed_during_calibration, print);
        for(i=0; i<= noSamples; i++)
        {
            getSensorArrayValues(&samples[0], &sensorByte, print);
            for(j=0; j<= 7; j++) // For all 8 Sensors in the QTR Sensor Array
            {
                if( samples[j] < calMin[j] && samples[j] > MIN_ALLOWED_READING) // if currently acquired sensor value is lower than calMin
                    calMin[j] = samples[j]; // then save it                       
            }
            delay( (samplingDelay * 2) ); // 180 degree
        }
                
        DUMP_MO_a("\r\n STOP Both Motors");
        moveMotors(0, 0, print);
        delay(1500);

        DUMP_MO_a("\r\n Turn Left and stop at center");
        moveMotors(motor_speed_during_calibration, -motor_speed_during_calibration, print);
        for(i=0; i<= noSamples; i++)
        {
            getSensorArrayValues(&samples[0], &sensorByte, print);
            for(j=0; j<= 7; j++) // For all 8 Sensors in the QTR Sensor Array
            {
                if( samples[j] < calMin[j] && samples[j] > MIN_ALLOWED_READING) // if currently acquired sensor value is lower than calMin
                    calMin[j] = samples[j]; // then save it                       
            }
            delay(samplingDelay);
        }

        DUMP_MO_a("\r\n STOP Both Motors");
        moveMotors(0, 0, print);
        delay(1500);

        DUMP_MO_a("\r\n Finally, the MINIMUM values, which will be used for calibration are:\r\n");
                   
        sprintf(displayStr,"\r\n M8:%4d M7:%4d M6:%4d M5:%4d M4:%4d M3:%4d M2:%4d M1:%4d", 
                calMin[7], calMin[6], calMin[5], calMin[4], 
                calMin[3], calMin[2], calMin[1], calMin[0] );
        DUMP_SA_a(displayStr);

    isCalibrated = true; // Indicate globally that the QTR Sensors are now calibrated.
    DUMP_SA_a("\r\n Calibration constants for QTR Sensors are ready.");

}
////////////////////////////////////////////////////////////////////////////
void getSensorArrayValuesCalibrated(int sensorValues[], unsigned char * sensorByte, bool print)
{
    int i;

    if(isCalibrated == false)
    {

      DUMP_SA_a("\r\n ERROR: Sensors must be calibrated before using: getSensorArrayValuesCalibrated()");
      DUMP_SA_a("\r\n        Modify your program to call: performCalibration()");

           hang("\r\n ERROR: Sensors must be calibrated before using: getSensorArrayValuesCalibrated()");
    }

    getSensorArrayValues(&sensorValues[0], sensorByte, NO_PRINT); //print);

    uint16_t denominator;
    int16_t value;

    for(i=0; i<=7; i++)
    {
        denominator = calMax - calMin[i];


        value = 0;
        if (denominator != 0)
        {
          value = (( (int32_t) sensorValues[i]) - calMin[i]) * NORMALIZED_MAX / denominator;
        }

        if (value < 0) { value = 0; }
        else if (value > NORMALIZED_MAX) { value = NORMALIZED_MAX; }

        sensorValues[i] = value;


    }

    // STEP: Display Result
    if(print)
    {   
        sprintf(displayStr,"\r\nN8:%4d N7:%4d N6:%4d N5:%4d N4:%4d N3:%4d N2:%4d N1:%4d  %s", 
        sensorValues[7], sensorValues[6], sensorValues[5], sensorValues[4], 
        sensorValues[3], sensorValues[2], sensorValues[1], sensorValues[0],
        dec2binStr[*sensorByte] );
        
        DUMP_SA_a(displayStr);
    }

}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
int readLine(int sensorValues[], unsigned char s, bool printIt)
{

////
//// REFERENCE: https://www.pololu.com/docs/0J19/3
////
//// Support » Arduino Library for the Pololu QTR Reflectance Sensors »
//// 3. QTRSensors Methods & Usage Notes
////
//// This function returns an estimated position of the line.
//// The estimate is made using a weighted average of the sensor indices multiplied by 1000,
//// so that a return value of 0 indicates that the line is directly below sensor 0
//// (or was last seen by sensor 0 before being lost),
//// a return value of 1000 indicates that the line is directly below sensor 1,
//// 2000 indicates that it’s below sensor 2, etc.
//// Intermediate values indicate that the line is between two sensors.
//// The formula is:
////
////  0*value0 + 1000*value1 + 2000*value2 + ...
//// --------------------------------------------
////     value0  +  value1  +  value2 + ...
////
//// This function/ method remembers where it last saw the line,
//// so if you ever lose the line to the left or the right, it’s
//// line position will continue to indicate the direction you need to go to reacquire the line.
//// For example,
//// if sensor 4 is your rightmost sensor and you end up completely off the line to the left,
//// this function will continue to return 4000.
////
//

           int index, numerator, denominator;
           int noOfBlacks;
           int lineNumber;
    static int pastValue; // Due to "static" key word, it rembembers the value even after the function returns



    noOfBlacks=0;
    for(index=0; index <= 7; index++)  //
    {
        if(sensorValues[index] == NORMALIZED_MAX)
        noOfBlacks++;
    }

    if(noOfBlacks==8)
        return POSITION_OF_BLACK_BLOCK_DETECTED; 

    if(noOfBlacks >= 1)
    {
        numerator =0, denominator=0;
        for(index=0; index <= 7; index++)  //
        {
            numerator   = numerator   + (index * NORMALIZED_MAX * sensorValues[index] );
            denominator = denominator +                           sensorValues[index]  ;
        }

       lineNumber =  numerator / denominator;
       pastValue = lineNumber;
    }
    else
       lineNumber =  pastValue;

   
   //   STEP: Display Result
   if(printIt) 
       { DUMP_SA_ab("\r\n LINE= ", lineNumber); }

    
   return lineNumber;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void drawLine(int lineNumber, int8_t left, int8_t right, bool clearScreen)
{
   int s,n, errNo;
   char errStr[20];

    if(clearScreen)
    {
       //Serial.write(27);
       //Serial1.write(27);
    }

      
   //DUMP_L1_ab("\r\n lineNumber= ",        lineNumber);
   
   
   //DUMP_L1_ab("\r\n n = (lineNumber-100)/20= ", n);
   

        DUMP_L1_a("\r\n");
        
//      DUMP_L1_a("\r\n                | LEFT                            RIGHT |");

#define BLACK  0
#define WHITE  1
#define MIDDLE 3500
        if(left==WHITE && right==WHITE)
          { DUMP_L1_a("\r\n                | LEFT: White              White: RIGHT |");
            //errNo = lineNumber - MIDDLE;
            //n = 55 - (lineNumber-100)/20;
          }
  else  if(left==WHITE && right==BLACK)
          { DUMP_L1_a("\r\n                | LEFT: White              Black: RIGHT |");
            //errNo = MIDDLE - lineNumber;
            //n =  (lineNumber-100)/20;
          }
  else  if(left==BLACK && right==WHITE)
          { DUMP_L1_a("\r\n                | LEFT: Black              White: RIGHT |");
            //errNo = lineNumber - MIDDLE;
            //n = 55 - (lineNumber-100)/20;
          }
  else  if(left==BLACK && right==BLACK)
          { DUMP_L1_a("\r\n                | LEFT: Black              Black: RIGHT |");
            //errNo = lineNumber - MIDDLE;
            //n = 55 - (lineNumber-100)/20;
          }

        errNo = lineNumber - MIDDLE;
        n = 55 - (lineNumber-100)/20;

        DUMP_L1_a("\r\n |    |    |    | D8 | D7 | D6 | D5 | D4 | D3 | D2 | D1 |    |    |    |");
        DUMP_L1_a("\r\n |    |    |    |    |    |    |    |    |    |    |    |    |    |    |");
        DUMP_L1_a("\r\n |    |    |    |  7 |  6 |  5 |  4 |  3 |  2 |  1 |  0 |    |    |    |");
        DUMP_L1_a("\r\n ");


        if(lineNumber == POSITION_OF_BLACK_BLOCK_DETECTED)
            {DUMP_L1_a("               #########################################");
             DUMP_L1_a("\r\n                        BLACK BLOCK DETECTED");
             
             return;
             }
  

        for(s=1; s<=n; s++)
            {  DUMP_L1_a(" "); }
        DUMP_L1_a("|______________|");


        DUMP_L1_a("\r\n ");
        for(s=1; s<=n; s++)
            { DUMP_L1_a(" ");  }

        sprintf(errStr, "|### E:%4d ###|", errNo);
        DUMP_L1_a(errStr);

}
//////////////////////////////////////////////////////////////////////////////

//                        int readLineBINARY(int d[], unsigned char s, bool printIt) //unsigned char whiteLine = 0)
//                        {
//                            int i;
//                            int lineNumber;
//
//                                   int position;
//                            static int pastValue; // Due to "static" key word, it rembembers the value even after the function returns
//                            static int noise=0;
//                            
//                            int noOfBlacks;
//                        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                        //               
//                        //                             Left                                            Right                                           
//                        //                     
//                        //      |      |      |      | D8   | D7   | D6   | D5   | D4   | D3   | D2   | D1   |
//                        //      |      |      |      |      |      |      |      |      |      |      |      |
//                        // S[]= |      |      |      |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |     
//                        //      |      |      |      |      |      |      |      |      |      |      |      |____________________|  1200 : OFF LEFT
//                        //      |      |      |      |      |      |      |      |      |      |      |                    |
//                        //      |      |      |      |      |      |      |      |      |      |      |____________________|         1100 : D1
//                        //      |      |      |      |      |      |      |      |      |      |                    |
//                        //      |      |      |      |      |      |      |      |      |      |____________________|                1000 : D2 D1
//                        //      |      |      |      |      |      |      |      |      |                    |
//                        //      |      |      |      |      |      |      |      |      |____________________|                        900 : D3 D2 D1
//                        //      |      |      |      |      |      |      |      |                    |
//                        //      |      |      |      |      |      |      |      |____________________|                               800
//                        //      |      |      |      |      |      |      |                    |
//                        //      |      |      |      |      |      |      |____________________|                                      700
//                        //      |      |      |      |      |      |                    |
//                        //      |      |      |      |      |      |____________________|                                             600
//                        //      |      |      |      |      |                    |
//                        //      |      |      |      |      |____________________|                                                    500
//                        //      |      |      |      |                    |
//                        //      |      |      |      |____________________|                                                           400
//                        //      |      |      |                    |
//                        //      |      |      |____________________|                                                                  300
//                        //      |      |                    |
//                        //      |      |____________________|                                                                         200
//                        //      |                    |
//                        //      |____________________|                                                                                100
//                        //
//                        // P=          100    200    300    400    500    600    700    800    900    1000   1100    1200    
//                        //                     
//                        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                            if(noise > NOISE_COUNT_FOR_EXIT)
//                            {
//                                noise=0;
//                                DUMP_L1_a("\r\n ERROR: TOO MANY NOISE SAMPLES");
//                                return LINE_NUMBER_ERROR_DUE_TOO_MUCH_NOISE; 
//                            }
//
//                            noOfBlacks = 0;  // Find the number of Ones in the Byte
//                            for(i=0x01 ; i<=0x80; i<<=1)
//                                if(s & i)
//                                    noOfBlacks++;
//                            // Black is represented as 1 in the input sebsor byte
//
//                            if(printIt)
//                                {DUMP_SA_ab("\r\n noOfBlacks= ", noOfBlacks);}
//
//                            switch(noOfBlacks)
//                            {
//                                case 0:   // LOST THE TRACK : All sensors sees white
//                                        if(pastValue <= 300)
//                                          { pastValue = 100;
//                                            return pastValue;
//                                          }
//
//                                        if(pastValue >= 1000)
//                                          { pastValue = 1200;
//                                            return pastValue;
//                                          }
//                                        return pastValue;
//                            
//                                case 1: 
//                                        if( s & 0x01 ) // 0b0000-0001 // if(s[0] == MAX_TIME)
//                                            {   position  = 200;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        if(s & 0x80) // 0b1000-000 // if(s[7] == MAX_TIME)
//                                            {   position  = 1100;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        DUMP_SA_a("1N"); noise++;
//                                        return NOISE_IN_DATA;
//                            
//                                case 2:
//                                        if((s & 0x03) == 0x03) // 0b0000-0011 // if(s[0] == MAX_TIME && s[1] == MAX_TIME)
//                                            {   position  = 300;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        if((s & 0xC0) == 0xC0) // 0b1100-0000 // if(s[6] == MAX_TIME && s[7] == MAX_TIME)
//                                            {   position  = 1000;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        DUMP_SA_a("2N"); noise++;
//                                        return NOISE_IN_DATA;
//                            
//                                case 3:
//                                        if((s & 0x07) == 0x07) // 0b0000-0111 // if(s[0] == MAX_TIME && s[1] == MAX_TIME && s[2] == MAX_TIME)
//                                            {   position  = 400;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        if((s & 0x0E) == 0x0E) // 0b0000-1110 // if(s[1] == MAX_TIME && s[2] == MAX_TIME && s[3] == MAX_TIME)
//                                            {   position  = 500;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        if((s & 0x1C) == 0x1C ) // 0b0001-1100 // if(s[2] == MAX_TIME && s[3] == MAX_TIME && s[4] == MAX_TIME)
//                                            {   position  = 600;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        if((s & 0x38) == 0x38 ) // 0b0011-1000 // if(s[3] == MAX_TIME && s[4] == MAX_TIME && s[5] == MAX_TIME)
//                                            {   position  = 700;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        if((s & 0x70) == 0x70 ) // 0b0111-0000 // if(s[4] == MAX_TIME && s[5] == MAX_TIME && s[6] == MAX_TIME)
//                                            {   position  = 800;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        if((s & 0xE0) == 0xE0 ) // 0b1110-0000 // if(s[5] == MAX_TIME && s[6] == MAX_TIME && s[7] == MAX_TIME)
//                                            {   position  = 900;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                         DUMP_SA_a("3N"); noise++;
//                                         return NOISE_IN_DATA;
//                            
//                                case 4:
//                                        
//                                        if((s & 0x0F) == 0x0F ) // 0b0000-1111 // if(s[0] == MAX_TIME && s[1] == MAX_TIME && s[2] == MAX_TIME && s[3] == MAX_TIME)
//                                            {   noise=0;
//                                                return pastValue;
//                                             }
//                                        if((s & 0x1E) == 0x1E ) // 0b0001-1110 // if(s[1] == MAX_TIME && s[2] == MAX_TIME && s[3] == MAX_TIME && s[4] == MAX_TIME)
//                                            {   noise=0;
//                                                return pastValue;                     
//                                            }
//                                        if((s & 0x3C) == 0x3C ) // 0b0011-1100 // if(s[2] == MAX_TIME && s[3] == MAX_TIME && s[4] == MAX_TIME && s[5] == MAX_TIME)
//                                            {   noise=0;
//                                                return pastValue;
//                                            }
//                                        if((s & 0x78) == 0x78 ) // 0b0111-1000 // if(s[3] == MAX_TIME && s[4] == MAX_TIME && s[5] == MAX_TIME && s[6] == MAX_TIME)
//                                            {   noise=0;
//                                                return pastValue;
//                                             }
//                                        if((s & 0xF0) == 0xF0 ) // 0b1111-0000 // if(s[4] == MAX_TIME && s[5] == MAX_TIME && s[6] == MAX_TIME && s[7] == MAX_TIME)
//                                            {   noise=0;
//                                                return pastValue;                     
//                                            }
//                                         DUMP_SA_a("4N"); noise++;
//                                         return NOISE_IN_DATA;
//                            
//                                case 5:
//                                        if((s & 0x1F) == 0x1F ) // 0b0001-1111 // if(s[0] == MAX_TIME && s[1] == MAX_TIME && s[2] == MAX_TIME && s[3] == MAX_TIME && s[4] == MAX_TIME)
//                                            {   position  = 100; //0;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        if((s & 0x3E) == 0x3E) // 0b0011-1110// if(s[1] == MAX_TIME && s[2] == MAX_TIME && s[3] == MAX_TIME && s[4] == MAX_TIME && s[5] == MAX_TIME) // NOISE
//                                            {   noise=0;
//                                                return pastValue;
//                                             }
//                                        if((s & 0x7C) == 0x7C ) // 0b0111-1100 // if(s[2] == MAX_TIME && s[3] == MAX_TIME && s[4] == MAX_TIME && s[5] == MAX_TIME && s[6] == MAX_TIME) // NOISE
//                                            {   noise=0;
//                                                return pastValue;
//                                             }
//                                        if((s & 0xF8) == 0xF8 ) // 0b1111-1000 // if(s[3] == MAX_TIME && s[4] == MAX_TIME && s[5] == MAX_TIME && s[6] == MAX_TIME && s[7] == MAX_TIME)
//                                            {   position  = 1200; //1300;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                         DUMP_SA_a("5N"); noise++;
//                                         return NOISE_IN_DATA;
//
//                            
//                                case 6:
//                                        if((s & 0x3F) == 0x3F ) // 0b0011-1111 // if(s[0] == MAX_TIME && s[1] == MAX_TIME && s[2] == MAX_TIME && s[3] == MAX_TIME && s[4] == MAX_TIME && s[5] == MAX_TIME)
//                                            {   position  = 100; //0;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        if((s & 0x7E) == 0x7E ) // 0b0111-1110 // if(s[1] == MAX_TIME && s[2] == MAX_TIME && s[3] == MAX_TIME && s[4] == MAX_TIME && s[5] == MAX_TIME && s[6] == MAX_TIME) // NOISE
//                                            {   //position  = ;
//                                                //pastValue = position; 
//                                                noise=0;
//                                                return pastValue;
//                                             }
//                                        if((s & 0xFC) == 0xFC ) // 0b1111-1100 // if(s[2] == MAX_TIME && s[3] == MAX_TIME && s[4] == MAX_TIME && s[5] == MAX_TIME && s[6] == MAX_TIME && s[7] == MAX_TIME)
//                                            {   position  = 1200; //1300;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                         DUMP_SA_a("6N"); noise++;
//                                         return NOISE_IN_DATA;
//                            
//                                case 7:
//                                        if((s & 0x7F) == 0x7F ) // 0b0111-1111 // if(s[0] == MAX_TIME && s[1] == MAX_TIME && s[2] == MAX_TIME && s[3] == MAX_TIME && s[4] == MAX_TIME && s[5] == MAX_TIME && s[6] == MAX_TIME)
//                                            {   position  = 100; //0;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                        if((s & 0xFE) == 0xFE ) // 0b1111-1110 // if(s[1] == MAX_TIME && s[2] == MAX_TIME && s[3] == MAX_TIME && s[4] == MAX_TIME && s[5] == MAX_TIME && s[6] == MAX_TIME && s[7] == MAX_TIME)
//                                            {   position  = 1200; //1300;
//                                                pastValue = position; noise=0;
//                                                return position;
//                                             }
//                                         DUMP_SA_a("7N"); noise++;
//                                         return NOISE_IN_DATA;
//                            
//                                case 8:
//                                         return POSITION_OF_BLACK_BLOCK_DETECTED; 
//                            
//                                default:
//                                         DUMP_L1_a("\r\n WARNING: readLine: default case");
//                                         return NOISE_IN_DATA;
//                            
//                            } // switch
//
//                            DUMP_SA_a("\r\n ############ CHECK ###############");
//                            return pastValue;
//                        }
