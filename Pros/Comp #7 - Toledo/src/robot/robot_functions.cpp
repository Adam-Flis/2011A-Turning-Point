#include "main.h"
#include "define_items.hpp"
#include "robot_functions.hpp"

/* ********** Math Functions ********** */

//360 degrees for one full wheel rotation
//Reading from 4 encoder values averaged each side
//One full rotation of 4in omni = 12.566 in traveled (circumference)
//inchToTicks = 360*2/12.566 = 57.297
int inchToTicks(float inch){
  int ticks;
  ticks = inch * 52.297;
  return ticks;
}

//360 degrees for one full bot turn
//Reading from 4 encoder values averaged each side
//1360 degree counting in the motor
//1360*2/360 = 7.556
int degreesToTicks(float degrees){
  float ticksPerTurn = 7.556;
  int ticks = degrees * ticksPerTurn;
  return ticks;
}

/* ********** Helper Functions ********** */

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

void resetDrive(){
  Left_Front_Drive.tare_position();
  Left_Back_Drive.tare_position();
  Right_Front_Drive.tare_position();
  Right_Back_Drive.tare_position();
}

void resetLeft(){
  Left_Front_Drive.tare_position();
  Left_Back_Drive.tare_position();
}

void resetRight(){
  Right_Front_Drive.tare_position();
  Right_Back_Drive.tare_position();
}

void driveSet(int leftVelocity, int rightVelocity){
  Left_Front_Drive.move_velocity(leftVelocity);
  Left_Back_Drive.move_velocity(leftVelocity);
  Right_Front_Drive.move_velocity(rightVelocity);
  Right_Back_Drive.move_velocity(rightVelocity);
}

//Returns the sum of the two left wheels
int leftSideSum(){
  return fabs(Left_Front_Drive.get_position() + Left_Back_Drive.get_position());
}

//Returns the sum of the two right wheels
int rightSideSum(){
  return fabs(Right_Front_Drive.get_position() + Right_Back_Drive.get_position());
}

/* ********** Braking Functions ********** */

void driveBrake(){
  Left_Front_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Left_Back_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Right_Front_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Right_Back_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void driveCoast(){
  Left_Front_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
  Left_Back_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
  Right_Front_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
  Right_Back_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
}

void driveHold(){
  Left_Front_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
  Left_Back_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
  Right_Front_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
  Right_Back_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/* ********** Drive Functions ********** */

void drive(std::string direction, float target, int velocity, int time){
  //Constants for forwards and backwards
  const float Kp = 0.5;
  const float Ki = 0.0001;
  const float Kd = 0.2;
  const float Kp_C = 0.01;

  //Constants for turning
  const float Kp_turn = 0.6;
  const float Ki_turn = 0.0001;
  const float Kd_turn = 0.4;

  //PID Variables
  float error;
  float proportion;
  float integralRaw;
  float integral;
  float lastError;
  float derivative;

  //Drift Variables
  float error_drift;
  float proportion_drift;

  //Intigral Limits
  const float integralVelocityLimit = 20/Ki;
  const float integralActiveZoneStraight = inchToTicks(3);
  const float integralActiveZoneTurn = degreesToTicks(3);

  //Velocity control
  int finalVelocity;
  int maxVelocity = velocity;
  const int minVelocity = 20;

  //Other intergers
  int endTime;
  endTime = millis() + time;
  resetDrive();
  if (direction == "forwards" || direction == "backwards"){
    while (endTime > millis()){
      error = inchToTicks(target) - ((leftSideSum()/2) + (rightSideSum()/2));
      proportion = Kp * error;

      //Ends drive when close to target
      if (error < 0){
        break;
      }

      //Drift control
      /*error_drift  = (leftSideSum() - rightSideSum());
      proportion_drift = Kp_C * error_drift;*/

      //Integral control
      if (fabs(error) < integralActiveZoneStraight && error != 0){
        integralRaw = integralRaw + error;
      }
      else{
        integralRaw = 0;
      }

      if (integralRaw > integralVelocityLimit){
        integralRaw = integralVelocityLimit;
      }
      if (integralRaw < integralVelocityLimit){
        integralRaw = -integralVelocityLimit;
      }

      integral = Ki * integralRaw;

      //Derivative control
      derivative = Kd * (error - lastError);
      lastError = error;
      if (error == 0){
        derivative = 0;
      }

      //Set final velocity
      finalVelocity = proportion + integral + derivative;

      if (abs(finalVelocity) > maxVelocity){
        finalVelocity = maxVelocity;
      }
      else if (abs(finalVelocity) < minVelocity){
        finalVelocity = minVelocity;
      }

      if (direction == "forwards"){
        //driveSet(finalVelocity - proportion_drift, finalVelocity + proportion_drift);
        driveSet(finalVelocity, finalVelocity);
      }
      else if (direction == "backwards"){
        //driveSet(-finalVelocity - proportion_drift, -finalVelocity + proportion_drift);
        driveSet(-finalVelocity, -finalVelocity);
      }

      //Prevents overload on the cortex
      delay(20);
    }
  }
  else if (direction == "turn_left" || direction == "turn_right"){
    while (endTime > millis()){
      error = degreesToTicks(target) - ((leftSideSum()/2) + (rightSideSum()/2));
      proportion = Kp_turn * error;

      //Ends drive when close to target
      if (error < 0){
        break;
      }

      //Integral control
      if (fabs(error) < integralActiveZoneTurn && error != 0){
        integralRaw = integralRaw + error;
      }
      else{
        integralRaw = 0;
      }

      if (integralRaw > integralVelocityLimit){
        integralRaw = integralVelocityLimit;
      }
      if (integralRaw < integralVelocityLimit){
        integralRaw = -integralVelocityLimit;
      }

      integral = Ki_turn * integralRaw;

      //Derivative control
      derivative = Kd_turn * (error - lastError);
      lastError = error;
      if (error == 0){
        derivative = 0;
      }

      //Set final velocity
      finalVelocity = proportion + integral + derivative;

      if (abs(finalVelocity) > maxVelocity){
        finalVelocity = maxVelocity;
      }
      else if (abs(finalVelocity) < minVelocity){
        finalVelocity = minVelocity;
      }
      if (direction == "turn_left"){
        driveSet(-finalVelocity, finalVelocity);
        }
      else if (direction == "turn_right"){
        driveSet(finalVelocity, -finalVelocity);
        }
        //Prevents overload on the cortex
        delay(20);
      }
    }
    //Turn off drive train
    driveSet(0,0);
  }

void swing(int sensor_left, int velocity_left, int sensor_right, int velocity_right, int time){
  int endTime;
  endTime = millis() + time;
  resetDrive();
  driveSet(velocity_left,velocity_right);
  if (velocity_left != 0 && velocity_right == 0){
    while (Left_Front_Drive.get_position() != sensor_left || Left_Back_Drive.get_position() != sensor_left){
      if (endTime == millis()){break;}
    }
  }
  else if (velocity_right != 0 && velocity_left == 0){
    while (Right_Front_Drive.get_position() != sensor_right || Right_Back_Drive.get_position() != sensor_right){
      if (endTime == millis()){break;}
    }
  }
  else if (velocity_left != 0 && velocity_right != 0){
    while (Left_Front_Drive.get_position() != sensor_left || Left_Back_Drive.get_position() != sensor_left || Right_Front_Drive.get_position() != sensor_right || Right_Back_Drive.get_position() != sensor_right){
      if (endTime == millis()){break;}
    }
  }
  driveBrake();
  driveSet(0,0);
}

void drivePlatform(int platform_count){
  int current_draw_spike = 0;
  bool isLow = true;
  int draw = 1000;
  while (current_draw_spike != (platform_count+1) && isLow == true){
      driveSet(-170,-170);
      if (Left_Back_Drive.get_current_draw() > draw && Right_Back_Drive.get_current_draw() > draw){
        if (isLow == true){
          current_draw_spike++;
          isLow = false;
        }
      }
      else{
        isLow = true;
      }
      //Prevents overload on the cortex
      delay(10);
  }
  resetDrive();
  driveHold();
  Left_Front_Drive.move_absolute(-900,-200); //Sennsor value needs to be changed
  Left_Back_Drive.move_absolute(-900,-200);
  Right_Front_Drive.move_absolute(-900,-200);
  Right_Back_Drive.move_absolute(-900,-200);
}

/* ********** Other Functions ********** */

void upBalls(int sensor, int velocity, int time){
  int endTime;
  endTime = millis() + time;
  Ball_Intake.tare_position();
  Ball_Intake.move_velocity(velocity);
  while (Ball_Intake.get_position() != sensor){
    if (endTime == millis()){break;}
  }
  Ball_Intake.set_brake_mode(MOTOR_BRAKE_COAST);
  Ball_Intake.move_velocity(0);
}

void downBall(int sensor, int velocity, int time){
  int endTime;
  endTime = millis() + time;
  Ball_Intake.tare_position();
  Ball_Intake.move_velocity(-velocity);
  while (Ball_Intake.get_position() != -sensor){
    if (endTime == millis()){break;}
  }
  Ball_Intake.set_brake_mode(MOTOR_BRAKE_COAST);
  Ball_Intake.move_velocity(0);
}

void launchCatapult(){
  Catapult.move_velocity(200);
  delay(600);
  Catapult.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Catapult.move_velocity(0);
  Catapult.tare_position();
}

void reloadCatapult(){
  /*while (Catapult_Potentiometer.get_value() > 2085){
    Catapult.move_velocity(200);
  }
  Catapult.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Catapult.move_velocity(0);*/
  Catapult.tare_position();
  Catapult.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Catapult.move_absolute(2650, 200);
}

void armUp(int sensor, int velocity, int time){
  int endTime;
  endTime = millis() + time;
  Left_Arm.tare_position();
  Right_Arm.tare_position();
  Left_Arm.move_velocity(velocity);
  Right_Arm.move_velocity(velocity);
  while (Left_Arm.get_position() != sensor || Right_Arm.get_position() != sensor){
    if (endTime == millis()){break;}
  }
  Left_Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  Right_Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  Left_Arm.move_velocity(0);
  Right_Arm.move_velocity(0);
}

void armDown(int sensor, int velocity, int time){
  int endTime;
  endTime = millis() + time;
  Left_Arm.tare_position();
  Right_Arm.tare_position();
  Left_Arm.move_velocity(-velocity);
  Right_Arm.move_velocity(-velocity);
  while (Left_Arm.get_position() != -sensor || Right_Arm.get_position() != -sensor){
    if (endTime == millis()){break;}
  }
  Left_Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  Right_Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  Left_Arm.move_velocity(0);
  Right_Arm.move_velocity(0);
}

void flipCap(){
  Left_Arm.move_velocity(200);
  Right_Arm.move_velocity(200);
  delay(140);
  Left_Arm.move_velocity(-200);
  Right_Arm.move_velocity(-200);
  delay(190);
}

void flipCapAutonomous(){
  flipCap();
  Left_Arm.move_velocity(0);
  Right_Arm.move_velocity(0);
}

void flagHeight(){
  int endTime;
  endTime = millis() + 1000;
  Left_Arm.move_absolute(252,200);
  Right_Arm.move_absolute(252,200);
  while (Left_Arm.get_position() < 250 && Right_Arm.get_position() < 250){
    if (endTime == millis()){break;}
  }
}
