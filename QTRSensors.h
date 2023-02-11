#ifndef _QTR_SENSORS_H_
    #define _QTR_SENSORS_H_

    #include <Arduino.h>
    //#include <Serial.h>
    #include "hardware/gpio.h"
    #include "hal.h"
    #include "debug.h"
    #include "utils.h"
    #include "motor.h"
    //#include "dec2bin.h"

    #define NORMALIZED_MAX                       1000
    #define MAX_TIME                             8000
    #define MIN_TIME                             50
    #define MIN_ALLOWED_READING                  MIN_TIME // NOISE free minimum VALUE of reading
    #define NOISE_IN_DATA                       -5000
    #define LINE_NUMBER_ERROR_DUE_TOO_MUCH_NOISE 6000
    #define POSITION_OF_BLACK_BLOCK_DETECTED     5000
    #define NOISE_COUNT_FOR_EXIT                 2000
    #define DELAY_10nF_CAPACITOR_CHARGE_uS        900   // DO NOT CHANGE Yes its verified, for given QTR Circuit we have


    const int photoDiodePins[8] = { IR_D1_PIN_NO, IR_D2_PIN_NO, IR_D3_PIN_NO, IR_D4_PIN_NO,
                                    IR_D5_PIN_NO, IR_D6_PIN_NO, IR_D7_PIN_NO, IR_D8_PIN_NO };

    void getSensorArrayValues(          int result[],       unsigned char * sensorByte, bool print);
    void getSensorArrayValuesCalibrated(int sensorValues[], unsigned char * sensorByte, bool print);

    void performCalibration(bool print);



    int readLineBINARY(int d[], unsigned char s, bool printIt);
    int readLine(int d[], unsigned char s, bool printIt);

    void drawLine(int lineNumber, int8_t left, int8_t right, bool clearScreen);

#endif // _QTR_SENSORS_H_