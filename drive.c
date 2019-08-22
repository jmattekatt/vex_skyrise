// Drivetrain code for Vex Skyrise 2014-2015
// Author: Joe Mattekatt

#define LEFT_STABLE_HEIGHT  2578
#define RIGHT_STABLE_HEIGHT 1240

#define X_TRANSLATION_CHAN Ch2
#define ROTATION_CHAN      Ch4
#define Y_TRANSLATION_CHAN Ch1


word FilterAnalogChannel(TVexJoysticks channel) {
  // Analog Re-mapping
  static const word driveMap[128] =
  {0,0,0,0,0,0,0,0,0,0,
  20,20,21,21,22,22,23,23,24,24,
  25,25,26,26,27,27,28,28,29,29,
  30,30,31,31,32,32,33,33,34,34,
  35,35,36,36,37,37,38,38,39,39,
  40,40,41,41,42,42,43,43,44,44,
  45,45,46,46,47,47,48,48,49,49,
  50,50,51,51,52,52,53,53,54,54,
  55,55,56,56,57,57,58,58,59,59,
  60,60,61,62,63,64,65,66,67,68,
  69,70,71,72,73,74,75,76,77,78,
  79,80,81,82,83,84,85,86,87,88,
  89,90,91,92,94,96,127,127};

  int filteredValue = driveMap[abs(vexRT[channel])];
  if (vexRT[channel] < 0) {
    return -filteredValue;
  }
  return filteredValue;
}

int SpeedFilter(word speed) {
  if(SensorValue[LeftPot] > LEFT_STABLE_HEIGHT || SensorValue[RightPot] > RIGHT_STABLE_HEIGHT){
    return speed/2;
  }
  return speed;
}

void Drive(word y_translation, word rotate, word x_translation){
  word y_translation_filtered = SpeedFilter(y_translation);

  // Mecanum drive motion equations
  motor[frontRight] = y_translation_filtered - rotate - x_translation;
  motor[backRight]  = y_translation_filtered - rotate + x_translation;
  motor[frontLeft]  = y_translation_filtered + rotate + x_translation;
  motor[backLeft]   = y_translation_filtered + rotate - x_translation;
}

void JoystickDrive() {
  Drive(
    FilterAnalogChannel(Y_TRANSLATION_CHAN),
    FilterAnalogChannel(ROTATION_CHAN),
    FilterAnalogChannel(X_TRANSLATION_CHAN)
  );
}

void EBrake() {
  motor[frontRight] = HARD_STOP;
  motor[backRight]  = HARD_STOP;
  motor[frontLeft]  = HARD_STOP;
  motor[backLeft]   = HARD_STOP;
  wait1Msec(5);
}

void AutoDrive(int steps, int timeOut) {
  static const PICoefficients coeffs = {0.333, 0.005};
  static const float gyroCoeff = 0.5;

  PIErrors rightErrors, leftErrors;
  PIErrorsInit(rightErrors);
  PIErrorsInit(leftErrors);

  //Reset encoders
  SensorValue[FrontRightEnc] = RESET_VALUE;
  SensorValue[BackRightEnc]  = RESET_VALUE;
  SensorValue[FrontLeftEnc]  = RESET_VALUE;
  SensorValue[BackLeftEnc]   = RESET_VALUE;
  SensorValue[Gyro]          = RESET_VALUE;
  clearTimer(T1);

  int absSteps = abs(steps);

  while (abs(SensorValue[BackRightEnc]) < absSteps && abs(SensorValue[BackLeftEnc]) < absSteps) {
    PIErrorCalculator(steps, SensorValue[BackRightEnc], rightErrors);
    PIErrorCalculator(steps, SensorValue[BackLeftEnc], leftErrors);

    int rightSpeed = PICalculator(rightErrors, coeffs) + gyroCoeff*SensorValue[Gyro];
    int leftSpeed = PICalculator(leftErrors, coeffs) - gyroCoeff*SensorValue[Gyro];

    motor[frontRight] = rightSpeed;
    motor[backRight]  = rightSpeed;
    motor[frontLeft]  = leftSpeed;
    motor[backLeft]   = leftSpeed;

    CHECK_TIMEOUT(timeOut);
  }

  EBrake();
}

void AutoTurn(int degrees, int timeOut) {
  static const PICoefficients coeffs = {0.333, 0.004};

  PIErrors errors;
  PIErrorsInit(errors);

  SensorValue[Gyro] = RESET_VALUE;
  clearTimer(T1);

  int absDegrees = abs(degrees);

  while(abs(SensorValue[Gyro]) < absDegrees){
    PIErrorCalculator(degrees, SensorValue[Gyro], errors);
    int speed = PICalculator(errors, coeffs);

    motor[frontRight] = speed;
    motor[backRight]  = speed;
    motor[frontLeft]  = -speed;
    motor[backLeft]   = -speed;

    CHECK_TIMEOUT(timeOut);
  }

  EBrake();
}
