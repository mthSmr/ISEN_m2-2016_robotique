/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motor.cpp
 * Author: Mathilde
 * 
 * Created on 17 octobre 2016, 16:53
 */

#include <Adafruit_NeoPixel.h>
//#include "Arduino.h"
#include "Motor.h"




//************************************************************************
//	Constructor with parameters
//	Arguments : the input 1 pin, the input 2 pin, the enable pin
//	Return : nothing
//************************************************************************

Motor::Motor(int newPinInput1, int newPinInput2, int newEn) {
    this->pinInput1 = newPinInput1;
    this->pinInput2 = newPinInput2;
    this->en = newEn;
    Motor::setSpeed(0);
    Motor::setDirection(true);
}

//*********************************************************************************************************************************
//	Constructor with parameters
//	Arguments : the input 1 pin, the input 2 pin, the enable pin, the basic speed, the direction (true = forward, false = backward)
//	Return : nothing
//*********************************************************************************************************************************

Motor::Motor(int newPinInput1, int newPinInput2, int newEn, float speed = 0, bool direction = true) {
    Motor::setSpeed(speed);
    Motor::setDirection(direction);
}

//************************************************************************
//	Getters
//************************************************************************

float Motor::getSpeed() {
	return this->speed;
}

bool Motor::getDirection() {
	return this->direction;
}

//************************************************************************
//	Setter
//************************************************************************

void Motor::setSpeed(float newSpeed){
  //settings max and min limits
     if (newSpeed > 255){
        newSpeed = 255;  
      }
      else if (newSpeed < 0){
        newSpeed = -newSpeed;  
      }

  //register speed value
    this->speed = newSpeed;
    analogWrite( this->en, newSpeed );
}

//***************************************************************************
//	Set the direction of the motor
//	Arguments : the direction of the motor (true = forward, false = backward)
//	Return : nothing
//***************************************************************************

void Motor::setDirection(bool newDirection){
    this->direction = newDirection;
    //handle clockwise
    if(this->direction){
      // Clockwise
      digitalWrite( this->pinInput1, LOW );             // Clockwise
      digitalWrite( this->pinInput2, HIGH );
    }
    else{
      digitalWrite( this->pinInput1, HIGH );             // anti-Clockwise
      digitalWrite( this->pinInput2, LOW );
    }
      
}

//************************************************************************
//	Initialization of the pin of the motor
//	Arguments : none
//	Return : nothing
//************************************************************************

bool Motor::init() {

	pinMode(this->en, OUTPUT);   // Sorties commande  moteur 1
	pinMode(this->pinInput1, OUTPUT);
	pinMode(this->pinInput2, OUTPUT);
}

/*
void Motor::moveForward(int distance)
{
	int begin = time_t() ;
	int clock;
	//set direction avant
	setDirection(true);
	//lancement du moteur
	setSpeed(75);

	//incr�mentation du timer
	while (this->getSpeed()*clock <= distance) {
		clock = begin - time_t();
	}
	//arret du moteur
	setSpeed(0);
}

void Motor::moveBackward(int distance)
{
	int begin = time_t();
	int clock;
	//set direction avant
	setDirection(false);
	//lancement du moteur
	setSpeed(75);

	//incr�mentation du timer
	while (this->getSpeed()*clock <= distance) {
		clock = begin - time_t();
	}
	//arret du moteur
	setSpeed(0);
}

void Motor::stop()
{
	setSpeed(0);
}
*/


