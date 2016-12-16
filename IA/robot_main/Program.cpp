/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Program.cpp
 * Author: Mathilde
 * 
 * Created on 22 novembre 2016, 14:32
 */


#include "Arduino.h"
#include "ControlPanel.h"
#include "Button.h"
#include "Program.h"
#include "Led.h"


Program::Program() {
}

Program::Program(int motorNbr, int sensorNbr){
  this->motorList.reserve(motorNbr);
  this->sensorList.reserve(sensorNbr);
}

void Program::addMotor(Motor const *newMotor){
    this->motorList.push_back(newMotor);
}

void Program::addSensor(Sensor const *newSensor){
    this->sensorList.push_back(newSensor);
}

void Program::dodger(ControlPanel const *buttonPanel, Led const *leds){
          delay(250);
          leds->setColor(1, 250, 49);//bleu foncé
      
    do{ 
          
        this->updateSensor();
        
        if (this->checkCenter()){
            this->motorList[0]->setDirection(false);
            this->motorList[1]->setDirection(true);
            this->motorList[0]->setSpeed(0);
            this->motorList[1]->setSpeed(75);
            delay(1000);
        }
        else if (this->checkLeft()){
			this->motorList[0]->setDirection(true);
			this->motorList[1]->setDirection(false);
            this->motorList[0]->setSpeed(75);
            this->motorList[1]->setSpeed(0);
            delay(250);
        }
        else if (this->checkRight()) {
			this->motorList[0]->setDirection(true);
			this->motorList[1]->setDirection(false);
			this->motorList[0]->setSpeed(0);
			this->motorList[1]->setSpeed(75);
			delay(250);
        } 
        else{
			this->motorList[0]->setDirection(true);
			this->motorList[1]->setDirection(false);
			this->motorList[0]->setSpeed(125);
			this->motorList[1]->setSpeed(75);
        }
        
    }
    while(buttonPanel->analyze() != 5);
    delay(250);
    this->motorList[0]->setSpeed(0);
    this->motorList[1]->setSpeed(0);
}

void Program::lineFollower(){
                //leds->setColor(254, 0, 27);//orange foncé
    
}

void Program::joystick(ControlPanel const *buttonPanel, Led const *leds){
  
	leds->setColor(136, 29, 66);
	bool loop = true;
                
  while(loop){
    //buttonPanel->analyze();
    delay(250);
    switch(buttonPanel->analyze()){
        
            case 1 : // rightBtn
                //delay(250);
                leds->setColor(88, 0, 41);//bleu foncé
                this->motorList[0]->setDirection(true);
                this->motorList[1]->setDirection(false);
                this->motorList[0]->setSpeed(125);
                this->motorList[1]->setSpeed(0);
                break;
                
            case 2: // leftBtn
                //delay(250);
                leds->setColor(44, 255, 117);//bleu ciel
                this->motorList[0]->setDirection(true);
                this->motorList[1]->setDirection(false);
                this->motorList[0]->setSpeed(0);
                this->motorList[1]->setSpeed(75);
                //delay(250);
                break;
                
            case 3 : // downBtn
                //delay(250);
                leds->setColor(121, 249, 28);//violet
                this->motorList[0]->setDirection(false);
                this->motorList[1]->setDirection(true);
                this->motorList[0]->setSpeed(125);
                this->motorList[1]->setSpeed(75);
                //delay(250);
                break;
                
            case 4 : // upBtn
                //delay(250);
                leds->setColor(129, 83, 20);//framboise
                this->motorList[0]->setDirection(true);
                this->motorList[1]->setDirection(false);
                this->motorList[0]->setSpeed(125);
                this->motorList[1]->setSpeed(75);
                //delay(250);
                break;
                
            case 5 : // validateBtn
                loop = false;
                break;
                
            default:
				this->motorList[0]->setSpeed(0);
				this->motorList[1]->setSpeed(0);
                break;
        }
    }

    this->motorList[0]->setSpeed(0);
    this->motorList[1]->setSpeed(0);
	delay(750);
}

void Program::firmata(){
    
}

void Program::arduino(){
    
}

void Program::updateSensor() {
  for(int i = 0; i< this->sensorList.size(); i++)
  {
    this->sensorList[i]->read();
  }
}

bool Program::checkRight() {
  bool result = false;
  for(int i = 0; i< this->sensorList.size(); i++)
  {
    if (this->sensorList[i]->value && this->sensorList[i]->position < 0)
    {
      result = true;
    }
  }

  return result;
}

bool Program::checkLeft() {
  bool result = false;
  for(int i = 0; i< this->sensorList.size(); i++)
  {
    if (this->sensorList[i]->value && this->sensorList[i]->position > 0)
    {
      result = true;
    }
  }

  return result;
}

bool Program::checkCenter() {
  bool result = false;
  for(int i = 0; i< this->sensorList.size(); i++)
  {
    if (this->sensorList[i]->value && this->sensorList[i]->position == 0)
    {
      result = true;
    }
  }

  return result;
}

