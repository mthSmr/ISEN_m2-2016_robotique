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


	int motorNumber;
    int pinInput1; // Commande de sens moteur, Input 1
    int pinInput2; // Commande de sens moteur, Input 2  
    int pinEnable;  // Commande de vitesse moteur, Output Enabled1
    float speed;
	float realSpeed;
    bool direction; //direction is forward? TRUE/FALSE
	int encoderPos;

	//constants linked to motor
	float b0;
	float b1;
	float a0;
	float a1;

	float ek[3];		//errors over the present state + the 2 last states
	float power[3];	//power over the present state + the 2 last states


public:


    Motor::Motor(int, int, int);
    Motor::Motor(int, int, int, float, bool);
    Motor();
    
    //getter
    float getSpeed();
	float getRealSpeed();
    bool getDirection();
	int getEncoderPos();
	float geta0();
	float geta1();
	float getb0();
	float getb1();
	float* getPower();
	float* getEk();
    
    //setter
  void setSpeed(float);
	void setRealSpeed(float);
  void setDirection(bool);
	void setEncoderPos(int);
	void seta0(float);
	void seta1(float);
	void setb0(float);
	void setb1(float);

	//utilitary 
	bool init();
	void initControl(int, float, float, float, float);
	static void handleInterrupt();
	void doCount();  // counts from the speed sensor
	float percentPower();
	void addPowerValue(float);
	void addEkValue(float);

	//void moveForward(int distance);
	//void moveBackward(int distance);
	//void stop();

};

#endif /* MOTOR_H */

