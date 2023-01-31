#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/skills.hpp"

void skills1(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 38, 180, 2000); //Grab ball and flip 1st cap
  delay(500);
  drive("forwards", 12, 130, 1000);
  delay(100);
  drive("turn_left", 90, 100, 1000); //Turn towards 2nd cap
  armUp(300, 200, 600); //Deploy arm
  armDown(300, 200, 600);
  drive("forwards", 8, 120, 1000);
  flipCap(); //Flip 2nd cap
  delay(100);
  drive("backwards", 8, 120, 1000);
  delay(100);
  drive("turn_right", 90, 100, 1000);
  delay(100);
  drive("backwards", 30, 180, 3000); //Align against wall
  drive("forwards", 8, 120, 1000);
  drive("turn_left", 90, 100, 1000); //Turn at flags
  drive("forwards", 40, 180, 2000); //Drive towards flags
  launchCatapult(); //Launch balls at flags
  reloadCatapult();
  flagHeight();
  drive("forwards", 36, 180, 2000); //Flip bottom flag
  delay(100);
  drive("backwards", 12, 150, 1000);
  delay(100);
  drive("turn_left", 45, 100, 1000); //Turn towards 3rd cap
  delay(100);
  drive("forwards", 24, 180, 1500);
  flipCap(); //Flip 3rd cap
  drive("backwards", 30, 180, 3000); //Align against wall
  drive("forwards", 5, 100, 1000);
  delay(100);
  drive("turn_left", 90, 120, 1000);
  delay(100);
  drive("forwards", 10, 120, 1000);
  delay(100);
  drive("turn_right", 90, 120, 1000);
  delay(100);
  drive("backwards", 10, 140, 2000); //Align against wall
  drive("forwards", 12, 100, 1500);
  delay(100);
  drive("turn_left", 180, 100, 2500);
}

void skills2(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 40, 170, 2000); //Grab ball and flip cap
  delay(500);
  drive("forwards", 36, 170, 2000); //Drive back to starting tile
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
  delay(200);
  //Go and park on center platform
  drive("backwards", 24, 100, 1500); //Align on wall
  drive("forwards", 12, 100, 1000);
  delay(100);
  drive("turn_left", 90, 120, 1000);
  delay(100);
  drive("backwards", 43, 180, 3000); //Back to platform
  delay(100);
  drive("turn_right", 90, 100, 2000); //Turn towards platform
  drive("backwards", 24, 100, 1500); //Align on wall
  drive("forwards", 8, 50, 2000);
  drive("turn_left", 180, 70, 3000);
  //Up platform
  driveSet(-200, -200);
  delay(2800);
  driveSet(0,0);
}
