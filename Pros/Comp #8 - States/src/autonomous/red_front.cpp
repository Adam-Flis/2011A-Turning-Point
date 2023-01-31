#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/red_front.hpp"

void red_front_main(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 38, 170, 2000); //Grab ball and flip 1st cap
  delay(500);
  drive("forwards", 32, 170, 2000); //Drive back to starting tile
  delay(200);
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
  drive("turn_right", 90, 100, 1000); //Turn towards 2nd cap
  delay(100);
  drive("forwards", 5, 80, 1000);
  delay(200);
  flipCapAutonomous(); //Flip 2nd cap
  drive("turn_left", 27, 100, 1000); //Turn towards bottom flag
  flagHeight();
  delay(1000);
  drive("forwards", 39, 180, 4000); //Flip 2nd bottom flag
}

void red_front_HI(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 38, 170, 2000); //Grab ball and flip cap
  drive("turn_right", 90, 100, 1000); //Turn to open space
  drive("forwards", 20, 170, 2000); //Drive to open space
  drive("turn_right", 90, 100, 1500); //Turn to say hi
  drive("forwards", 58, 180, 2000); //HIIIIIIIIIII!!!!!!!
  driveSet(0,0); //Hold hi
}
