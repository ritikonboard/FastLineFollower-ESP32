#ifndef _HAL_H_
    #define _HAL_H_

    #define LED_SUCCESS_PIN_NO   11
    #define BUZZER_PIN_NO        26

    #define SWITCH_TOP_PIN_NO    27
    #define SWITCH_MIDDLE_PIN_NO 22
    #define SWITCH_BOTTOM_PIN_NO 21

    #define MOTOR_LEFT_A_PIN_NO  16
    #define MOTOR_LEFT_B_PIN_NO  17
    #define MOTOR_STANDBY_PIN_NO 18
    #define MOTOR_RIGHT_A_PIN_NO 19
    #define MOTOR_RIGHT_B_PIN_NO 20

    #define IR_LEFT_PIN_NO    13  // Left  Sensor
    #define IR_RIGHT_PIN_NO   12  // Right Sensor

    #define IR_ON_PIN_NO   10

    #define IR_D1_PIN_NO   9
    #define IR_D2_PIN_NO   8
    #define IR_D3_PIN_NO   7
    #define IR_D4_PIN_NO   6
    #define IR_D5_PIN_NO   5
    #define IR_D6_PIN_NO   4
    #define IR_D7_PIN_NO   3
    #define IR_D8_PIN_NO   2

    #define BATTERY_VOLTAGE_CHECK_PIN_NO    A2
    #define ANALOG_REFERENCE_VOLTAGE        3.3   // Do NOT change
    #define ANALOG_READ_RESOLUTION          12    // Do NOT change
    #define R7_OHM_POSITIVE                 10000.0
    #define R8_OHM_GROUND                   5100.0

 //// Select any one: 
    #define ANALOG_WRITE_RESOLUTION         16    // Allows speeds of 0 to 65,565
   //   #define ANALOG_WRITE_RESOLUTION         8   // Allows speeds of 0 to 255

    #include "utils.h"

    void init_GPIO(void);


#endif // _HAL_H_