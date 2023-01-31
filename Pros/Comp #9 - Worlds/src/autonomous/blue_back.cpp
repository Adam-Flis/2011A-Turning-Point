#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/blue_back.hpp"

void blue_back(){
  

}

void blue_back_no_shoot(){
  Ball_Intake.move_velocity(200);
  driveBackwardsArm(39, 180, 2000); //Grab ball and drop cap
  Cap_Stacker.move_velocity(-200);
  delay(500);
  Cap_Stacker.move_velocity(0);
  drive("turn_right", 90, 100, 1000); //turn at cap
  delay(200);
  drive("forwards", 14, 150, 2000); //drive to cap
  flagHeight(); //flip cap
  delay(200);
  drive("backwards", 2, 180, 1000);
  drive("turn_right", 87, 100, 1500); //turn to pole
  armDown(270, 200, 500); //lower arm
  drive("backwards", 10, 170, 1500); //drive to pole
  drive("turn_left", 110, 100, 1500); //turn at pole
  Ball_Intake.move_velocity(0);
  driveSet(-200,-200); //Drive up platform
  delay(1450);
  driveHold();
  driveSet(0,0);
}
