#include "main.h"

const string forwards = "forwards";
const string backwards = "backwards";
const string turn_left = "turn_left";
const string turn_right = "turn_right";

//Math Functions
int inchToTicks(float inch);
int degreesToTicks(float degrees);

//Helper Functions
void resetSensors();
void resetDrive();
void resetLeft();
void resetRight();
void driveSet(int leftVelocity, int rightVelocity);
int leftSideSum();
int rightSideSum();

//Breaking Functions
void driveBrake();
void driveCoast();
void driveHold();

//Drive Functions
void drive(std::string direction, float target, int velocity, int time);
void swing(int sensor_left, int velocity_left, int sensor_right, int velocity_right, int time);
void drivePlatform(int platform_count);

//Ball Functions
void upBalls(int sensor, int velocity, int time);
void downBalls(int sensor, int velocity, int time);

//Catapult Functions
void launchCatapult();
void reloadCatapult();

//Arm functions
void armUp(int sensor, int velocity, int time);
void armDown(int sensor, int velocity, int time);
void flipCap();
void flipCapAutonomous();
void flagHeight();
