// General Functions for Vex Skyrise 2014-2015
// Author: Joe Mattekatt

// Common defines
#define ACTIVE   1
#define INACTIVE 0
#define PRESSED  1
#define RELEASED 0

#define FULL_SPEED_FORWARD -127
#define FULL_SPEED_BACKWARD 127
#define HARD_STOP           0
#define RESET_VALUE         0

#define CHECK_TIMEOUT(timeOut) if(time1[T1] > timeOut){break;}
#define LOOP_DELAY wait1Msec(5)

typedef struct _ToggleButton{
  TVexJoysticks button;
  char wasPressed;
  char state;
} ToggleButton;

typedef struct _ToggleActuator{
  ToggleButton togButton;
  tSensors actuator;
} ToggleActuator;

void ToggleButtonInit(ToggleButton &obj, TVexJoysticks button) {
  obj.button = button;
  obj.wasPressed = RELEASED;
  obj.state = INACTIVE;
}

void ToggleActuatorInit(ToggleActuator &obj, TVexJoysticks button, tSensors actuator) {
  ToggleButtonInit(obj.togButton, button);
  obj.actuator = actuator;
}

void ToggleButtonUpdate(ToggleButton &obj) {
  if(vexRT[obj.button] == PRESSED)
    obj.wasPressed = PRESSED;
  else if(vexRT[obj.button] == RELEASED && obj.wasPressed == PRESSED){
    obj.wasPressed = RELEASED;
    if (obj.state == ACTIVE) {
      obj.state = INACTIVE;
    } else {
      obj.state = ACTIVE;
    }
  }
}

void ToggleActuatorUpdate(ToggleActuator &obj) {
  ToggleButtonUpdate(obj.togButton);
  SensorValue[obj.actuator] = obj.togButton.state;
}

void DisplayRow(char row, const string formatString, int leftValue, int rightValue) {
  string displayString;
  sprintf(displayString, formatString, leftValue, rightValue);

  displayLCDString(row, 0, "");
  displayNextLCDString(displayString);
}

void DisplayBatteryLevels() {
  DisplayRow(0, "%1.2fV %1.2fV", nImmediateBatteryLevel/1000.0, BackupBatteryLevel/1000.0);
}

typedef struct _PIErrors {
  int error;
  int integralError;
} PIErrors;

typedef struct _PICoefficients {
  float proportionalCoeff;
  float integralCoeff;
} PICoefficients;

void PIErrorsInit(PIErrors &errors) {
  errors.error = RESET_VALUE;
  errors.integralError = RESET_VALUE;
}

void PIErrorCalculator(int desiredValue, int currentValue, PIErrors &errors) {
  errors.error = desiredValue - currentValue;
  errors.integralError = errors.integralError + errors.error;
}

float PICalculator(const PIErrors &errors, const PICoefficients &coefficients) {
  return coefficients.proportionalCoeff * errors.error + coefficients.integralCoeff * errors.integralError;
}
