// Lift code for Vex Skyrise 2014-2015
// Author: Joe Mattekatt

#define LOW_SPEED_FORWARD  -40
#define LOW_SPEED_BACKWARD 40
#define LIFT_HOLD_SPEED    -10

#define FAST_LIFT_UP_BUTTON   Btn5U
#define FAST_LIFT_DOWN_BUTTON Btn5D
#define SLOW_LIFT_UP_BUTTON   Btn7U
#define SLOW_LIFT_DOWN_BUTTON Btn7D

#define LEFT_UPPER_LIMIT   3550
#define RIGHT_UPPER_LIMIT  2100
#define LEFT_BOTTOM_LIMIT  1585
#define RIGHT_BOTTOM_LIMIT 350
#define LIFT_STOPPING_DIFF 10


void Lift(word speed) {
  motor[FrontLeftLiftMotor]  = speed;
  motor[BackLeftLiftMotor]   = speed;
  motor[FrontRightLiftMotor] = speed;
  motor[BackRightLiftMotor]  = speed;
}

void JoystickLift() {
  if (vexRT[FAST_LIFT_UP_BUTTON] == PRESSED && vexRT[FAST_LIFT_DOWN_BUTTON] == PRESSED){
    Lift(LIFT_HOLD_SPEED);

  } else if (vexRT[FAST_LIFT_UP_BUTTON] == PRESSED){
    if (SensorValue[LeftPot] < LEFT_UPPER_LIMIT && SensorValue[RightPot] < RIGHT_UPPER_LIMIT) {
      Lift(FULL_SPEED_FORWARD);
    }

  } else if (vexRT[FAST_LIFT_DOWN_BUTTON] == PRESSED){
    if (SensorValue[LeftPot] > LEFT_BOTTOM_LIMIT && SensorValue[RightPot] > RIGHT_BOTTOM_LIMIT) {
      Lift(FULL_SPEED_BACKWARD);
    }

  } else if (vexRT[SLOW_LIFT_UP_BUTTON] == PRESSED){
    Lift(LOW_SPEED_FORWARD);

  } else if (vexRT[SLOW_LIFT_DOWN_BUTTON] == PRESSED){
    Lift(LOW_SPEED_BACKWARD);

  } else{
    Lift(HARD_STOP);
  }
}

void AutoLift (int height, int timeOut) {
  static const PICoefficients coeffs = {0.25, 0.01};

  PIErrors errors;
  PIErrorsInit(errors);

  clearTimer(T1);

  while (abs(SensorValue[RightPot] - height) > LIFT_STOPPING_DIFF) {
    PIErrorCalculator(height, SensorValue[RightPot], errors);
    int speed = PICalculator(errors, coeffs);
    Lift(speed);

    CHECK_TIMEOUT(timeOut);
  }

  Lift(HARD_STOP);
}
