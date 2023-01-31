#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/red_back.hpp"

void red_back_main(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 39, 180, 2000); //Grab ball and flip cap
  delay(500);
  drive("forwards", 12, 100, 2500);
  delay(100);
  swing(-1300, -130, 0, 0, 1300); //Swing towards cap and align on platform
  Ball_Intake.move_velocity(0);
  flagHeight(); //Deploy arm
  delay(100);
  drive("forwards", 11.5, 140, 2000); //Drive towards cap
  delay(100);
  armDown(320, 200, 700); //Smack cap
  delay(100);
  flagHeight(); 
  delay(100);
  drive("backwards", 3, 100, 1000);
  armDown(320, 200, 700);
  drive("forwards", 3, 100, 1000);
  flipCapAutonomous(); //Flip 2nd cap
  delay(100);
  drive("turn_left", 18, 30, 1000);
  delay(200);
  driveSet(-200,-200); //Drive up platform
  delay(1600);
  driveHold();
  driveSet(0,0);
}

void red_back_combo(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 39, 180, 2000); //Grab ball and flip cap
  delay(500);
  drive("forwards", 12, 160, 2500);
  delay(100);
  swing(-1300, -130, 0, 0, 1300); //Swing towards cap and align on platform
  Ball_Intake.move_velocity(0);
  flipCapAutonomous(); //Deploy arm
  delay(100);
  drive("forwards", 11, 160, 2000); //Drive towards cap
  delay(100);
  flipCapAutonomous(); //Flip 2nd cap
  drive("turn_left", 45, 110, 1500);
  delay(400);
  drive("backwards",35, 180, 2000);
  drive("turn_left", 100, 110, 1500);
  drive("forwards", 37, 170, 2000);
  drive("turn_right", 90, 80, 1500);
  delay(400);
  drive("forwards", 55, 170, 9000); //Drive towards 1st set of flags
  Ball_Intake.move_velocity(0);
  delay(450);
  launchCatapult(); //Launch balls at 1st set of flags
  reloadCatapult();
  drive("turn_left", 8, 100, 1000); //Turn for 1st bottom flag
  flagHeight();
  drive("forwards", 38, 200, 2000); //Flip 1st bottom flag
  delay(100);
  Ball_Intake.move_velocity(200);
  drive("backwards", 64 , 200, 1500);
  armDown(270, 200, 500); //Bring arm down
  drive("turn_left", 90, 90, 1500);
  driveSet(-200,-200); //Drive up platform
  delay(1600);
  driveHold();
  driveSet(0,0);
  resetSensors();
}

void red_back_across(){
  delay(5000);
  launchCatapult();
  reloadCatapult();
  delay(100);
  drive("turn_left", 120, 100, 2000);
  delay(100);
  Ball_Intake.move_velocity(200);
  drive("backwards", 39, 180, 2000); //Grab ball and flip cap
  delay(500);
  drive("forwards", 5, 80, 2000);
  delay(100);
  drive("turn_left", 90, 100, 1500);
  driveSet(-200,-200); //Drive up platform
  delay(1550);
  driveHold();
  driveSet(0,0);
}
