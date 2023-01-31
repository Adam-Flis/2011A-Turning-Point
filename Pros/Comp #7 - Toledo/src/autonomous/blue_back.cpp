#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/blue_back.hpp"

void blue_back_main(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 39, 180, 2000); //Grab ball and flip cap
  delay(500);
  drive("forwards", 12, 100, 2500);
  delay(100);
  swing(0, 0, -1300, -130, 1300); //Swing towards cap and align on platform
  Ball_Intake.move_velocity(0);
  flipCapAutonomous(); //Deploy arm
  delay(400);
  flipCapAutonomous();
  delay(400);
  drive("forwards", 15, 140, 2000); //Drive towards cap
  delay(100);
  flipCapAutonomous(); //Flip 2nd cap
  delay(100);
  swing(0, 0, -60, -50, 400); //Swing towards platform
  delay(200);
  driveSet(-200,-200); //Drive up platform
  delay(1600);
  driveHold();
  driveSet(0,0);
}

void blue_back_combo(){
Ball_Intake.move_velocity(200);
drive("backwards", 39, 180, 2000); //Grab ball and flip cap
delay(500);
drive("forwards", 39, 180, 2000);
drive("turn_left", 90, 140, 1500);
delay(400);
drive("forwards", 25, 160, 1500);
delay(400);
launchCatapult();
reloadCatapult();
flagHeight();
drive("forwards", 28, 180, 1500);
armDown(270, 200, 500);
drive("backwards", 30, 180, 1500);
drive("turn_right", 90, 140, 1500);
driveSet(-200,-200); //Drive up platform
delay(1600);
driveHold();
driveSet(0,0);
}

void blue_back_across(){
delay(5000);
launchCatapult();
drive("turn_right", 105, 140, 1500);
Ball_Intake.move_velocity(200);
drive("backwards", 39, 180, 2000); //Grab ball and flip cap
delay(500);
drive("forwards", 12, 180, 2000);
drive("turn_right", 90, 140, 1500);
driveSet(-200,-200); //Drive up platform
delay(1600);
driveHold();
driveSet(0,0);
}
