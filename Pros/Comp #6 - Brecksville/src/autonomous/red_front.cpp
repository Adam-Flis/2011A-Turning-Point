#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/red_front.hpp"

void red_front(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 38, 170, 2000); //Grab ball and flip cap
  delay(500);
  drive("forwards", 35, 170, 2000); //Drive back to starting tile
  delay(100);
  drive("turn_right", 92.5, 100, 2500); //Turn towards flags
  delay(300);
  Ball_Intake.move_velocity(0);
  launchCatapult(); //Launch balls at flags
  flagHeight();
  delay(100);
  drive("forwards", 40, 180, 2500); //Flip 1st bottom flags
  delay(100);
  drive("backwards", 18, 100, 1000); //Drive back to 2nd cap
  delay(100);
  armDown(270, 200, 500);
  resetSensors();
  flipCapAuto(); //Deploy arm
  drive("turn_right", 80, 120, 1000); //Turn towards 2nd cap
  delay(100);
  drive("forwards", 5, 80, 1000);
  delay(200);
  flipCapAuto(); //Flip 2nd cap
  drive("turn_left", 27, 100, 1000); //Turn towards bottom flag
  delay(100);
  flagHeight();
  delay(1000);
  drive("forwards", 37, 180, 4000); //Flip 2nd bottom flag
}
