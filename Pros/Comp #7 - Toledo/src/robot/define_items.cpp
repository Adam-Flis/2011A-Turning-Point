#include "main.h"
#include "define_items.hpp"

//Define motors, controller, and sensors
Motor Left_Front_Drive (Left_Front_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor Left_Back_Drive (Left_Back_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor Right_Front_Drive (Right_Front_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
Motor Right_Back_Drive (Right_Back_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
Motor Ball_Intake (Ball_Intake_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
Motor Catapult (Catapult_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
Motor Left_Arm (Left_Arm_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
Motor Right_Arm (Right_Arm_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
ADIAnalogIn Catapult_Potentiometer (Catapult_Potentiometer_Port);
Controller master (CONTROLLER_MASTER);
