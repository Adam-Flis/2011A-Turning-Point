#include "main.h"
#include "define_items.hpp"
#include "robot_functions.hpp"

/* ********** Conversion Functions ********** */

//360 degrees for one full wheel rotation
//Reading from 4 encoder values averaged each side
//One full rotation of 4in omni = 12.566 in traveled (circumference)
//inchToTicks = 288*2/12.566 = 45.837
int inchToTicks(float inch){
  int ticks;
  ticks = inch * 45.837;
  return ticks;
}

/* ********** Reset Functions ********** */

void resetSensors(){
  Left_Front_Drive.tare_position();
  Left_Back_Drive.tare_position();
  Right_Front_Drive.tare_position();
  Right_Back_Drive.tare_position();
  Ball_Intake.tare_position();
  Catapult.tare_position();
  Cap_Stacker.tare_position();
  Gyro.reset();
}

void resetGyro(){
  Gyro.reset();
}

void resetDrive(){
  Left_Front_Drive.tare_position();
  Left_Back_Drive.tare_position();
  Right_Front_Drive.tare_position();
  Right_Back_Drive.tare_position();
}

void resetLeftDrive(){
  Left_Front_Drive.tare_position();
  Left_Back_Drive.tare_position();
}

void resetRightDrive(){
  Right_Front_Drive.tare_position();
  Right_Back_Drive.tare_position();
}

/*********** Drive Set Functions ***********/

void driveSet(int leftVelocity, int rightVelocity){
  Left_Front_Drive.move_velocity(leftVelocity);
  Left_Back_Drive.move_velocity(leftVelocity);
  Right_Front_Drive.move_velocity(rightVelocity);
  Right_Back_Drive.move_velocity(rightVelocity);
}

void driveSetCurrent(int leftCurrent, int rightCurrent){
  Left_Front_Drive.set_current_limit(leftCurrent);
  Left_Back_Drive.set_current_limit(leftCurrent);
  Right_Front_Drive.set_current_limit(rightCurrent);
  Right_Front_Drive.set_current_limit(rightCurrent);
}


/*********** Absolute Value Functions ***********/

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
  resetSensors();
  //Constants for forwards and backwards
  const float Kp = 0.3;
  const float Ki = 0.0001;
  const float Kd = 0.17;

  //Constant for drift
  const float Kp_C = 0.15;

  //Constants for turning
  const float Kp_turn = 0.165;
  const float Ki_turn = 0.0001;
  const float Kd_turn = 0.1;

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
  const float integralVelocityLimit = 5/Ki;
  const float integralActiveZone = inchToTicks(3);

  //Velocity control
  int finalVelocity;
  int maxVelocity = velocity;

  //Other intergers
  int endTime;
  endTime = millis() + time;

  //Reset Sensors
  resetDrive();
  resetGyro();

  if (direction == "forwards" || direction == "backwards"){
    while (1){
      //c::lcd_print(0, "Gyro: %f", Gyro.get_value()/10);

      //Reloads catapult while driving on the field
      if (Catapult_Potentiometer.get_value() > 960){
    			Catapult.move_velocity(200);
      }
      else {
    			Catapult.set_brake_mode(MOTOR_BRAKE_COAST);
    			Catapult.move_velocity(0);
    	}

      error = inchToTicks(target) - ((leftSideSum()/2) + (rightSideSum()/2));
      proportion = Kp * error;

      //Stops drive when the robot reaches target
      if (error < 25){break;}

      //Timeout statement
      if (endTime == millis()){break;}

      //Drift control
      error_drift = Gyro.get_value();
      proportion_drift = Kp_C * error_drift;

      //Integral control
      if (fabs(error) < integralActiveZone && error != 0){
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

      if (finalVelocity > maxVelocity){
        finalVelocity = maxVelocity;
      }
      else if (finalVelocity < -maxVelocity){
        finalVelocity = -maxVelocity;
      }

      if (direction == "forwards"){
        driveSet(finalVelocity - proportion_drift, finalVelocity + proportion_drift);
        //driveSet(finalVelocity, finalVelocity);
      }
      else if (direction == "backwards"){
        driveSet(-finalVelocity - proportion_drift, -finalVelocity + proportion_drift);
        //driveSet(-finalVelocity, -finalVelocity);
      }
      //Prevents overload on the cortex
      delay(20);
      }
    }
    else if (direction == "turn_left" || direction == "turn_right"){
      while (1){
        //c::lcd_print(0, "Gyro: %f", Gyro.get_value()/10);

        //Reloads catapult while driving on the field
        if (Catapult_Potentiometer.get_value() > 960){
      			Catapult.move_velocity(200);
        }
        else {
      			Catapult.set_brake_mode(MOTOR_BRAKE_COAST);
      			Catapult.move_velocity(0);
      	}

        error = fabs(target * 10) - fabs(Gyro.get_value());
        proportion = Kp_turn * error;

        //Stops drive when the robot reaches target
        if (error < 25){break;}

        //Timeout statement
        if (endTime == millis()){break;}

        //Drift control
        error_drift  = (leftSideSum() - rightSideSum());
        proportion_drift = Kp_C * error_drift;

        //Integral control
        if (fabs(error) < integralActiveZone && fabs(error) != 0)
        integralRaw = integralRaw + error;
        else
        integralRaw = 0;

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

        if (finalVelocity > maxVelocity){
          finalVelocity = maxVelocity;
        }
        else if (finalVelocity < -maxVelocity){
          finalVelocity = -maxVelocity;
        }

        if (direction == "turn_left"){
          driveSet(-finalVelocity - proportion_drift, finalVelocity + proportion_drift);
          //driveSet(-finalVelocity, finalVelocity);
        }
        else if (direction == "turn_right"){
          driveSet(finalVelocity - proportion_drift, -finalVelocity + proportion_drift);
          //driveSet(finalVelocity, -finalVelocity);
        }
        //Prevents overload on the cortex
        delay(20);
      }
    }
  //Turn off things
  driveBrake();
  Catapult.set_brake_mode(MOTOR_BRAKE_COAST);
  driveSet(0,0);
  Catapult.move_velocity(0);
}

void driveBackwardsArm(float target, int velocity, int time){
resetSensors();
  //Constants for forwards and backwards
  const float Kp = 0.3;
  const float Ki = 0.0001;
  const float Kd = 0.17;

  //Constant for drift
  const float Kp_C = 0.15;

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
  const float integralVelocityLimit = 5/Ki;
  const float integralActiveZone = inchToTicks(3);

  //Velocity control
  int finalVelocity;
  int maxVelocity = velocity;

  //Other intergers
  int endTime;
  endTime = millis() + time;
  bool reverse = false;

  //Reset Sensors
  resetDrive();
  resetGyro();

  while (1){
    //c::lcd_print(0, "Gyro: %f", Gyro.get_value()/10);

    //Reloads catapult while driving on the field
    if (Catapult_Potentiometer.get_value() > 960){
        Catapult.move_velocity(200);
    }
    else {
        Catapult.set_brake_mode(MOTOR_BRAKE_COAST);
        Catapult.move_velocity(0);
    }

    //Deploys Arm
    if (Cap_Stacker_Potentiometer.get_value() < 800 && reverse == false){
      Cap_Stacker.move_velocity(200);
    }
    else if (Cap_Stacker_Potentiometer.get_value() > 300 && reverse == true){
      Cap_Stacker.move_velocity(-200);
    }
    else {
        Cap_Stacker.set_brake_mode(MOTOR_BRAKE_BRAKE);
        Cap_Stacker.move_velocity(0);
    }
    if (Cap_Stacker_Potentiometer.get_value() > 1000){
      reverse = true;
    }

    error = inchToTicks(target) - ((leftSideSum()/2) + (rightSideSum()/2));
    proportion = Kp * error;

    //Stops drive when the robot reaches target
    if (error < 25){break;}

    //Timeout statement
    if (endTime == millis()){break;}

    //Drift control
    error_drift = Gyro.get_value();
    proportion_drift = Kp_C * error_drift;

    //Integral control
    if (fabs(error) < integralActiveZone && error != 0){
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

    if (finalVelocity > maxVelocity){
      finalVelocity = maxVelocity;
    }
    else if (finalVelocity < -maxVelocity){
      finalVelocity = -maxVelocity;
    }

    driveSet(-finalVelocity - proportion_drift, -finalVelocity + proportion_drift);
    //driveSet(-finalVelocity, -finalVelocity);

    //Prevents overload on the cortex
    delay(20);
  }

  //Turn off things
  driveBrake();
  Catapult.set_brake_mode(MOTOR_BRAKE_COAST);
  Cap_Stacker.set_brake_mode(MOTOR_BRAKE_BRAKE);
  driveSet(0,0);
  Catapult.move_velocity(0);
  Cap_Stacker.move_velocity(0);
}

void swing(int sensor_left, int velocity_left, int sensor_right, int velocity_right, int time){
  resetSensors();
  int endTime;
  endTime = millis() + time;
  bool leftOn = true;
  bool rightOn = true;
  resetDrive();
  driveSet(velocity_left, velocity_right);
  while(1){
    if (Left_Front_Drive.get_position() == sensor_left || Left_Back_Drive.get_position() == sensor_left){
      Left_Front_Drive.move_velocity(0);
      Left_Back_Drive.move_velocity(0);
      leftOn = false;
    }
    if (Right_Front_Drive.get_position() == sensor_right || Right_Back_Drive.get_position() == sensor_right){
      Right_Front_Drive.move_velocity(0);
      Right_Back_Drive.move_velocity(0);
      rightOn = false;
    }
    if (leftOn == false && rightOn == false){break;}
    if (endTime == millis()){break;}
  }
}

void drivePlatform(int platform_count){
  resetSensors();
  int current_draw_spike = 0;
  bool isLow = true;
  int draw = 1000;
  while (current_draw_spike != (platform_count+1)){
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

/* ********** Ball Functions ********** */

void upBalls(int sensor, int velocity, int time){
  int endTime;
  endTime = millis() + time;
  Ball_Intake.tare_position();
  Ball_Intake.move_velocity(velocity);
  while (1){
    if (Ball_Intake.get_position() == sensor){break;}
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
  while (1){
    if (Ball_Intake.get_position() == -sensor){break;}
    if (endTime == millis()){break;}
  }
  Ball_Intake.set_brake_mode(MOTOR_BRAKE_COAST);
  Ball_Intake.move_velocity(0);
}

/* ********** Catapult Functions ********** */
void shootLastSecond(){
  Catapult.set_brake_mode(MOTOR_BRAKE_COAST);
  while (1){
    if (millis() > 14400){
      Catapult.move_velocity(200);
      delay(500);
      Catapult.move_velocity(0);
      break;
    }
    else {
      Catapult.move_velocity(0);
    }
  }
}

void launchCatapult(){
  Catapult.move_velocity(200);
  delay(500);
  Catapult.set_brake_mode(MOTOR_BRAKE_COAST);
  Catapult.move_velocity(0);
  Catapult.tare_position();
}

/* ********** Rake Functions ********** */

void rakePot(int sensor, int time){
  int endTime;
  endTime = millis() + time;
  Rake.set_brake_mode(MOTOR_BRAKE_HOLD);
  while (1){
    if (Rake_Potentiometer.get_value() > (sensor + 10)){
      Rake.move_velocity(70);
    }
    else if (Rake_Potentiometer.get_value() < (sensor - 10)){
      Rake.move_velocity(-70);
    }
    else {
      Rake.move_velocity(0);
      break;
    }
    if (endTime == millis()){
      Rake.move_velocity(0);
      break;
    }
  }
}

void rakeBall(){
  int endTime;
  int sensor = 1580;
  endTime = millis() + 600;
  Rake.set_brake_mode(MOTOR_BRAKE_HOLD);
  while (1){
    if (Rake_Potentiometer.get_value() > (sensor + 15)){
      Rake.move_velocity(70);
    }
    else if (Rake_Potentiometer.get_value() < (sensor - 15)){
      Rake.move_velocity(-70);
    }
    else {
      Rake.move_velocity(0);
      break;
    }
    if (endTime == millis()){
      Rake.move_velocity(0);
      break;
    }
  }
  delay(300);
  Ball_Intake.move_velocity(200);
  driveSet(50, 50);
  delay(300);
  driveSet(0, 0);
}

void rakeUp(int sensor, int velocity, int time){
  int endTime;
  endTime = millis() + time;
  Rake.tare_position();
  Rake.move_velocity(velocity);
  while (1){
    if (Rake.get_position() == sensor){break;}
    if (endTime == millis()){break;}
  }
  Rake.set_brake_mode(MOTOR_BRAKE_HOLD);
  Rake.move_velocity(0);
}

void rakeDown(int sensor, int velocity, int time){
  int endTime;
  endTime = millis() + time;
  Rake.tare_position();
  Rake.move_velocity(-velocity);
  while (1){
    if (Rake.get_position() == -sensor){break;}
    if (endTime == millis()){break;}
  }
  Rake.set_brake_mode(MOTOR_BRAKE_HOLD);
  Rake.move_velocity(0);
}

/* ********** Arm Functions ********** */

void armUp(int sensor, int velocity, int time){
  int endTime;
  endTime = millis() + time;
  Cap_Stacker.tare_position();
  Cap_Stacker.move_velocity(velocity);
  while (1){
    if (Cap_Stacker_Potentiometer.get_value() == sensor){break;}
    if (endTime == millis()){break;}
  }
  Cap_Stacker.set_brake_mode(MOTOR_BRAKE_HOLD);
  Cap_Stacker.move_velocity(0);
}

void armDown(int sensor, int velocity, int time){
  int endTime;
  endTime = millis() + time;
  Cap_Stacker.tare_position();
  Cap_Stacker.move_velocity(-velocity);
  while (1){
    if (Cap_Stacker_Potentiometer.get_value() == sensor){break;}
    if (endTime == millis()){break;}
  }
  Cap_Stacker.set_brake_mode(MOTOR_BRAKE_HOLD);
  Cap_Stacker.move_velocity(0);
}

void flipCap(){
  Cap_Stacker.move_velocity(200);
  delay(250);
  Cap_Stacker.move_velocity(-200);
  delay(280);
}

void flipCapAutonomous(){
  flipCap();
  Cap_Stacker.move_velocity(0);
}

void flagHeight(){
  int endTime;
  endTime = millis() + 1000;
  Cap_Stacker.move_velocity(200);
  while (1){
    if (Cap_Stacker_Potentiometer.get_value() > 1000){break;}
    if (endTime == millis()){break;}
  }
  Cap_Stacker.set_brake_mode(MOTOR_BRAKE_HOLD);
  Cap_Stacker.move_velocity(0);
}
