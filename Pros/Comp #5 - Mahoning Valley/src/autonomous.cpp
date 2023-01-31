#include "main.h"

void resetSensors(){
   Left_Front_Drive.tare_position();
   Left_Back_Drive.tare_position();
   Right_Front_Drive.tare_position();
   Right_Back_Drive.tare_position();
   Ball_Intake.tare_position();
   Catapult.tare_position();
   Left_Arm.tare_position();
   Right_Arm.tare_position();
}

void resetDriveTrain(){
    Left_Front_Drive.tare_position();
    Left_Back_Drive.tare_position();
    Right_Front_Drive.tare_position();
    Right_Back_Drive.tare_position();
}

void driveTrainBreaking(){
   Left_Front_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
   Left_Back_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
   Right_Front_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
   Right_Back_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void driveTrainCoasting(){
   Left_Front_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
   Left_Back_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
   Right_Front_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
   Right_Back_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
}

void driveTrainHolding(){
   Left_Front_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
   Left_Back_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
   Right_Front_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
   Right_Back_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void leftDriveTrain(int sensor,int velocity,int timeOut,int delayAfter){
  int endTime = millis() + timeOut;
  Left_Front_Drive.tare_position();
  Left_Back_Drive.tare_position();
  Left_Front_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Left_Back_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Left_Front_Drive.move_absolute(sensor,velocity);
  Left_Back_Drive.move_absolute(sensor,velocity);
  while (Left_Front_Drive.get_position() != sensor && Left_Back_Drive.get_position() != sensor){
    if (millis() == endTime){
      break;
    }
  }
  delay(delayAfter);
}

void rightDriveTrain(int sensor,int velocity,int timeOut,int delayAfter){
  int endTime = millis() + timeOut;
  Right_Front_Drive.tare_position();
  Right_Back_Drive.tare_position();
  Right_Front_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Right_Back_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Right_Front_Drive.move_absolute(sensor,velocity);
  Right_Back_Drive.move_absolute(sensor,velocity);
  while (Right_Front_Drive.get_position() != sensor && Right_Back_Drive.get_position() != sensor){
    if (millis() == endTime){
      break;
    }
  }
  delay(delayAfter);
}

void driveTrain(int sensor,int velocity,int timeOut,int delayAfter){
  int endTime = millis() + timeOut;
  resetDriveTrain();
  driveTrainBreaking();
  Left_Front_Drive.move_absolute(sensor,velocity);
  Left_Back_Drive.move_absolute(sensor,velocity);
  Right_Front_Drive.move_absolute(sensor,velocity);
  Right_Back_Drive.move_absolute(sensor,velocity);
  while (Left_Front_Drive.get_position() != sensor && Left_Back_Drive.get_position() != sensor && Right_Front_Drive.get_position() != sensor && Right_Back_Drive.get_position() != sensor){
    if (millis() == endTime){
      break;
    }
  }
  delay(delayAfter);
}

void moveLeftDriveTrain(int velocity){
   Left_Front_Drive.move_velocity(velocity);
   Left_Back_Drive.move_velocity(velocity);
}

void moveRightDriveTrain(int velocity){
  Right_Front_Drive.move_velocity(velocity);
  Right_Back_Drive.move_velocity(velocity);
}

void moveDriveTrain(int velocity){
  Left_Front_Drive.move_velocity(velocity);
  Left_Back_Drive.move_velocity(velocity);
  Right_Front_Drive.move_velocity(velocity);
  Right_Back_Drive.move_velocity(velocity);
}

//360 for one full wheel rotation
//Reading from 4 encoder values each side averaged
//360 * 2
//One full rotation of 4in omni = 12.566 in traveled (circumference)
//inchToTicks = 360*2/12.566 = 57.296
int inchToTicks (float inch){
  int ticks;
  ticks = inch * 57.296;
  return ticks;
}


//One full 360 degree turn of the robot =
//1360 degree counting in the motor
//1360*2/360 = 7.556
int degreesToTicks(float degrees){
  float ticksPerTurn = 7.556;
  int ticks = degrees * ticksPerTurn;
  return ticks;
}

void driveForwardsPID(float target,int timeOut,int maxVelocity,int delayAfter){
  float Kp = 0.4;
  float Ki = 0.15;
  float Kd = 0.6;
  int error;
  int proportion;
  int intergralRaw;
  float intergralActiveZone = inchToTicks(3);
  float intergral;
  int lastError;
  int derivative;
  int finalVelocity;
  float intergralVelocityLimit = 20/Ki;
  float Kp_C = 0.01;
  int error_drift;
  float proportion_drift;
  resetDriveTrain();
  long endTime;
  endTime = millis() + timeOut;
  while (millis() < endTime){
    error = inchToTicks(target) - (((Left_Front_Drive.get_position() + Left_Back_Drive.get_position())/2) + ((Right_Front_Drive.get_position() + Right_Back_Drive.get_position())/2));
    if (error < 70){
      break;
    }
    proportion = Kp * error;
    if (abs(error) < intergralActiveZone && error != 0){
      intergralRaw = intergralRaw + error;
    }
    else {
      intergralRaw = 0;
    }
    if (intergralRaw > intergralVelocityLimit){
      intergralRaw = intergralVelocityLimit;
    }
    if (intergralRaw < intergralVelocityLimit){
      intergralRaw = -intergralVelocityLimit;
    }
    intergral = Ki * intergralRaw;
    derivative = Kd * (error - lastError);
    lastError = error;
    if (error == 0){
      derivative = 0;
    }
    finalVelocity = proportion + intergral + derivative;
    if (finalVelocity > maxVelocity){
      finalVelocity = maxVelocity;
    }
    else if (finalVelocity < -maxVelocity){
      finalVelocity = -maxVelocity;
    }
    error_drift  = (((Left_Front_Drive.get_position() + Left_Back_Drive.get_position())/2) - ((Right_Front_Drive.get_position() + Right_Back_Drive.get_position())/2));
    proportion_drift = Kp_C * error_drift;
    moveLeftDriveTrain(finalVelocity + proportion_drift);
    moveRightDriveTrain(finalVelocity - proportion_drift);
    delay(20);
  }
  driveTrainBreaking();
  moveDriveTrain(0);
  delay(delayAfter);
}

void driveBackwardsPID(float target,int timeOut,int maxVelocity,int delayAfter){
  float Kp = 0.4;
  float Ki = 0.15;
  float Kd = 0.6;
  int error;
  int proportion;
  int intergralRaw;
  float intergralActiveZone = inchToTicks(3);
  float intergral;
  int lastError;
  int derivative;
  int finalVelocity;
  float intergralVelocityLimit = 20/Ki;
  float Kp_C = 0.01;
  int error_drift;
  float proportion_drift;
  resetDriveTrain();
  long endTime;
  endTime = millis() + timeOut;
  while (millis() < endTime){
    error = inchToTicks(target) + (((Left_Front_Drive.get_position() + Left_Back_Drive.get_position())/2) + ((Right_Front_Drive.get_position() + Right_Back_Drive.get_position())/2));
    proportion = Kp * error;
    if (error < 70){
      break;
    }
    if (abs(error) < intergralActiveZone && error != 0){
      intergralRaw = intergralRaw + error;
    }
    else {
      intergralRaw = 0;
    }
    if (intergralRaw > intergralVelocityLimit){
      intergralRaw = intergralVelocityLimit;
    }
    if (intergralRaw < intergralVelocityLimit){
      intergralRaw = -intergralVelocityLimit;
    }
    intergral = Ki * intergralRaw;
    derivative = Kd * (error - lastError);
    lastError = error;
    if (error == 0){
      derivative = 0;
    }
    finalVelocity = proportion + intergral + derivative;
    if (finalVelocity > maxVelocity){
      finalVelocity = maxVelocity;
    }
    else if (finalVelocity < -maxVelocity){
      finalVelocity = -maxVelocity;
    }
    error_drift  = (((Left_Front_Drive.get_position() + Left_Back_Drive.get_position())/2) - ((Right_Front_Drive.get_position() + Right_Back_Drive.get_position())/2));
    proportion_drift = Kp_C * error_drift;
    moveLeftDriveTrain(-finalVelocity + proportion_drift);
    moveRightDriveTrain(-finalVelocity - proportion_drift);
    delay(20);
  }
  driveTrainBreaking();
  moveDriveTrain(0);
  delay(delayAfter);
}

void turnLeftPID(float target,int timeOut,int maxVelocity,int delayAfter){
  float Kp = 0.6;
  float Ki = 0.15;
  float Kd = 0.8;
  int error;
  int proportion;
  int intergralRaw;
  float intergralActiveZone = degreesToTicks(3);
  float intergral;
  int lastError;
  int derivative;
  int finalVelocity;
  float intergralVelocityLimit = 20/Ki;
  resetDriveTrain();
  long endTime;
  endTime = millis() + timeOut;
  while (millis() < endTime){
    error = degreesToTicks(target) + (((Left_Front_Drive.get_position() + Left_Back_Drive.get_position())/2) - ((Right_Front_Drive.get_position() + Right_Back_Drive.get_position())/2));
    if (error < 30){
      break;
    }
    proportion = Kp * error;
    if (abs(error) < intergralActiveZone && error != 0){
         intergralRaw = intergralRaw + error;
    }
    else {
      intergralRaw = 0;
    }
    if (intergralRaw > intergralVelocityLimit){
      intergralRaw = intergralVelocityLimit;
    }
    if (intergralRaw < intergralVelocityLimit){
      intergralRaw = -intergralVelocityLimit;
    }
    intergral = Ki * intergralRaw;
    derivative = Kd * (error - lastError);
    lastError = error;
    if (error == 0){
      derivative = 0;
    }
    finalVelocity = proportion + intergral + derivative;
    if (finalVelocity > maxVelocity){
      finalVelocity = maxVelocity;
    }
    else if (finalVelocity < -maxVelocity){
      finalVelocity = -maxVelocity;
    }
    moveLeftDriveTrain(-finalVelocity);
    moveRightDriveTrain(finalVelocity);
    delay(20);
  }
  driveTrainBreaking();
  moveDriveTrain(0);
  delay(delayAfter);
}

void turnRightPID(float target,int timeOut,int maxVelocity,int delayAfter){
  float Kp = 0.6;
  float Ki = 0.15;
  float Kd = 0.8;
  int error;
  int proportion;
  int intergralRaw;
  float intergralActiveZone = degreesToTicks(3);
  float intergral;
  int lastError;
  int derivative;
  int finalVelocity;
  float intergralVelocityLimit = 20/Ki;
  resetDriveTrain();
  long endTime;
  endTime = millis() + timeOut;
  while (millis() < endTime){
    error = degreesToTicks(target) - (((Left_Front_Drive.get_position() + Left_Back_Drive.get_position())/2) - ((Right_Front_Drive.get_position() + Right_Back_Drive.get_position())/2));
    if (error < 30){
      break;
    }
    proportion = Kp * error;
    if (abs(error) < intergralActiveZone && error != 0){
         intergralRaw = intergralRaw + error;
    }
    else {
      intergralRaw = 0;
    }
    if (intergralRaw > intergralVelocityLimit){
      intergralRaw = intergralVelocityLimit;
    }
    if (intergralRaw < intergralVelocityLimit){
      intergralRaw = -intergralVelocityLimit;
    }
    intergral = Ki * intergralRaw;
    derivative = Kd * (error - lastError);
    lastError = error;
    if (error == 0){
      derivative = 0;
    }
    finalVelocity = proportion + intergral + derivative;
    if (finalVelocity > maxVelocity){
      finalVelocity = maxVelocity;
    }
    else if (finalVelocity < -maxVelocity){
      finalVelocity = -maxVelocity;
    }
    moveLeftDriveTrain(finalVelocity);
    moveRightDriveTrain(-finalVelocity);
    delay(20);
  }
  driveTrainBreaking();
  moveDriveTrain(0);
  delay(delayAfter);
}

void upBalls(int sensor,int velocity,int delayAfter){
  Ball_Intake.tare_position();
  Ball_Intake.set_brake_mode(MOTOR_BRAKE_COAST);
  Ball_Intake.move_absolute(sensor, velocity);
  while (Ball_Intake.get_position() != sensor){}
  delay(delayAfter);
}

void downBall(int sensor,int velocity,int delayAfter){
  Ball_Intake.tare_position();
  Ball_Intake.set_brake_mode(MOTOR_BRAKE_COAST);
  Ball_Intake.move_absolute(-sensor, -velocity);
  while (Ball_Intake.get_position() != -sensor){}
  delay(delayAfter);
}

void launchBalls(int time,int velocity,int delayAfter){
  Catapult.tare_position();
  Catapult.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Catapult.move_velocity(velocity);
  delay(time);
  Catapult.move_velocity(0);
  delay(delayAfter);
}

void prepCatapult(){
  while (Catapult_Potentiometer.get_value() < 1180){
    Catapult.move_velocity(200);
  }
  Catapult.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Catapult.move_velocity(0);
}

void armUp(int sensor,int velocity,int timeOut,int delayAfter){
  int endTime = millis() + timeOut;
  Left_Arm.tare_position();
  Right_Arm.tare_position();
  Left_Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  Right_Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  Left_Arm.move_absolute(sensor,velocity);
  Right_Arm.move_absolute(sensor,velocity);
  while (Left_Arm.get_position() != sensor && Right_Arm.get_position() != sensor){
    if (millis() == endTime){
      break;
    }
  }
  delay(delayAfter);
}

void armDown(int sensor,int velocity,int timeOut,int delayAfter){
  int endTime = millis() + timeOut;
  Left_Arm.tare_position();
  Right_Arm.tare_position();
  Left_Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  Right_Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  Left_Arm.move_absolute(-sensor,-velocity);
  Right_Arm.move_absolute(-sensor,-velocity);
  while (Left_Arm.get_position() != -sensor && Right_Arm.get_position() != -sensor){
    if (millis() == endTime){
      break;
    }
  }
  delay(delayAfter);
}

void flipCap(){
  Left_Arm.move_velocity(200);
  Right_Arm.move_velocity(200);
  delay(200);
  Left_Arm.move_velocity(-200);
  Right_Arm.move_velocity(-200);
  delay(250);
}

void flagHeight(){
  int endTime = millis() + 1500;
  Left_Arm.move_absolute(250,200);
  Right_Arm.move_absolute(250,200);
  while (Left_Arm.get_position() != 250 && Right_Arm.get_position() != 250){
    if (millis() == endTime){
      break;
    }
  }
}

//************************************************************//

void blueFront(){
  Ball_Intake.move_velocity(200);
  driveBackwardsPID(37, 4000, 180, 450); //Grab ball
  driveForwardsPID(30.5, 4000, 180, 100);
  Ball_Intake.move_velocity(0);
  turnLeftPID(95, 1000, 80, 100); //Turn towards flags
  driveForwardsPID(5, 2000, 50, 100);
  launchBalls(1000, 200, 100); //Launch balls at flags
  flagHeight();
  driveForwardsPID(36, 2500, 180, 100); //Flip bottom flag
  driveBackwardsPID(17, 1000, 100, 100);
  armDown(300, 200, 500, 50);
  resetSensors();
  turnLeftPID(90, 1000, 120, 100); //Turn towards cap
  driveForwardsPID(6, 1000, 70, 100);
  flipCap(); //Flip cap
  turnRightPID(45, 1000, 100, 200); //Turn towards bottom flag
  flagHeight();
  driveForwardsPID(36, 2000, 180, 100); //Flip bottom flag
}

void blueBack(){
  Ball_Intake.move_velocity(200);
  driveBackwardsPID(37, 4000, 180, 500); //Grab ball
  driveForwardsPID(12, 4000, 100, 100);
  leftDriveTrain(1300, 140, 1400, 100); //Swing towards cap
  Ball_Intake.move_velocity(0);
  armUp(400, 200, 500, 0); //Deploy arm
  armDown(400, 200, 500, 100);
  driveForwardsPID(23.5, 1300, 150, 100); //Drive towards cap
  flipCap();
  leftDriveTrain(-1200, -90, 1400, 100); //Swing to platform
  driveTrain(-1200, -200, 3500, 0); //Park
  driveTrainHolding();
}

void redFront(){
  Ball_Intake.move_velocity(200);
  driveBackwardsPID(36, 4000, 180, 400); //Grab ball
  driveForwardsPID(30.5, 4000, 180, 100);
  Ball_Intake.move_velocity(0);
  turnRightPID(95, 1000, 80, 100); //Turn towards flags
  driveForwardsPID(5, 2000, 50, 100);
  launchBalls(1000, 200, 100); //Launch balls at flags
  flagHeight();
  driveForwardsPID(36, 2500, 180, 100); //Flip bottom flag
  driveBackwardsPID(17, 1000, 100, 100);
  armDown(300, 200, 500, 50);
  resetSensors();
  turnRightPID(90, 1000, 120, 100); //Turn towards cap
  driveForwardsPID(6, 1000, 70, 100);
  flipCap(); //Flip cap
  turnLeftPID(30, 1000, 100, 200); //Turn towards bottom flag
  flagHeight();
  driveForwardsPID(36, 2000, 180, 100); //Flip bottom flag
}

void redBack(){
  Ball_Intake.move_velocity(200);
  driveBackwardsPID(36, 4000, 180, 400); //Grab ball
  driveForwardsPID(12, 4000, 100, 100);
  rightDriveTrain(1300, 140, 1400, 100); //Swing towards cap
  Ball_Intake.move_velocity(0);
  armUp(400, 200, 500, 0); //Deploy arm
  armDown(400, 200, 500, 100);
  driveForwardsPID(23.5, 1300, 150, 100); //Drive towards cap
  flipCap();
  rightDriveTrain(-1200, -90, 1400, 100); //Swing to platform
  driveTrain(-1250, -200, 3500, 0); //Park
  driveTrainHolding();
}

void Skills(){
  Ball_Intake.move_velocity(200);
  driveBackwardsPID(36, 4000, 170, 300);
  driveForwardsPID(12, 3000, 150, 100);
  Ball_Intake.move_velocity(0);
  turnLeftPID(45, 2000, 100, 100);
  driveForwardsPID(24, 4000, 170, 100);
  flipCap();
  driveBackwardsPID(24, 4000, 170, 100);
  turnRightPID(45, 1000, 150, 100);
  driveBackwardsPID(52, 5000, 180, 100);
  driveForwardsPID(6, 1000, 100, 100);
  turnRightPID(90, 1000, 150, 100);
  driveForwardsPID(48, 3000, 180, 100);
  launchBalls(1000, 200, 100);
  flagHeight();
  driveForwardsPID(36, 2000, 180, 100);
  driveBackwardsPID(12, 1000, 140, 100);
}

void autonomous(){
  resetSensors();
  //turnRightPID(90, 10000, 100, 0);
  blueBack();
  //driveForwardsPID(96, 10000, 80, 0);
  lcd::set_text(3, "Chung");
}
