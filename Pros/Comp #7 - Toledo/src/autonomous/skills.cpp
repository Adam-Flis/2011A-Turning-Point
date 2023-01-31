#include "main.h"
#include "../robot/define_items.hpp"
#include "../robot/robot_functions.hpp"
#include "headers/skills.hpp"

void skills_main(){
  Ball_Intake.move_velocity(200);
  drive("backwards", 45, 190, 5000); //Grab ball and flip 1st cap
  delay(350);
  //drive("forwards", 2.5, 70, 1000); //Drive away from cap
  drive("turn_left", 90, 120, 1000); //Turn towards 2nd cap
  drive("backwards", 8.5, 80, 1200); //Align on platform
  //Deploy arm
  flipCapAutonomous();
  delay(150);
  flipCapAutonomous();
  delay(150);
  drive("forwards", 7, 120, 1500); //Drive towards 2nd cap
  delay(100);
  flipCapAutonomous(); //Flip 2nd cap
  drive("backwards", 14, 80, 1100); //Align on platform
  drive("forwards", 5.5, 70, 1500); //Drive away from platform
  delay(100);
  drive("turn_left", 90, 100, 1500); //Turn towards wall
  delay(100);
  drive("backwards", 40, 180, 4000); //Drive towards wall
  delay(100);
  drive("turn_left", 90, 100, 1000); //Turn at 1st set of flags
  delay(100);
  drive("forwards", 55, 150, 9000); //Drive towards 1st set of flags
  drive("turn_right", 90, 100, 1000); //Turn at wall
  Ball_Intake.move_velocity(0);
  drive("backwards", 30, 100, 1500); //Align on wall
  drive("forwards", 5.6, 100, 2000); //Off the wall
  delay(200);
  drive("turn_left", 90, 100, 1000); //Turn at flags
  delay(550);
  launchCatapult(); //Launch balls at 1st set of flags
  reloadCatapult();
  Ball_Intake.move_velocity(200);
  drive("turn_left", 8, 80, 1000); //Turn for 1st bottom flag
  flagHeight();
  drive("forwards", 38, 200, 2000); //Flip 1st bottom flag
  delay(100);
  drive("backwards", 8.3, 160, 1500); //Drive away from 1st bottom flag
  armDown(270, 200, 500); //Bring arm down
  resetSensors();
  drive("turn_right", 95, 120, 1000); //Turn towards 3rd cap
  delay(100);
  drive("forwards", 3.5, 120, 1500); //Drive towards 3rd cap
  flipCapAutonomous(); //Flip 3rd cap
  drive("backwards", 8, 140, 2500); //Drive towards wall
  Ball_Intake.move_velocity(0);
  drive("backwards", 30, 80, 1000); //Align on wall
  Ball_Intake.move_velocity(200);
  drive("forwards", 6, 80, 1500); //Drive away from wall
  delay(100);
  drive("turn_left", 90, 120, 1000); //Turn away from wall
  delay(100);
  drive("backwards", 25.7, 160, 1500); //Drive back from wall
  delay(100);
  drive("turn_right", 90, 120, 1000); //Turn at wall
  delay(100);
  drive("backwards", 20, 60, 1400); //Align on wall
  drive("forwards", 12, 140, 1500); //Drive away from wall
  delay(100);
  drive("turn_right", 180, 120, 2500); //Turn at cap
  delay(100);
  drive("backwards", 42, 200, 2500); //Drive towards 4th cap and grab ball
  delay(350);
  drive("forwards", 4.5, 80, 1500); //Drive back to flags
  delay(100);
  drive("turn_right", 90, 120, 1000); //Turn for shot
  delay(100);
  drive("backwards", 10, 80, 1200); //Align on platform
  drive("forwards", 5, 100, 1000); //Drive to flags
  delay(550);
  Ball_Intake.move_velocity(0);
  launchCatapult(); //Launch balls at 2nd set of flags
  reloadCatapult();
  flagHeight();
  Ball_Intake.move_velocity(200);
  drive("forwards", 39, 200, 2000); //Flip 2nd bottom flag
  armDown(270, 200, 500);
  resetSensors();
  drive("backwards", 25, 180, 2000); //Drive away from 2nd bottom flag
  drive("backwards", 20, 100, 2000); //Align on platform
  drive("forwards", 8, 100, 1000); //Drive away from platform
  delay(100);
  drive("turn_right", 90, 120, 2000); //Turn at wall
  delay(100);
  drive("backwards", 72, 180, 3000); //Drive back to wall
  /*delay(100);
  drive("turn_left", 90, 120, 1000); //Turn towards 5th cap
  delay(100);
  drive("backwards", 42, 200, 8000); //Drive at 5th cap
  delay(100);
  flipCapAutonomous(); //Flip 5th cap
  drive("turn_left", 90, 120, 1000); //Turn towards lineup
  delay(100);
  drive("backwards", 22, 180, 1000); //Drive towards lineup
  delay(100);
  drive("turn_right", 90, 120, 1000); //Turn towards 6th cap
  delay(100);
  drive("backwards", 26, 200, 1000); //Drive towards 6th cap and grab ball
  delay(100);
  drive("forwards", 30, 180, 1000); //Drive towards flags
  delay(100);
  drive("turn_left", 90, 120, 1000); //Turn towards flags
  Ball_Intake.move_velocity(0);
  delay(550);
  launchCatapult(); //Launch balls at 3rd set of flag
  reloadCatapult();
  delay(100);
  drive("turn_left", 90, 120, 1000); //Turn towards wall
  delay(100);
  drive("backwards", 24, 100, 1500); //Align on wall*/
  drive("forwards", 12, 100, 1000); //Drive away from wall
  delay(100);
  drive("turn_left", 90, 120, 1000); //Turn away from wall
  delay(100);
  drive("backwards", 32, 180, 3000); //Back to platform
  delay(100);
  drive("turn_right", 90, 100, 2000); //Turn towards wall
  delay(100);
  drive("backwards", 24, 100, 1500); //Align on wall
  drive("forwards", 8, 60, 2000); //Drive off wall
  delay(100);
  drive("turn_left", 180, 80, 3000); //Turn around to face platfrom
  //Drive up platform
  driveHold();
  driveSet(-200, -200);
  delay(2750);
  driveSet(0,0);
  Ball_Intake.move_velocity(0);
}

void skills_backup(){
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
  flipCapAutonomous(); //Deploy arm
  drive("turn_right", 80, 120, 1000); //Turn towards 2nd cap
  delay(100);
  drive("forwards", 5, 80, 1000);
  delay(200);
  flipCapAutonomous(); //Flip 2nd cap
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
