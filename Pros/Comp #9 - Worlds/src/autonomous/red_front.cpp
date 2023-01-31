#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/red_front.hpp"

void red_front(){
  Ball_Intake.move_velocity(200);
  driveBackwardsArm(19.95, 200, 1200);
  rakeDown(290, 100, 300); //Get ball off platform
  Rake.move_velocity(-5);
  drive("forwards", 14, 180, 1000);
  Rake.move_velocity(0);
  drive("turn_right", 64, 110, 800); //Turn at flags
  Ball_Intake.move_velocity(0);
  delay(200);
  launchCatapult();
  flagHeight();
  drive("forwards", 42, 200, 1200); //Flip 1st bottom flag
  drive("backwards", 3, 180, 350); //Go back from flag
  armDown(300, 200, 300);
  rakeUp(1100, 200, 400);
  drive("turn_left", 60, 100, 800); //Turn at cap to get Ball
  Ball_Intake.move_velocity(200);
  drive("backwards", 7.8, 160, 750); //Drive at cap
  rakePot(1920, 700); //Get ball off cap
  drive("forwards", 3, 200, 150);
  drive("backwards", 8.3, 180, 300);
  rakeUp(1005, 200, 300); //Flip Cap
  drive("turn_right", 45, 110, 800);
  drive("backwards", 27.75, 180, 1500);
  drive("turn_left", 79, 100, 800);
  delay(50);
  drive("backwards", 30, 180, 1300);
  drive("forwards", 4, 200, 400);
  delay(50);
  drive("turn_right", 114, 150, 900);
  Ball_Intake.move_velocity(0);
  launchCatapult();
}
