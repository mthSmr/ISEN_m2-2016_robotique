/*
   To change this license header, choose License Headers in Project Properties.
   To change this template file, choose Tools | Templates
   and open the template in the editor.
*/

/*
   File:   Sensor.cpp
   Author: Mathilde

   Created on 11 octobre 2016, 14:05
*/

#include <Arduino.h>
#include "Sensor.h"
#include "SensorType.h"

//************************************************************************
//	Constructor
//************************************************************************

Sensor::Sensor() {
  setType(SensorType::undefined);
}

//*****************************************************************************************************************************************************************************************************
//	Constructor with parameters
//	Arguments : the digitam pin attached to the sensor, the analog pin attached to the sensor, the threshold of the analog pin to set the sensor, the sensor type, the position on the robot <0 if left
//	Return : nothing
//*****************************************************************************************************************************************************************************************************

Sensor::Sensor(int newDigitalPin, int newAnalogPin, int newCap, SensorType type, int pos) {
  this->digitalPin = newDigitalPin;
  this->analogPin = newAnalogPin;
  this->cap = newCap;
  this->position = pos;
  setType(type);
  pinMode(this->digitalPin, OUTPUT);
}

//************************************************************************
//	Read the value of the analog pin of the sensor
//	Arguments : none
//	Return : nothing
//************************************************************************

void Sensor::read() {
  int analog;
  // print out the value you read:
  digitalWrite(this->digitalPin, HIGH);
  delay(5);
  analog = analogRead(analogPin);
  
  //Serial.print("capteur ");
  //Serial.println(analogPin);
  //Serial.print(" = ");
  //Serial.println(analog);
  //delay(1000);
  
  delay(5);
  digitalWrite(this->digitalPin, LOW);

  if (analog >= this->cap) {
    this->value = true ;
  } else {
    this->value = false ;
  }
}

//************************************************************************
//	Setter
//************************************************************************

void Sensor::setType(SensorType newType) {
  type = newType;
}

void Sensor::setCap(int newCap) {
  this->cap = newCap;
}

void Sensor::setPosition(int pos)
{
  this->position = pos;
}

//************************************************************************
//	Getters
//************************************************************************

SensorType Sensor::getType() {
  return this->type;
}

int Sensor::getCap() {
  return this->cap;
}

bool Sensor::getValue() {
  return this->value;
}


int Sensor::getPosition()
{
  return this->position;
}






