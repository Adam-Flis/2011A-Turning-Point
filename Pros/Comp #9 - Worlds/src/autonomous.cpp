#include "main.h"
#include "robot/define_items.hpp"
#include "robot/robot_functions.hpp"
#include "robot/lcd_functions.hpp"
#include "autonomous/headers/all_autons.hpp"

void autonomous() {
/*lcd::clear();
  lcd::shutdown();
  centerPressed();

  //All autons go here
  switch(selectAutonomous()){
    case 1:
      blue_front();
      break;
    case 2:
      red_back();
      break;
    case 3:
      red_front();
      break;
    case 4:
      red_back();
      break;
    case 5:
      nothing();
      break;
    } */

//-------- Blue Front --------//
  //blue_front();

//-------- Blue Back --------//
  //blue_back();
  //blue_back_no_shoot();

//-------- Red Front --------//
  //red_front();

//-------- Red Back --------//
  red_back_no_shoot();
  //red_back_no_shoot();

//-------- Nothing --------//
  //nothing();
}
