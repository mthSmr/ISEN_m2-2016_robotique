/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motor.h
 * Author: Mathilde
 *
 * Created on 17 octobre 2016, 16:53
 */


#ifndef MOTOR_H
#define MOTOR_H

//#include <ctime>

#include "Arduino.h"
#include "ControlPanel.h"
#include "Button.h"


class Motor {
    
private:

      int pinInput1;	//Command moteur direction, Input 1
      int pinInput2;	//Command motor direction, Input 2  
      int en;			//Command motor speed, Output Enable1
      float speed;		//Store the speed of the motor
      bool direction;	//direction is forward? TRUE/FALSE
      

public:
    
	//Constructors
	Motor(int, int, int);
    Motor(int, int, int, float, bool);
    
    //getter
    float getSpeed();
    bool getDirection();
    
    //setter
    void setSpeed(float);
    void setDirection(bool);

	//utilitary 
	bool init();	//initialization function
	//void moveForward(int distance);
	//void moveBackward(int distance);
	//void stop();

};

#endif /* MOTOR_H */

