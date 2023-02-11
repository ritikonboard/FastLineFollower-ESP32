#ifndef _UI_H_
    #define _UI_H_ //   UI:   User Interface related functions

    #include "hal.h"
    #include "debug.h"
    #include "motor.h"
    #include "QTRSensors.h"
    #include "battery.h"
    #include "utils.h"

    #define SWITCH_TOP    1
    #define SWITCH_MIDDLE 2
    #define SWITCH_BOTTOM 3

    void waitForSwitchPress(int switchNumber, bool promptLoop);

#endif // _UI_H_