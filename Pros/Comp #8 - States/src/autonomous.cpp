#include "main.h"
#include "robot/define_items.hpp"
#include "robot/robot_functions.hpp"
#include "robot/lcd_functions.hpp"
#include "autonomous/headers/all_autons.hpp"

void autonomous() {
  lcd::clear();
  lcd::shutdown();
  /*centerPressed();

  //All autons go here
  switch(selectAutonomous()){
    case 1:
      blue_front_main();
      break;
    case 2:
      blue_front_HI();
      break;
    case 3:
      blue_back_main();
      break;
    case 4:
      blue_back_combo();
      break;
    case 5:
      blue_back_across();
      break;
    case 6:
      red_front_main();
      break;
    case 7:
      red_front_HI();
      break;
    case 8:
      red_back_main();
      break;
    case 9:
      red_back_combo();
      break;
    case 10:
      red_back_across();
      break;
    case 11:
      skills();
      break;
    case 12:
      nothing();
      break;
    }*/

//-------- Blue Front --------//
  //blue_front_main();
  //blue_front_HI();

//-------- Blue Back --------//
  //blue_back_main();
  //blue_back_combo();
  //blue_back_across();

//-------- Red Front --------//
  red_front_main();
  //red_front_HI();

//-------- Red Back --------//
  //red_back_main();
  //red_back_combo();
  //red_back_across();

//-------- Skills --------//
  //skills();

//-------- Nothing --------//
  //nothing();

}
