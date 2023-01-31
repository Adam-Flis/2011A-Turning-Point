#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/skills.hpp"

void skills(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 45, 190, 5000); //Grab ball and flip 1st cap
  delay(350);
  drive("forwards", 18, 140, 2500);
  delay(100);
  swing(-1300, -130, 0, 0, 1300); //Swing towards cap and align on platform
  //Deploy arm
  flipCapAutonomous();
  delay(150);
  drive("forwards", 10.8, 80, 1500); //Drive towards 2nd cap
  delay(100);
  flipCapAutonomous(); //Flip 2nd cap
  drive("backwards", 14, 80, 1100); //Align on platform
  drive("forwards", 6.5, 70, 1500); //Drive away from platform
  delay(100);
  drive("turn_left", 90, 100, 1500); //Turn towards wall
  delay(100);
  drive("backwards", 40, 180, 4000); //Drive towards wall
  delay(100);
  drive("turn_left", 90, 100, 1000); //Turn at 1st set of flags
  delay(100);
  drive("forwards", 55.9, 170, 9000); //Drive towards 1st set of flags
  drive("turn_right", 90, 100, 1000); //Turn at wall
  Ball_Intake.move_velocity(0);
  drive("backwards", 30, 100, 1200); //Align on wall
  drive("forwards", 5.8, 100, 2000); //Off the wall
  delay(200);
  drive("turn_left", 90, 90, 1000); //Turn at flags
  delay(350);
  launchCatapult(); //Launch balls at 1st set of flags
  //reloadCatapult();
  Ball_Intake.move_velocity(200);
  drive("turn_left", 8, 80, 1000); //Turn for 1st bottom flag
  flagHeight();
  drive("forwards", 37.3, 200, 2000); //Flip 1st bottom flag
  delay(100);
  drive("backwards", 12, 180, 1500); //Drive away from 1st bottom flag
  armDown(270, 200, 500); //Bring arm down
  resetSensors();
  delay(200);
  drive("turn_right", 95, 100, 1000); //Turn towards 3rd cap
  delay(100);
  drive("forwards", 4, 140, 1500); //Drive towards 3rd cap
  flipCapAutonomous(); //Flip 3rd cap
  drive("backwards", 8, 140, 2000); //Drive towards wall
  Ball_Intake.move_velocity(0);
  drive("backwards", 30, 80, 1000); //Align on wall
  Ball_Intake.move_velocity(180);
  drive("forwards", 6, 100, 1500); //Drive away from wall
  delay(100);
  drive("turn_left", 90, 100, 1000); //Turn away from wall
  delay(100);
  drive("backwards", 20, 160, 1500); //Drive back from wall
  delay(100);
  drive("turn_right", 90, 100, 1000); //Turn at wall
  delay(100);
  drive("backwards", 20, 60, 1200); //Align on wall
  drive("forwards", 12, 130, 1500); //Drive away from wall
  delay(100);
  drive("turn_right", 180, 90, 2500); //Turn at cap
  delay(100);
  drive("backwards", 40, 200, 2500); //Drive towards 4th cap and grab ball
  delay(350);
  drive("turn_right", 50, 100, 1000); //Turn for shot
  drive("forwards", 3.8, 140, 1200);
  drive("turn_right", 40, 100, 1000);
  delay(100);
  Ball_Intake.move_velocity(0);
  Left_Front_Drive.set_current_limit(150);
  Left_Back_Drive.set_current_limit(150);
  Right_Front_Drive.set_current_limit(150);
  Right_Back_Drive.set_current_limit(150);
  drive("backwards", 15, 60, 1200); //Align on platform
  Left_Front_Drive.set_current_limit(100000);
  Left_Back_Drive.set_current_limit(100000);
  Right_Front_Drive.set_current_limit(100000);
  Right_Back_Drive.set_current_limit(100000);
  drive("forwards", 6, 120, 700); //Drive to flags
  delay(350);
  launchCatapult(); //Launch balls at 2nd set of flags
  //reloadCatapult();
  flagHeight();
  Ball_Intake.move_velocity(200);
  drive("forwards", 40, 200, 2000); //Flip 2nd bottom flag
  armDown(270, 200, 500);
  resetSensors();
  delay(200);
  drive("backwards", 18, 180, 2500); //Drive away from 2nd bottom flag
  drive("turn_right", 92, 100, 2500); //new
  drive("forwards", 50, 200, 2000); //Drive towards 5th cap
  delay(150);
  flipCapAutonomous();
  drive("turn_left", 90, 80, 1500);
  flagHeight();
  drive("forwards", 12, 170, 2000); //Flip 3rd bottom flag
  delay(100);
  drive("backwards", 36, 180, 2000);
  armDown(270, 200, 500); //Bring arm down-
  resetSensors();
  delay(200);
  drive("turn_left", 90, 80, 2000); //end of new
  drive("backwards", 40, 160, 1100); //Drive back to wall
  drive("forwards", 12, 110, 1000); //Drive away from wall
  delay(100);
  drive("turn_left", 90, 100, 1000); //Turn away from wall
  delay(100);
  drive("forwards", 29.5, 180, 2000); //Back to platform
  delay(100);
  drive("turn_right", 90, 100, 2000); //Turn towards wall
  delay(100);
  drive("backwards", 24, 110, 1200); //Align on wall
  drive("forwards", 8, 80, 2000); //Drive off wall
  delay(100);
  drive("turn_left", 180, 90, 3000); //Turn around to face platfrom
  //Drive up platform
  driveHold();
  driveSet(-200, -200);
  delay(3000);
  driveSet(0,0);
  Ball_Intake.move_velocity(0);
/*  drive("backwards", 20, 80, 2000); //Align on platform
  drive("forwards", 8, 100, 1000); //Drive away from platform
  delay(100);
  drive("turn_right", 90, 100, 2000); //Turn at wall
  delay(100);
  drive("backwards", 72, 180, 3000); //Drive back to wall
  drive("forwards", 12, 100, 1000); //Drive away from wall
  delay(100);
  drive("turn_left", 90, 100, 1000); //Turn away from wall
  delay(100);
  drive("backwards", 32, 180, 3000); //Back to platform
  delay(100);
  drive("turn_right", 90, 100, 2000); //Turn towards wall
  delay(100);
  drive("backwards", 24, 100, 1500); //Align on wall
  drive("forwards", 8, 60, 2000); //Drive off wall
  delay(100);
  drive("turn_left", 180, 100, 3000); //Turn around to face platfrom
  //Drive up platform
  driveHold();
  driveSet(-200, -200);
  delay(2750);
  driveSet(0,0);
  Ball_Intake.move_velocity(0); */
}
