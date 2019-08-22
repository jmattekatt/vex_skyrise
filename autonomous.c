// Autonomous code for Vex Skyrise 2014-2015
// Author: Joe Mattekatt

#define PROGRAMMING_SKILLS  1900
#define RED_SKYRISE         900
#define BLUE_SKYRISE        2900
#define RED_CUBE            3500
#define BLUE_CUBE           100
#define RANGE               400

#define DRIVE_TIMEOUT_MS  5000
#define LIFT_TIMEOUT_MS   3000
#define INTAKE_TIMEOUT_MS 5000

#define WAIT_250_MS   250
#define WAIT_500_MS   500
#define WAIT_750_MS   750
#define WAIT_1000_MS  1000
#define WAIT_1500_MS  1500
#define WAIT_2000_MS  2000

#define OPEN_CLAW   SensorValue[Claw] = 1
#define CLOSE_CLAW  SensorValue[Claw] = 0

void SkyriseSequence(int height, int inbetweenWait, int minHeight, word direction) {
  CLOSE_CLAW;
  wait1Msec(inbetweenWait);

  AutoLift(height, LIFT_TIMEOUT_MS);
  wait1Msec(inbetweenWait);

  AutoTurn(direction * 900, DRIVE_TIMEOUT_MS);
  wait1Msec(inbetweenWait);

  OPEN_CLAW;
  wait1Msec(inbetweenWait);

  AutoTurn(direction * -900, DRIVE_TIMEOUT_MS);
  wait1Msec(inbetweenWait);

  AutoLift(minHeight, LIFT_TIMEOUT_MS);
  wait1Msec(inbetweenWait);
}

void RedSkyriseSequence(int height, int inbetweenWait, int minHeight) {
  SkyriseSequence(height, inbetweenWait, minHeight, 1);
}

void BlueSkyriseSequence(int height, int inbetweenWait, int minHeight) {
  SkyriseSequence(height, inbetweenWait, minHeight, -1);
}

void ProgrammingSkills() {
  //Engage claw
  AutoLift(420, LIFT_TIMEOUT_MS);
  wait1Msec(WAIT_250_MS);

  AutoTurn(-150, DRIVE_TIMEOUT_MS);
  wait1Msec(WAIT_250_MS);

  OPEN_CLAW;
  AutoLift(340, LIFT_TIMEOUT_MS);
  wait1Msec(WAIT_250_MS);

  //Skyrise #1 ------------
  RedSkyriseSequence(420, WAIT_250_MS, 340);
  wait1Msec(WAIT_750_MS);

  //Skyrise #2 ------------
  RedSkyriseSequence(440, WAIT_250_MS, 340);
  wait1Msec(WAIT_750_MS);

  //Skyrise #3 ------------
  RedSkyriseSequence(535, WAIT_250_MS, 400);
  wait1Msec(WAIT_750_MS);

  //Skyrise #4 ------------
  RedSkyriseSequence(890, WAIT_250_MS, 400);
  wait1Msec(WAIT_750_MS);

  //Skyrise #5 ------------
  RedSkyriseSequence(1220, WAIT_250_MS, 400);
  wait1Msec(WAIT_750_MS);

  //Skyrise #6 ------------
  RedSkyriseSequence(1550, WAIT_500_MS, 400);
  wait1Msec(WAIT_750_MS);

  //Skyrise #7 ------------
  RedSkyriseSequence(2080, WAIT_500_MS, 400);
  wait1Msec(WAIT_750_MS);
}

void RedSkyriseTile() {
  //Engage claw
  AutoLift(420, LIFT_TIMEOUT_MS);
  wait1Msec(WAIT_250_MS);

  AutoTurn(-150, DRIVE_TIMEOUT_MS);
  wait1Msec(WAIT_250_MS);

  OPEN_CLAW;
  AutoLift(340, LIFT_TIMEOUT_MS);
  wait1Msec(WAIT_250_MS);

  //Skyrise #1 ------------
  RedSkyriseSequence(420, WAIT_250_MS, 340);
  wait1Msec(WAIT_750_MS);

  //Skyrise #2 ------------
  RedSkyriseSequence(440, WAIT_250_MS, 340);
  wait1Msec(WAIT_750_MS);

  //Skyrise #3 ------------
  RedSkyriseSequence(535, WAIT_250_MS, 400);
  wait1Msec(WAIT_750_MS);
}

void BlueSkyriseTile() {
  //Engage claw
  AutoLift(420, LIFT_TIMEOUT_MS);
  wait1Msec(WAIT_250_MS);

  AutoTurn(150, DRIVE_TIMEOUT_MS);
  wait1Msec(WAIT_250_MS);

  OPEN_CLAW;
  AutoLift(340, LIFT_TIMEOUT_MS);
  wait1Msec(WAIT_250_MS);

  //Skyrise #1 ------------
  BlueSkyriseSequence(420, WAIT_250_MS, 340);
  wait1Msec(WAIT_750_MS);

  //Skyrise #2 ------------
  BlueSkyriseSequence(440, WAIT_250_MS, 340);
  wait1Msec(WAIT_750_MS);

  //Skyrise #3 ------------
  BlueSkyriseSequence(535, WAIT_250_MS, 400);
  wait1Msec(WAIT_750_MS);
}

void RedCubeTile() {
  SensorValue[Turntable] = 1;
  AutoDrive(450, DRIVE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoIntake(500, INTAKE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoLift(2640, LIFT_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoTurn(-450, DRIVE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoDrive(80, DRIVE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoIntake(-900, INTAKE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoDrive(-620, DRIVE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoLift(1700, LIFT_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);
}

void BlueCubeTile() {
  SensorValue[Turntable] = 1;
  AutoDrive(450, DRIVE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoIntake(500, INTAKE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoLift(2640, LIFT_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoTurn(450, DRIVE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoDrive(80, DRIVE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoIntake(-900, INTAKE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoDrive(-620, DRIVE_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);

  AutoLift(1700, LIFT_TIMEOUT_MS);
  wait1Msec(WAIT_500_MS);
}

void ChooseAutoRoutine() {
  if (abs(SensorValue[autonChoose] - PROGRAMMING_SKILLS) < RANGE) {
    ProgrammingSkills();

  } else if (abs(SensorValue[autonChoose] - RED_SKYRISE) < RANGE) {
    RedSkyriseTile();

  } else if (abs(SensorValue[autonChoose] - BLUE_SKYRISE) < RANGE) {
    BlueSkyriseTile();

  } else if (SensorValue[autonChoose] < BLUE_CUBE) {
    RedCubeTile();

  } else if (SensorValue[autonChoose] > RED_CUBE) {
    BlueCubeTile();
  }
}
