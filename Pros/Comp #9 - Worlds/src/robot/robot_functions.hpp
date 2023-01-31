#include "main.h"

const string forwards = "forwards";
const string backwards = "backwards";
const string turn_left = "turn_left";
const string turn_right = "turn_right";

//Conversion Functions
int inchToTicks(float inch);

//Reset Functions
void resetSensors();
void resetGyro();
void resetDrive();
void resetLeftDrive();
void resetRightDrive();

//Drive Set Functions
void driveSet(int leftVelocity, int rightVelocity);
void driveSetCurrent(int leftCurrent, int rightCurrent);

//Absolute Value Functions
int leftSideSum();
int rightSideSum();

//Breaking Functions
void driveBrake();
void driveCoast();
void driveHold();

//Drive Functions
void drive(std::string direction, float target, int velocity, int time);
void swing(int sensor_left, int velocity_left, int sensor_right, int velocity_right, int time);
void driveBackwardsArm(float target, int velocity, int time);
void drivePlatform(int platform_count);

//Ball Functions
void upBalls(int sensor, int velocity, int time); //Input motor value for sensor
void downBalls(int sensor, int velocity, int time); //Input motor value for sensor

//Catapult Functions
void shootLastSecond();
void launchCatapult();

//Rake Functions
void rakePot(int sensor, int time); //Input Potentiometer value for sensor
void rakeBall();
void rakeUp(int sensor, int velocity, int time); //Input motor value for sensor
void rakeDown(int sensor, int velocity, int time); //Input motor value for sensor

//Arm Functions
void armUp(int sensor, int velocity, int time); //Input Potentiometer value for sensor
void armDown(int sensor, int velocity, int time); //Input Potentiometer value for sensor
void flipCap();
void flipCapAutonomous();
void flagHeight();
