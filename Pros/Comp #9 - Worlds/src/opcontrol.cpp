#include "main.h"
#include "robot/define_items.hpp"
#include "robot/robot_functions.hpp"

bool SwitchDrive = false;
bool CatapultStop = false;
bool FlagHeight = false;
bool ArmLock = false;
bool RakeUpBallIntake = false;
bool RakeUpCapStacker = false;

void opcontrol() {
	Gyro.reset();
	while (true){
		//c::lcd_print(0, "Gyro: %f", Gyro.get_value()/10);

		if (Main.get_digital_new_press(DIGITAL_LEFT)){
			SwitchDrive =! SwitchDrive;
		}
		if (Main.get_digital_new_press(DIGITAL_UP)){
			CatapultStop =! CatapultStop;
		}
		if (Main.get_digital_new_press(DIGITAL_B) && Cap_Stacker_Potentiometer.get_value() < 1000){
			FlagHeight = true;
		}

		//--------------------------------------------// Controller Screen

		if (SwitchDrive == false){
			Main.set_text(2,0,"Fast Movement");
		}
		else {
			Main.set_text(2,0,"Slow Movement");
		}

		if (SwitchDrive == false){
			driveBrake();
			Left_Front_Drive.move(Main.get_analog(ANALOG_LEFT_Y) * .95);
			Left_Back_Drive.move(Main.get_analog(ANALOG_LEFT_Y) * .95);
			Right_Front_Drive.move(Main.get_analog(ANALOG_RIGHT_Y));
			Right_Back_Drive.move(Main.get_analog(ANALOG_RIGHT_Y));
		}
		else {
			driveHold();
			Left_Front_Drive.move(Main.get_analog(ANALOG_LEFT_Y) * .65);
			Left_Back_Drive.move(Main.get_analog(ANALOG_LEFT_Y) * .65);
			Right_Front_Drive.move(Main.get_analog(ANALOG_RIGHT_Y) * .7);
			Right_Back_Drive.move(Main.get_analog(ANALOG_RIGHT_Y) * .7);
		}

		//--------------------------------------------// Ball Intake

		if (Main.get_digital(DIGITAL_L1) && Catapult_Potentiometer.get_value() < 1000){
			Ball_Intake.move_velocity(200);
			RakeUpBallIntake = true;
		}
		else if (Main.get_digital(DIGITAL_DOWN)){
			Ball_Intake.move_velocity(-200);
			RakeUpBallIntake = true;
		}
		else {
			Ball_Intake.set_brake_mode(MOTOR_BRAKE_COAST);
			Ball_Intake.move_velocity(0);
			RakeUpBallIntake = false;
		}

		//--------------------------------------------// Catapult

		if (Catapult_Potentiometer.get_value() > 960 && CatapultStop == false){
			Catapult.move_velocity(200);
		}
		else if (Main.get_digital(DIGITAL_L2)){
			Catapult.move_velocity(200);
		}
		else {
			Catapult.set_brake_mode(MOTOR_BRAKE_COAST);
			Catapult.move_velocity(0);
		}

		//--------------------------------------------// Rake

		if (Main.get_digital(DIGITAL_X)){
			Rake.move_velocity(100);
		}
		else if (Main.get_digital(DIGITAL_A)){
			Rake.move_velocity(-100);
		}
		else if (Rake_Potentiometer.get_value() > 11){
			if (RakeUpBallIntake == true || RakeUpCapStacker == true){
				Rake.move_velocity(200);
			}
		}
		else{
			Rake.set_brake_mode(MOTOR_BRAKE_BRAKE);
			Rake.move_velocity(0);
		}

		//--------------------------------------------// Cap Stacker

		if (Main.get_digital(DIGITAL_R1) && ArmLock == false){
			Cap_Stacker.move_velocity(170);
			RakeUpCapStacker = true;
		}
		else if (Main.get_digital(DIGITAL_R2)){
			Cap_Stacker.move_velocity(-170);
		}
		else if (FlagHeight == true){
			Cap_Stacker.move_velocity(200);
			if (Cap_Stacker_Potentiometer.get_value() > 1000){
				FlagHeight = false;
				ArmLock = true;
			}
		}
		else if (Cap_Stacker_Potentiometer.get_value() > 3550){
			Cap_Stacker.move_velocity(-200);
		}
		else {
			if (Cap_Stacker_Potentiometer.get_value() < 950){
				ArmLock = false;
			}
			if (Cap_Stacker_Potentiometer.get_value() < 500){
				Cap_Stacker.set_brake_mode(MOTOR_BRAKE_BRAKE);
				RakeUpCapStacker = false;
			}
			else {
				Cap_Stacker.set_brake_mode(MOTOR_BRAKE_HOLD);
				RakeUpCapStacker = true;
			}
			Cap_Stacker.move_velocity(0);
		}
		//Prevents overload on the cortex
		delay(20);
	}
}
