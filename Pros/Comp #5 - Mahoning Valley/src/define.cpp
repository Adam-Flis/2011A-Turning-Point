#include "main.h"

/*
Define motors and sensor in this document
Don't forget to add the extern in the main.h file
*/

//prosv5 upload --slot [number]

#define Left_Front_Port 1
#define Left_Back_Port 2
#define Right_Front_Port 3
#define Right_Back_Port 4
#define Ball_Intake_Port 5
#define Catapult_Port 6
#define Left_Arm_Port 11
#define Right_Arm_Port 12
#define Catapult_Potentiometer_Port 'a'

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
