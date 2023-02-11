#ifndef _UTILS_H_
    #define _UTILS_H_

    #include "hal.h"
    #include "debug.h"
    #include "motor.h"
    #include "QTRSensors.h"
    #include "battery.h"

    void blink(int n, int timePeriod);
    void beep(int n, int timePeriod);
    void blink_n_beep(int n, int timePeriod);
    void hang(const char* reason);

#endif // _UTILS_H_