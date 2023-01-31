#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/red_front.hpp"

void red_front_main(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 38, 170, 2000); //Grab ball and flip cap
  delay(500);
  drive("forwards", 32, 170, 2000); //Drive back to starting tile
  delay(100);
  drive("turn_right", 90, 100, 2500); //Turn towards flags
  delay(300);
  Ball_Intake.move_velocity(0);
  launchCatapult(); //Launch balls at flags
  flagHeight();
  delay(100);
  drive("forwards", 40, 180, 2500); //Flip 1st bottom flags
  delay(100);
  drive("backwards", 16, 100, 1000); //Drive back to 2nd cap
  delay(100);
  armDown(270, 200, 500);
  resetSensors();
  flipCapAutonomous(); //Deploy arm
  drive("turn_right", 90, 120, 1000); //Turn towards 2nd cap
  delay(100);
  drive("forwards", 5, 80, 1000);
  delay(200);
  flipCapAutonomous(); //Flip 2nd cap
  drive("turn_left", 27, 100, 1000); //Turn towards bottom flag
  flagHeight();
  delay(1000);
  drive("forwards", 38, 180, 4000); //Flip 2nd bottom flag
}

void red_front_combo(){
Ball_Intake.move_velocity(200);
drive("backwards", 38, 170, 2000); //Grab ball and flip cap
delay(500);
drive("forwards", 10, 180, 1500);
drive("turn_right", 90, 140, 1500);
delay(700);
launchCatapult();
reloadCatapult();
flagHeight();
drive("forwards", 28, 180, 1500);
drive("backwards", 12, 180, 1500);
armDown(270, 200, 500);
drive("turn_left", 90, 140, 1500);
flipCapAutonomous();
drive("forwards", 8, 180, 1500);
drive("turn_right", 90, 140, 1500);
driveSet(-200,-200); //Drive up platform
delay(1600);
driveHold();
driveSet(0,0);
}
