#include "main.h"

#ifndef DEFINE_ITEMS_HPP
#define DEFINE_ITEMS_HPP

//Motor and sensor ports
#define Left_Front_Port 4
#define Left_Back_Port 3
#define Right_Front_Port 2
#define Right_Back_Port 1
#define Ball_Intake_Port 13
#define Catapult_Port 15
#define Rake_Port 12
#define Cap_Stacker_Port 14
#define Catapult_Potentiometer_Port 'a'
#define Rake_Potentiometer_Port 'b'
#define Cap_Stacker_Potentiometer_Port 'c'
#define Gyro_Port 'd'
//#define Vision_Port 20


//Delcare motors and sensors
extern Motor Left_Front_Drive;
extern Motor Left_Back_Drive;
extern Motor Right_Front_Drive;
extern Motor Right_Back_Drive;
extern Motor Ball_Intake;
extern Motor Catapult;
extern Motor Rake;
extern Motor Cap_Stacker;
extern ADIAnalogIn Catapult_Potentiometer;
extern ADIAnalogIn Rake_Potentiometer;
extern ADIAnalogIn Cap_Stacker_Potentiometer;
extern ADIGyro Gyro;
//extern Vision Vision1;
extern Controller Main;


#endif
