#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/red_back.hpp"

void red_back(){
  delay(7000);
  drive("forwards", 18, 60, 1250);
  delay(300);
  launchCatapult(); //Shoot across field
  drive("backwards", 11, 80, 1100);
  delay(100);
  drive("turn_left", 130, 100, 1100);
  Ball_Intake.move_velocity(200);
  driveBackwardsArm(37, 140, 2000); //Grab ball and drop cap
  Cap_Stacker.move_velocity(-200);
  drive("turn_left", 20, 60, 1000);
  Cap_Stacker.move_velocity(0);
  drive("forwards", 9.3, 130, 1500); //Drive back to platform
  drive("turn_left", 90, 120, 1000);
  Ball_Intake.move_velocity(0);
  driveSet(-200,-200); //Drive up platform
  delay(1250);
  driveHold();
  driveSet(0,0);
}


void red_back_no_shoot(){
  Ball_Intake.move_velocity(200);
  driveBackwardsArm(39, 180, 2000); //Grab ball and drop cap
  Cap_Stacker.move_velocity(-200);
  delay(500);
  Cap_Stacker.move_velocity(0);
  drive("turn_left", 90, 100, 1000); //turn at cap
  delay(200);
  drive("forwards", 14, 150, 2000); //drive to cap
  flagHeight(); //flip cap
  delay(200);
  drive("backwards", 2, 180, 1000);
  drive("turn_left", 87, 100, 1500); //turn to pole
  armDown(270, 200, 500); //lower arm
  drive("backwards", 10, 170, 1500); //drive to pole
  drive("turn_right", 110, 100, 1500); //turn at pole
  Ball_Intake.move_velocity(0);
  driveSet(-200,-200); //Drive up platform
  delay(1450);
  driveHold();
  driveSet(0,0);
}
