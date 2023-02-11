#include "utils.h"

///////////////////////////////////////////////////////////////////////////////////
void blink(int n, int timePeriod)
{
    while(n > 0)
    {
        digitalWrite(LED_BUILTIN,     HIGH);
        digitalWrite(LED_SUCCESS_PIN_NO, HIGH);
        delay(timePeriod/2);

        digitalWrite(LED_BUILTIN,     LOW );
        digitalWrite(LED_SUCCESS_PIN_NO, LOW );
        delay(timePeriod/2);

        n--;
    }
}
/////////////////////////////////////////////////////////////////////////
void beep(int n, int timePeriod)
{
    while(n > 0)
    {
        digitalWrite(BUZZER_PIN_NO, HIGH);
        delay(timePeriod/2);

        digitalWrite(BUZZER_PIN_NO, LOW);
        delay(timePeriod/2);

        n--;
    }
}
/////////////////////////////////////////////////////////////////////////
void blink_n_beep(int n, int timePeriod)
{
    while(n > 0)
    {
        digitalWrite(LED_BUILTIN,     HIGH);
        digitalWrite(LED_SUCCESS_PIN_NO, HIGH);
        digitalWrite(BUZZER_PIN_NO,      HIGH);
        delay(timePeriod/2);

        digitalWrite(LED_BUILTIN,     LOW );
        digitalWrite(LED_SUCCESS_PIN_NO, LOW );
        digitalWrite(BUZZER_PIN_NO,      LOW );
        delay(timePeriod/2);

        n--;
    }
}
/////////////////////////////////////////////////////////////////////////
void hang(const char* reason)
{
    int t=1000;
    DUMP_L1_a("\r\n\r\n######     HANG     ######\r\n");

    digitalWrite(BUZZER_PIN_NO, HIGH);
    delay(2000);
    digitalWrite(BUZZER_PIN_NO, LOW);

    while(1)
    {
        digitalWrite(LED_BUILTIN,     HIGH);
        digitalWrite(LED_SUCCESS_PIN_NO, LOW );
        delay(200);

        digitalWrite(LED_BUILTIN,     LOW );
        digitalWrite(LED_SUCCESS_PIN_NO, HIGH);
        delay(200);

        if(t%1000==0)
        {
            DUMP_L1_abcd("\r\n\r\n ", t, " HANG: ", reason);
            batteryVoltageCheck(1); // Always Keep this line: 0= No Print, 1 = Print
        }

        t++;
    }
}
/////////////////////////////////////////////////////////////////////////
