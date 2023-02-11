#ifndef _DEBUG_H_
    #define _DEBUG_H_

    //#include <Serial.h>
    #define PRINT true
    #define NO_PRINT false

    #define BAUD_RATE  115200
    //#define BAUD_RATE  128000

    #define DEBUG_L1            1  // ALWAYS 1 : IMPORTANT MESSAGES
    #define DEBUG_L2            1  // More details: NOT so important messages
    #define DEBUG_SENSOR_ARRAY  1  // Do you want to debug / display Sensor array values
    #define DEBUG_MOTORS        1  // Do you want to debug  MOTOR related functions
    #define DEBUG_UI            1  // Do you want to debug  User Interface (Switches etc.) related functions


    #ifdef DEBUG_L1
        #define  DUMP_L1_a(a)          { Serial.print(a); Serial1.print(a); }
        #define  DUMP_L1_ab(a,b)       { Serial.print(a); Serial.print(b); Serial1.print(a); Serial1.print(b); }
        #define  DUMP_L1_abc(a,b,c)    { Serial.print(a); Serial.print(b); Serial.print(c); Serial1.print(a); Serial1.print(b); Serial1.print(c);  }
        #define  DUMP_L1_abcd(a,b,c,d) { Serial.print(a); Serial.print(b); Serial.print(c); Serial.print(d); Serial1.print(a); Serial1.print(b); Serial1.print(c); Serial1.print(d); }
        #define  DUMP_L1_aBIN(a,b)     { Serial.print(a); Serial.print(b, BIN); Serial1.print(a); Serial1.print(b, BIN); }
    #else
        #define  DUMP_L1_a(a)          { ; }
        #define  DUMP_L1_ab(a,b)       { ; }
        #define  DUMP_L1_abc(a,b,c)    { ; }
        #define  DUMP_L1_abcd(a,b,c,d) { ; }
        #define  DUMP_L1_aBIN(a,b)     { ; }
    #endif

    #ifdef DEBUG_L2
        #define  DUMP_L2_a(a)          { Serial.print(a); Serial1.print(a); }
        #define  DUMP_L2_ab(a,b)       { Serial.print(a); Serial.print(b); Serial1.print(a); Serial1.print(b); }
        #define  DUMP_L2_abc(a,b,c)    { Serial.print(a); Serial.print(b); Serial.print(c); Serial1.print(a); Serial1.print(b); Serial1.print(c);  }
        #define  DUMP_L2_abcd(a,b,c,d) { Serial.print(a); Serial.print(b); Serial.print(c); Serial.print(d); Serial1.print(a); Serial1.print(b); Serial1.print(c); Serial1.print(d); }
        #define  DUMP_L2_aBIN(a,b)     { Serial.print(a); Serial.print(b, BIN); Serial1.print(a); Serial1.print(b, BIN); }
    #else
        #define  DUMP_L2_a(a)          { ; }
        #define  DUMP_L2_ab(a,b)       { ; }
        #define  DUMP_L2_abc(a,b,c)    { ; }
        #define  DUMP_L2_abcd(a,b,c,d) { ; }
        #define  DUMP_L2_aBIN(a,b)     { ; }
    #endif

    #ifdef DEBUG_SENSOR_ARRAY
        #define  DUMP_SA_a(a)          { Serial.print(a); Serial1.print(a); }
        #define  DUMP_SA_ab(a,b)       { Serial.print(a); Serial.print(b); Serial1.print(a); Serial1.print(b); }
        #define  DUMP_SA_abc(a,b,c)    { Serial.print(a); Serial.print(b); Serial.print(c); Serial1.print(a); Serial1.print(b); Serial1.print(c);  }
        #define  DUMP_SA_abcd(a,b,c,d) { Serial.print(a); Serial.print(b); Serial.print(c); Serial.print(d); Serial1.print(a); Serial1.print(b); Serial1.print(c); Serial1.print(d); }
        #define  DUMP_SA_aBIN(a,b)     { Serial.print(a); Serial.print(b, BIN); Serial1.print(a); Serial1.print(b, BIN); }
    #else
        #define  DUMP_SA_a(a)          { ; }
        #define  DUMP_SA_ab(a,b)       { ; }
        #define  DUMP_SA_abc(a,b,c)    { ; }
        #define  DUMP_SA_abcd(a,b,c,d) { ; }
        #define  DUMP_SA_aBIN(a,b)     { ; }
    #endif

    #ifdef DEBUG_MOTORS
        #define  DUMP_MO_a(a)          { Serial.print(a); Serial1.print(a); }
        #define  DUMP_MO_ab(a,b)       { Serial.print(a); Serial.print(b); Serial1.print(a); Serial1.print(b); }
        #define  DUMP_MO_abc(a,b,c)    { Serial.print(a); Serial.print(b); Serial.print(c); Serial1.print(a); Serial1.print(b); Serial1.print(c);  }
        #define  DUMP_MO_abcd(a,b,c,d) { Serial.print(a); Serial.print(b); Serial.print(c); Serial.print(d); Serial1.print(a); Serial1.print(b); Serial1.print(c); Serial1.print(d); }
        #define  DUMP_MO_aBIN(a,b)     { Serial.print(a); Serial.print(b, BIN); Serial1.print(a); Serial1.print(b, BIN); }
    #else             
        #define  DUMP_MO_a(a)          { ; }
        #define  DUMP_MO_ab(a,b)       { ; }
        #define  DUMP_MO_abc(a,b,c)    { ; }
        #define  DUMP_MO_abcd(a,b,c,d) { ; }
        #define  DUMP_MO_aBIN(a,b)     { ; }
    #endif

    #ifdef DEBUG_UI
        #define  DUMP_UI_a(a)          { Serial.print(a); Serial1.print(a); }
        #define  DUMP_UI_ab(a,b)       { Serial.print(a); Serial.print(b); Serial1.print(a); Serial1.print(b); }
        #define  DUMP_UI_abc(a,b,c)    { Serial.print(a); Serial.print(b); Serial.print(c); Serial1.print(a); Serial1.print(b); Serial1.print(c);  }
        #define  DUMP_UI_abcd(a,b,c,d) { Serial.print(a); Serial.print(b); Serial.print(c); Serial.print(d); Serial1.print(a); Serial1.print(b); Serial1.print(c); Serial1.print(d); }
        #define  DUMP_UI_aBIN(a,b)     { Serial.print(a); Serial.print(b, BIN); Serial1.print(a); Serial1.print(b, BIN); }
    #else             
        #define  DUMP_UI_a(a)          { ; }
        #define  DUMP_UI_ab(a,b)       { ; }
        #define  DUMP_UI_abc(a,b,c)    { ; }
        #define  DUMP_UI_abcd(a,b,c,d) { ; }
        #define  DUMP_UI_aBIN(a,b)     { ; }
    #endif


#endif // _DEBUG_H_