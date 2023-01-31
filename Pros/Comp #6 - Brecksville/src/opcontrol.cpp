#include "main.h"
#include "robot/define_items.hpp"
#include "robot/robot_functions.hpp"

bool SwitchDrive = false;
bool CatapultStop = false;
bool CapFlip = false;
bool FlagHeight = false;

void opcontrol() {
	while (true){
		if (master.get_digital_new_press(DIGITAL_Y)){
		c::lcd_print(1,"Left_Front_Current:%d",Left_Front_Drive.get_current_draw());
		c::lcd_print(2,"Left_Back_Current:%d",Left_Back_Drive.get_current_draw());
		c::lcd_print(3,"Right_Front_Current:%d",Right_Front_Drive.get_current_draw());
		c::lcd_print(4,"Right_Back_Current:%d",Right_Back_Drive.get_current_draw());
	}

		if (master.get_digital_new_press(DIGITAL_DOWN)){
			SwitchDrive =! SwitchDrive;
		}
		if (master.get_digital_new_press(DIGITAL_UP)){
			CatapultStop =! CatapultStop;
		}
		if(master.get_digital_new_press(DIGITAL_A) && Left_Arm.get_position() < 40 && Right_Arm.get_position() < 40) {
			CapFlip = true;
		}
		if(master.get_digital_new_press(DIGITAL_B)){
			FlagHeight = true;
		}

		//--------------------------------------------// Controller Screen

		if (SwitchDrive == false){
			master.set_text(2,0,"Fast Movement     ");
		}
		else {
			master.set_text(2,0,"Slow Movement     ");
		}

		//--------------------------------------------// Drive Train

		if (SwitchDrive == false){
			driveCoast();
			Left_Front_Drive.move(master.get_analog(ANALOG_LEFT_Y));
			Left_Back_Drive.move(master.get_analog(ANALOG_LEFT_Y));
			Right_Front_Drive.move(master.get_analog(ANALOG_RIGHT_Y));
			Right_Back_Drive.move(master.get_analog(ANALOG_RIGHT_Y));
		}
		else {
			driveHold();
			Left_Front_Drive.move(master.get_analog(ANALOG_LEFT_Y) * .6);
			Left_Back_Drive.move(master.get_analog(ANALOG_LEFT_Y) * .6);
			Right_Front_Drive.move(master.get_analog(ANALOG_RIGHT_Y) * .6);
			Right_Back_Drive.move(master.get_analog(ANALOG_RIGHT_Y) * .6);
		}

		//--------------------------------------------// Ball Intake

		if (master.get_digital(DIGITAL_L1)){
			Ball_Intake.move_velocity(200);
		}
		else if (master.get_digital(DIGITAL_L2)){
			Ball_Intake.move_velocity(-200);
		}
		else {
			Ball_Intake.set_brake_mode(MOTOR_BRAKE_COAST);
			Ball_Intake.move_velocity(0);
		}

		//--------------------------------------------// Catapult

		if (Catapult_Potentiometer.get_value() > 2085 && CatapultStop == false){
			Catapult.move_velocity(200);
		}
		else if (master.get_digital(DIGITAL_LEFT)){
			Catapult.move_velocity(200);
		}
		else {
			Catapult.set_brake_mode(MOTOR_BRAKE_BRAKE);
			Catapult.move_velocity(0);
		}

		//--------------------------------------------// Cap Flipper

		if (master.get_digital(DIGITAL_R1)){
			Left_Arm.move_velocity(180);
			Right_Arm.move_velocity(180);
		}
		else if (master.get_digital(DIGITAL_R2)){
			Left_Arm.move_velocity(-180);
			Right_Arm.move_velocity(-180);
		}
		else if (CapFlip == true){
			flipCap();
			CapFlip = false;
		}
		else if (FlagHeight == true){
			Left_Arm.move_absolute(252,200);
		  Right_Arm.move_absolute(252,200);
			if (Left_Arm.get_position() > 250 && Right_Arm.get_position() > 250){
				FlagHeight = false;
			}
		}
		else {
			if (Left_Arm.get_position() < 40 && Right_Arm.get_position() < 40){
				Left_Arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
				Right_Arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
			}
			else {
				Left_Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
				Right_Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
			}
			Left_Arm.move_velocity(0);
			Right_Arm.move_velocity(0);
		}
		delay(20);
	}
}
