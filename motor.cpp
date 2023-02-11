#include "motor.h"

/////////////////////////////////////////////////////////////////////////
void moveMotors(int speedLeft, int speedRight, bool print)
{
    if(print)
        DUMP_L1_abcd(" moveMotors: speedLeft= ", speedLeft, " speedRight= ", speedRight);

    if(speedLeft > 0)
    {
            analogWrite( MOTOR_LEFT_A_PIN_NO, speedLeft );
            pinMode(     MOTOR_LEFT_B_PIN_NO, OUTPUT);
            digitalWrite(MOTOR_LEFT_B_PIN_NO, LOW   );
    }
    else   if(speedLeft < 0)
    {
            pinMode(     MOTOR_LEFT_A_PIN_NO, OUTPUT);
            digitalWrite(MOTOR_LEFT_A_PIN_NO, LOW   );
            analogWrite( MOTOR_LEFT_B_PIN_NO, -speedLeft );
    }
    else // speedLeft is ZERO
    {
            pinMode(     MOTOR_LEFT_A_PIN_NO, OUTPUT);
            digitalWrite(MOTOR_LEFT_A_PIN_NO, LOW);

            pinMode(     MOTOR_LEFT_B_PIN_NO, OUTPUT);
            digitalWrite(MOTOR_LEFT_B_PIN_NO, LOW);
    }


    if(speedRight > 0)
    {
            pinMode(     MOTOR_RIGHT_A_PIN_NO, OUTPUT);
            digitalWrite(MOTOR_RIGHT_A_PIN_NO, LOW   );
            analogWrite( MOTOR_RIGHT_B_PIN_NO, speedRight );
    }
    else if(speedRight < 0)
    {
            analogWrite( MOTOR_RIGHT_A_PIN_NO, -speedRight );
            pinMode(     MOTOR_RIGHT_B_PIN_NO, OUTPUT);
            digitalWrite(MOTOR_RIGHT_B_PIN_NO, LOW   );    
    }
    else // speedRight is ZERO
    {
            pinMode(     MOTOR_RIGHT_A_PIN_NO, OUTPUT);
            digitalWrite(MOTOR_RIGHT_A_PIN_NO, LOW);

            pinMode(     MOTOR_RIGHT_B_PIN_NO, OUTPUT);
            digitalWrite(MOTOR_RIGHT_B_PIN_NO, LOW);    
    }


  if(speedLeft == 0 && speedRight == 0)
      digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_STANDBY);
  else
    digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_ENABLE);
  
}
/////////////////////////////////////////////////////////////////////////
void motionForward(int speed)
{
  analogWrite( MOTOR_LEFT_A_PIN_NO, speed );
  pinMode(     MOTOR_LEFT_B_PIN_NO, OUTPUT);
  digitalWrite(MOTOR_LEFT_B_PIN_NO, LOW   );

  pinMode(     MOTOR_RIGHT_A_PIN_NO, OUTPUT);
  digitalWrite(MOTOR_RIGHT_A_PIN_NO, LOW   );
  analogWrite( MOTOR_RIGHT_B_PIN_NO, speed );

  digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_ENABLE);
}
/////////////////////////////////////////////////////////////////////////
void motionReverse(int speed)
{
  pinMode(     MOTOR_LEFT_A_PIN_NO, OUTPUT);
  digitalWrite(MOTOR_LEFT_A_PIN_NO, LOW   );
  analogWrite( MOTOR_LEFT_B_PIN_NO, speed );

  analogWrite( MOTOR_RIGHT_A_PIN_NO, speed );
  pinMode(     MOTOR_RIGHT_B_PIN_NO, OUTPUT);
  digitalWrite(MOTOR_RIGHT_B_PIN_NO, LOW   );

  digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_ENABLE);
}
/////////////////////////////////////////////////////////////////////////
void motionStop(void)
{
  pinMode(     MOTOR_RIGHT_A_PIN_NO, OUTPUT);
  digitalWrite(MOTOR_RIGHT_A_PIN_NO, LOW);

  pinMode(     MOTOR_RIGHT_B_PIN_NO, OUTPUT);
  digitalWrite(MOTOR_RIGHT_B_PIN_NO, LOW);

  pinMode(     MOTOR_LEFT_A_PIN_NO, OUTPUT);
  digitalWrite(MOTOR_LEFT_A_PIN_NO,  LOW);

  pinMode(     MOTOR_LEFT_B_PIN_NO, OUTPUT);
  digitalWrite(MOTOR_LEFT_B_PIN_NO,  LOW);

  digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_STANDBY);
}
/////////////////////////////////////////////////////////////////////////
