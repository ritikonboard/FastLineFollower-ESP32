#include "ui.h"

//   UI:   User Interface related functions

void waitForSwitchPress(int switchNumber, bool promptLoop)
{
    DUMP_UI_abc("\r\n Waiting for Switch No: ", switchNumber, " to be pressed ....");
    switch(switchNumber)
    {
        case SWITCH_TOP:

            while( digitalRead(SWITCH_TOP_PIN_NO) == HIGH)
            {
                if(promptLoop)
                {
                    DUMP_L1_a("\r\n Waiting for SWITCH_TOP press:");
                    delay(250);
                }
            }
            DUMP_UI_a("\r\n SWITCH_TOP: PRESSED, wait over.");
            beep(1, 800);

        break;
    
        case SWITCH_MIDDLE:

            while( digitalRead(SWITCH_MIDDLE_PIN_NO) == HIGH)
            {
                if(promptLoop)
                {
                    DUMP_L1_a("\r\n Waiting for SWITCH_MIDDLE press:");
                    delay(250);
                }
            }
            DUMP_UI_a("\r\n SWITCH_MIDDLE: PRESSED, wait over.");
            beep(1, 800);


        break;
    
        case SWITCH_BOTTOM:

            while( digitalRead(SWITCH_BOTTOM_PIN_NO) == HIGH)
            {
                if(promptLoop)
                {
                    DUMP_L1_a("\r\n Waiting for SWITCH_BOTTOM press:");
                    delay(250);
                }
            }
            DUMP_UI_a("\r\n SWITCH_BOTTOM: PRESSED, wait over.");
            beep(1, 800);


        break;    
    }


}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
