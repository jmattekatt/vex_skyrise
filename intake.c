// End Effector code for Vex Skyrise 2014-2015
// Author: Joe Mattekatt

#define JOYSTICK_CONTROL ACTIVE
#define RESET_INTAKE     INACTIVE

#define BACKWARD_BUTTON Btn6U
#define FORWARD_BUTTON  Btn6D

#define CUBE_TRIGGER_LIMIT   100
#define INTAKE_ENCODER_LOOP  430
#define INTAKE_ENCODER_LIMIT 15
#define RESET_SPEED_SCALING  0.5


void Intake(word speed) {
  motor[CubeIntakeMotor]  = speed;
  motor[CubeIntakeMotor2] = speed;
}

void JoystickIntake() {
  if(vexRT[BACKWARD_BUTTON] == PRESSED && SensorValue[CubeLimit] > CUBE_TRIGGER_LIMIT) {
    Intake(FULL_SPEED_BACKWARD);
  } else if(vexRT[FORWARD_BUTTON] == PRESSED) {
    Intake(FULL_SPEED_FORWARD);
  } else {
    Intake(HARD_STOP);
  }
}

bool ResetIntake() {
  int position = abs(SensorValue[QuadEncoder]) % INTAKE_ENCODER_LOOP;

  if(position > INTAKE_ENCODER_LIMIT){
    word speed = position * RESET_SPEED_SCALING;

    if(SensorValue[QuadEncoder] > 0) {
      Intake(-speed);
    } else if(SensorValue[QuadEncoder] < 0) {
      Intake(speed);
    }
    return false;
  }
  else {
    Intake(HARD_STOP);
    return true;
  }
}

void IntakeStateMachine(ToggleButton &stateControl) {
  if (stateControl.state == JOYSTICK_CONTROL) {
    JoystickIntake();
  } else if (stateControl.state == RESET_INTAKE) {
    bool resetComplete = ResetIntake();
    if (resetComplete) {
      stateControl.state = JOYSTICK_CONTROL;
    }
  }
}

void AutoIntake(int steps, int timeOut){
  int current = SensorValue[QuadEncoder];
  clearTimer(T1);

  if(steps > 0){
    while(SensorValue[QuadEncoder] < current + steps && SensorValue[CubeLimit] > 100){
      Intake(FULL_SPEED_BACKWARD);
      CHECK_TIMEOUT(timeOut);
    }
  }
  else if(steps < 0){
    while(SensorValue[QuadEncoder] > current + steps){
      Intake(FULL_SPEED_FORWARD);
      CHECK_TIMEOUT(timeOut);
    }
  }
  Intake(HARD_STOP);
}
