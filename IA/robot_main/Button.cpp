/* 
 * File:   Button.cpp
 * Author: Mathilde
 * 
 * Created on 17 octobre 2016, 17:45
 */

#include "StandardCplusplus.h"
#include "vector" 
#include "Arduino.h"
#include "Button.h"

//************************************************************************
//						Constructors
//************************************************************************

Button::Button() {
}

//************************************************************************
//	Constructor with parameters
//	Argument : the pin you want the button to be assigned
//	Return : nothing
//************************************************************************

Button::Button(int newPin) {
    this->pin = newPin;
    pinMode(this->pin, INPUT);  //set the pin mode of the pin in argument as an INPUT
}

//************************************************************************
//						Setter
//************************************************************************

int Button::getValue(){
    return this->value;
}

//************************************************************************
//						Specific class methods
//************************************************************************

//************************************************************************
//	Read the value of the button
//	Argument : none
//	Return : HIGH if the button is pressed; LOW if the button is not pressed
//************************************************************************

void Button::readValue(){
    this->value = digitalRead(this->pin);
}

