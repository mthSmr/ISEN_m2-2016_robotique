/*
   To change this license header, choose License Headers in Project Properties.
   To change this template file, choose Tools | Templates
   and open the template in the editor.
*/

/*
   File:   Program.cpp
   Author: Mathilde

   Created on 22 novembre 2016, 14:32
*/


#include "Arduino.h"
#include "ControlPanel.h"
#include "Button.h"
#include "Program.h"
#include "Led.h"



Program::Program() {
}

Program::Program(int motorNbr, int sensorNbr) {
  this->motorList.reserve(motorNbr);
  this->sensorList.reserve(sensorNbr);
}

std::vector<Motor*> Program::getMotorList()
{
  return motorList;
}

std::vector<Sensor*> Program::getSensorList()
{
  return sensorList;
}

std::vector<Led*> Program::getLedList()
{
  return ledList;
}

ControlPanel Program::getControls()
{
  return this->controls;
}

void Program::setControls(ControlPanel* newControlPanel)
{
  this->controls = newControlPanel;
}

void Program::addMotor(Motor *const newMotor)
{
  this->motorList.push_back(newMotor);
}

void Program::addSensor(Sensor *const newSensor)
{
  this->sensorList.push_back(newSensor);
}

void Program::addLed(Led * const newLeds)
{
  this->ledList.push_back(newLeds);
}

void Program::dodger(ControlPanel *const buttonPanel, Led *const leds)
{
  leds->setColor(1, 250, 49);//bleu foncé
  delay(250);

  do {

    this->updateSensor("distance");
	for (int i = 0; i < this->sensorList.size(); i++) {
		if (this->sensorList[i]->getType() == SensorType::infraR && this->sensorList[i]->getPosition() == 0 && this->sensorList[i]->getValue() == true) {
			motorList[0]->setDirection(false);
			motorList[1]->setDirection(true);
			motorList[0]->setSpeed(0);
			motorList[1]->setSpeed(150);
			delay(1000);
		}
		else if (this->sensorList[i]->getType() == SensorType::infraR && this->sensorList[i]->getPosition() == 1 && this->sensorList[i]->getValue() == true) {
			motorList[0]->setDirection(true);
			motorList[1]->setDirection(false);
			motorList[0]->setSpeed(150);
			motorList[1]->setSpeed(0);
			delay(250);
		}
		else if (this->sensorList[i]->getType() == SensorType::infraR && this->sensorList[i]->getPosition() == -1 && this->sensorList[i]->getValue() == true) {
			motorList[0]->setDirection(true);
			motorList[1]->setDirection(false);
			motorList[0]->setSpeed(0);
			motorList[1]->setSpeed(150);
			delay(250);
		}
		else {
			motorList[0]->setDirection(true);
			motorList[1]->setDirection(false);
			motorList[0]->setSpeed(200);
			motorList[1]->setSpeed(200);
		}
		delay(70);
	}
  }
  while (buttonPanel->analyze() != 5);
  delay(200);
  this->motorList[0]->setSpeed(0);
  this->motorList[1]->setSpeed(0);
}

void Program::lineFollower(ControlPanel *const buttonPanel, Led *const leds) {

	int premierCapt = 0;
	int etat0 = 0, etat1 = 0, etat = 0;
	int i = 0;
	 
  leds->setColor(254, 0, 27);//orange foncé
  for (int i = 0; i < this->sensorList.size(); i++) {
	  if (this->sensorList[i]->getType() != SensorType::line) {

		  premierCapt++;
	  }
  }
  do {
    updateSensor("line");


//		Serial.print(premierCapt);
//		Serial.print(":  ");
//		Serial.println(this->sensorList[premierCapt]->getValue());
//		Serial.print(premierCapt+1);
//  	Serial.print(":  ");
		Serial.println(this->sensorList[premierCapt]->getValue());
		
      if (this->sensorList[premierCapt]->getValue() == true && this->sensorList[premierCapt + 1]->getValue() == false) {
		  
//		Serial.println("Tourner gauche");
      motorList[0]->setDirection(true);
      motorList[1]->setDirection(false);
      motorList[0]->setSpeed(75);
	  motorList[1]->setSpeed(0);
//		delay(200);

      }
      else if (this->sensorList[premierCapt + 1]->getValue() == true && this->sensorList[premierCapt]->getValue() == false) {

//		Serial.println("Tourner droite");
      motorList[0]->setDirection(true);
      motorList[1]->setDirection(false);
      motorList[0]->setSpeed(0);
      motorList[1]->setSpeed(75);
//		delay(200);

      }
      else {

//		Serial.println("Tourner tout droit");
      motorList[0]->setDirection(true);
      motorList[1]->setDirection(false); 
      motorList[0]->setSpeed(150);
      motorList[1]->setSpeed(150);

      }

    delay(80);
  }
  while (buttonPanel->analyze() != 5);
  delay(200);
  this->motorList[0]->setSpeed(0);
  this->motorList[1]->setSpeed(0);
}



void Program::joystick(ControlPanel *const buttonPanel, Led *const leds) {

  leds->setColor(136, 29, 66);
  bool loop = true;

  while (loop) {

    delay(250);
    switch (buttonPanel->analyze()) {

      case 1 : // rightBtn
        leds->setColor(88, 0, 41);//bleu foncé
        this->motorList[0]->setDirection(true);
        this->motorList[1]->setDirection(false);
        this->motorList[0]->setSpeed(125);
        this->motorList[1]->setSpeed(0);
        break;

      case 2: // leftBtn
        leds->setColor(44, 255, 117);//bleu ciel
        this->motorList[0]->setDirection(true);
        this->motorList[1]->setDirection(false);
        this->motorList[0]->setSpeed(0);
        this->motorList[1]->setSpeed(75);
        break;

      case 3 : // downBtn
        leds->setColor(121, 249, 28);//violet
        this->motorList[0]->setDirection(false);
        this->motorList[1]->setDirection(true);
        this->motorList[0]->setSpeed(125);
        this->motorList[1]->setSpeed(75);
        break;

      case 4 : // upBtn
        leds->setColor(129, 83, 20);//framboise
        this->motorList[0]->setDirection(true);
        this->motorList[1]->setDirection(false);
        this->motorList[0]->setSpeed(125);
        this->motorList[1]->setSpeed(75);
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

void Program::arduino() {

}

void Program::updateSensor(String sensorToUpdate) {
  if (sensorToUpdate == "distance") {
    for (int i = 0; i < this->sensorList.size(); i++)
    {
      if (this->sensorList[i]->getType() == SensorType::infraR) {
        this->sensorList[i]->read();
      }
    }
  }
  if (sensorToUpdate == "line") {
	  for (int i = 0; i < this->sensorList.size(); i++)
	  {
		  if (this->sensorList[i]->getType() == SensorType::line) {
			  this->sensorList[i]->read();
		  }
	  }
  }
}

bool Program::checkRight() {
  bool result = false;
  for (int i = 0; i < this->sensorList.size(); i++)
  {
    if (this->sensorList[i]->getValue() && this->sensorList[i]->getPosition() < 0)
    {
      result = true;
    }
  }

  return result;
}

bool Program::checkLeft() {
  bool result = false;
  for (int i = 0; i < this->sensorList.size(); i++)
  {
    if (this->sensorList[i]->getValue() && this->sensorList[i]->getPosition() > 0)
    {
      result = true;
    }
  }

  return result;
}

bool Program::checkCenter() {
  bool result = false;
  for (int i = 0; i < this->sensorList.size(); i++)
  {
    if (this->sensorList[i]->getValue() && this->sensorList[i]->getPosition() == 0)
    {
      result = true;
    }
  }

  return result;
}

//void checkLineSensor() {
//  for (int i = 0; i < 2; i++) {
//
//    if (i == 0) {
//      Serial.println("Capteur gauche");
//    }
//    else {
//      Serial.println("Capteur droit");
//    }
//    digitalWrite(sensCommand[i], HIGH);
//    delay(5);
//    rawtcrt[i] = analogRead(sensData[i]);
//    Serial.println(rawtcrt[i]);
//    if (rawtcrt[i] < colorThreshold) {
//      bwtcrt[i] = 0;
//    }
//    else {
//      bwtcrt[i] = 1;
//    }
//    Serial.println(bwtcrt[0]);
//    Serial.println(bwtcrt[1]);
//    delay(5);
//    digitalWrite(sensCommand[i], LOW);
//  }
