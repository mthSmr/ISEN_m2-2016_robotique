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
          this->motorList[0]->setDirection(false);
          this->motorList[1]->setDirection(true);
          
        this->updateSensor();
        
        if (this->checkCenter()){
          //Serial.println("check center ");
            this->motorList[0]->setSpeed(0);
            this->motorList[1]->setSpeed(0);
            delay(250);
            this->motorList[0]->setDirection(true);
            this->motorList[1]->setDirection(false);
            this->motorList[0]->setSpeed(75);
            this->motorList[1]->setSpeed(75);
        }
        else if (this->checkLeft()){
          //Serial.println("check right ");
            this->motorList[0]->setSpeed(75);
            this->motorList[1]->setSpeed(0);
        }
        else if (this->checkRight()) {
          //Serial.println("check left ");
            this->motorList[0]->setSpeed(0);
            this->motorList[1]->setSpeed(75);
        } 
        else{
          //Serial.println("see nothing ");
            this->motorList[0]->setSpeed(100);
            this->motorList[1]->setSpeed(100);
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

void Program::joystick(){
    
}

void Program::firmata(){
    
}

void Program::arduino(){
    
}

void Program::updateSensor() {
  for(int i = 0; i< this->sensorList.size(); i++)
  {
    this->sensorList[i]->read(); 
//    Serial.print("capteur ");
//    Serial.print(i);
//    Serial.print(" = ");
//    Serial.println(this->sensorList[i]->value);
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

