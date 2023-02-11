#include "hal.h"

void init_GPIO(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_SUCCESS_PIN_NO, OUTPUT);
  pinMode(BUZZER_PIN_NO, OUTPUT);

  pinMode(SWITCH_TOP_PIN_NO,    INPUT_PULLUP);
  pinMode(SWITCH_MIDDLE_PIN_NO, INPUT_PULLUP);
  pinMode(SWITCH_BOTTOM_PIN_NO, INPUT_PULLUP);

  pinMode(MOTOR_LEFT_A_PIN_NO,   OUTPUT);
  pinMode(MOTOR_LEFT_B_PIN_NO,   OUTPUT);

  pinMode(MOTOR_STANDBY_PIN_NO,  OUTPUT);

  pinMode(MOTOR_RIGHT_A_PIN_NO,  OUTPUT);
  pinMode(MOTOR_RIGHT_B_PIN_NO,  OUTPUT);

  pinMode(IR_LEFT_PIN_NO , INPUT);
  pinMode(IR_RIGHT_PIN_NO, INPUT);

  pinMode(IR_ON_PIN_NO, OUTPUT); // Control Pin

  // Not required to make input: Why ?!?! Think!
  // pinMode(IR_D......_PIN_NO, INPUT);


  pinMode(BATTERY_VOLTAGE_CHECK_PIN_NO, INPUT);

  analogReadResolution(ANALOG_READ_RESOLUTION);   // For Battery Voltage Check

  analogWriteResolution(ANALOG_WRITE_RESOLUTION); // For Motor PWM : DO NOT CHANGE
  //analogWriteResolution(8); // For Motor PWM 2^8 is 0 to 255

  //#ifdef DEBUG_L1 || DEBUG_L2
      Serial.begin(BAUD_RATE);
  //#endif

  //#ifdef DEBUG_L1 || DEBUG_L2 || DEBUG_SENSOR_ARRAY
      Serial1.begin(BAUD_RATE);
  //#endif

  blink_n_beep(3, 500);

  DUMP_L1_a("\r\n========= RESET =========");

}