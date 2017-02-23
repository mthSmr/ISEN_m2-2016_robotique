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


static void (Motor::*interruptFunction_p)();

//************************************************************************
//	Constructor with parameters
//	Arguments : the input 1 pin, the input 2 pin, the enable pin
//	Return : nothing
//************************************************************************

Motor::Motor(int newPinInput1, int newPinInput2, int newEnable) {
    this->pinInput1 = newPinInput1;
    this->pinInput2 = newPinInput2;
    this->pinEnable = newEnable;
	interruptFunction_p = &doCount;
    Motor::setSpeed(0);
    Motor::setDirection(true);
}

Motor::Motor(){
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

float Motor::getRealSpeed()
{
	return realSpeed;
}

bool Motor::getDirection() {
	return this->direction;
}

int Motor::getEncoderPos()
{
	return encoderPos;
}

float Motor::geta0()
{
	return a0;
}

float Motor::geta1()
{
	return a1;
}

float Motor::getb0()
{
	return b0;
}

float Motor::getb1()
{
	return b1;
}

float* Motor::getPower()
{
	return power;
}

float * Motor::getEk()
{
	return ek;
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
    analogWrite( this->pinEnable, newSpeed );
}

void Motor::setRealSpeed(float newRealSpeed)
{
	realSpeed = newRealSpeed;
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

void Motor::setEncoderPos(int newEncoderPos)
{
	encoderPos = newEncoderPos;
}

void Motor::seta0(float newValue)
{
	a0 = newValue;
}

void Motor::seta1(float newValue)
{
	a1 = newValue;
}

void Motor::setb0(float newValue)
{
	b0 = newValue;
}

void Motor::setb1(float newValue)
{
	b1 = newValue;
}


//utilitary

//************************************************************************
//	Initialization of the pin of the motor
//	Arguments : none
//	Return : nothing
//************************************************************************
bool Motor::init() {

	pinMode(this->pinEnable, OUTPUT);   // Sorties commande  moteur
	pinMode(this->pinInput1, OUTPUT);
	pinMode(this->pinInput2, OUTPUT);
}

//************************************************************************
//  Initialization of motor control
//  Arguments : interrupt pin plus constant of the motor
//  Return : nothing
//************************************************************************
void Motor::initControl(int interrupt, float newa0, float newa1, float newb0, float newb1)
{
	{
		seta0(newa0);
		seta1(newa1);
		setb0(newb0);
		setb1(newb1);

		// Interruption de l'encodeur A en sortie 5 (pin 18)
		//attachInterrupt(interrupt, handleInterrupt, RISING);		// increase counter of Motor when speed sensor pin goes High

		// Initialisation sortie moteur à 0
		setSpeed(0);
		delay(300);                // Pause de 0,3 sec pour laisser le temps au moteur de s'arréter si celui-ci est en marche

	}
}

void Motor::handleInterrupt()
{
	interruptFunction_p;
}

void Motor::doCount()
{
	encoderPos++;  // increase +1 the counter value
 Serial.println("doCount");
}

float Motor::percentPower()
{
	return -1 * a1 * power[1] + (-1) * a0 * power[2] + b1 * ek[1] + b0 * ek[2];
}

void Motor::addPowerValue(float newPower)
{
	power[2] = power[1];
	power[1] = power[0];
	power[0] = newPower;
}

void Motor::addEkValue(float newEk)
{
	ek[2] = ek[1];
	ek[1] = ek[0];
	ek[0] = newEk;
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


