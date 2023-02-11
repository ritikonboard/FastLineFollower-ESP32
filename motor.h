#ifndef _MOTOR_H_
    #define _MOTOR_H_

    #include <Arduino.h>

    #include "hal.h"


    #define MOTOR_DRIVER_ENABLE  1
    #define MOTOR_DRIVER_STANDBY 0

    void moveMotors(int speedLeft, int speedRight, bool print);
    void motionForward(int speed);
    void motionReverse(int speed);
    void motionStop(void);


#endif // _MOTOR_H_