#include "main.h"
#include "lcd_functions.hpp"

bool leftButton = false;
bool centerButton = false;
bool rightButton = false;

void leftPressed(){
  leftButton = true;
}

void centerPressed(){
  centerButton = true;
}

void rightPressed(){
  rightButton = true;
}

//Always keep at 1 for competition
//Different # after autonomousChoice to select auto w/o LCD
int autonomousChoice = 1;

int selectAutonomous(){
  lcd::set_text(0, "Select Autonomous:");
  while(1){
    lcd::register_btn0_cb(leftPressed);
    lcd::register_btn1_cb(centerPressed);
    lcd::register_btn2_cb(rightPressed);
    if (leftButton == true){
      autonomousChoice -= 1;
      leftButton = false;
    }
    if (rightButton == true){
      autonomousChoice += 1;
      rightButton = false;
    }
    if (centerButton == true){
      break;
    }
    if (autonomousChoice > 12){
      autonomousChoice = 1;
    }
    if (autonomousChoice < 1){
      autonomousChoice = 12;
    }
    if (autonomousChoice == 1){
      lcd::set_text(1, "Blue Front Main");
    }
    else if (autonomousChoice == 2){
      lcd::set_text(1, "Blue Front HI");
    }
    else if (autonomousChoice == 3){
      lcd::set_text(1, "Blue Back Main");
    }
    else if (autonomousChoice == 4){
      lcd::set_text(1, "Blue Back Combo");
    }
    else if (autonomousChoice == 5){
      lcd::set_text(1, "Blue Back Across");
    }
    else if (autonomousChoice == 6){
      lcd::set_text(1, "Red Front Main");
    }
    else if (autonomousChoice == 7){
      lcd::set_text(1, "Red Front HI");
    }
    else if (autonomousChoice == 8){
      lcd::set_text(1, "Red Back Main");
    }
    else if (autonomousChoice == 9){
      lcd::set_text(1, "Red Back Combo");
    }
    else if (autonomousChoice == 10){
      lcd::set_text(1, "Red Back Across");
    }
    else if (autonomousChoice == 11){
      lcd::set_text(1, "Skills");
    }
    else if (autonomousChoice == 12){
      lcd::set_text(1, "Nothing");
    }
    //Prevents overload on the cortex
    delay(10);
  }
  lcd::clear_line(0);
  lcd::set_text(0, "Autonomous Selected:");
  return autonomousChoice;
}
