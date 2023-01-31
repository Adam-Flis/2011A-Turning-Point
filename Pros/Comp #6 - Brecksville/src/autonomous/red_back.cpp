#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/red_back.hpp"

void red_back(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 39, 180, 2000); //Grab ball and flip cap
  delay(500);
  drive("forwards", 12, 100, 2500);
  delay(100);
  swing(-1300, -130, 0, 0, 1300); //Swing towards cap and align on platform
  Ball_Intake.move_velocity(0);
  flipCapAuto(); //Deploy arm
  delay(400);
  flipCapAuto();
  delay(400);
  drive("forwards", 15, 140, 2000); //Drive towards cap
  delay(100);
  flipCapAuto(); //Flip 2nd cap
  delay(100);
  swing(-60, -50, 0, 0, 400); //Swing towards platform
  delay(200);
  driveSet(-200,-200); //Drive up platform
  delay(1600);
  driveHold();
  driveSet(0,0);
}
