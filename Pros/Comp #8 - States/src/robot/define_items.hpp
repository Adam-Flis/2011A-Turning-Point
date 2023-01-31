#include "main.h"

#ifndef DEFINE_ITEMS_HPP
#define DEFINE_ITEMS_HPP

//Change slot program is downloaded to
//prosv5 upload --slot [number]

//Motor and sensor ports
#define Left_Front_Port 1
#define Left_Back_Port 2
#define Right_Front_Port 3
#define Right_Back_Port 4
#define Ball_Intake_Port 5
#define Catapult_Port 6
#define Left_Arm_Port 11
#define Right_Arm_Port 12
#define Catapult_Potentiometer_Port 'a'

//Delcare motors and sensors
extern Motor Left_Front_Drive;
extern Motor Left_Back_Drive;
extern Motor Right_Front_Drive;
extern Motor Right_Back_Drive;
extern Motor Ball_Intake;
extern Motor Catapult;
extern Motor Left_Arm;
extern Motor Right_Arm;
extern ADIAnalogIn Catapult_Potentiometer;
extern Controller master;

#endif
