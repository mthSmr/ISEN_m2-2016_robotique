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


//************************************************************************
//	Constructor
//************************************************************************

Program::Program() {
}

//************************************************************************
//	Constructor with parameters
//	Arguments : the number of motors; the number of sensors
//	Return : nothing
//************************************************************************

Program::Program(int motorNbr, int sensorNbr) {
  this->motorList.reserve(motorNbr);
  this->sensorList.reserve(sensorNbr);
}

//************************************************************************
//	Getters
//************************************************************************

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

//************************************************************************
//	Setters
//************************************************************************

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

//************************************************************************
//	Program obstacle doger
//	Arguments : the button panel object, the two leds strip objects
//	Return : nothing
//************************************************************************

void Program::dodger(ControlPanel *const buttonPanel, Led *const ledFront, Led *const ledBack)
{
  ledFront->setColor(1, 250, 49);//bleu foncé
  ledBack->setColor(1, 250, 49);
  delay(250);

  do {

    this->updateSensor("distance");

    for (int i = 0; i < this->sensorList.size(); i++) {
      if (this->sensorList[i]->getType() == SensorType::infraR && this->sensorList[i]->getPosition() == 0 && this->sensorList[i]->getValue() == true) {

		//Serial.println("Reculer");
        motorList[0]->setDirection(true);
        motorList[1]->setDirection(false);
		motorList[1]->setSpeed(200);
		delay(20);
        motorList[0]->setSpeed(0);
        motorList[1]->setSpeed(100);
		i = 20;
        //delay(1000);
      }
      else if (this->sensorList[i]->getType() == SensorType::infraR && this->sensorList[i]->getPosition() == 1 && this->sensorList[i]->getValue() == true) {

		//Serial.println("tourner gauche");
		motorList[0]->setDirection(true);
		motorList[1]->setDirection(true);
		motorList[1]->setSpeed(0);
		motorList[0]->setSpeed(200);
		delay(20);
		motorList[0]->setSpeed(100);
		i = 20;
        //delay(250);
      }
	  else if (this->sensorList[i]->getType() == SensorType::infraR && this->sensorList[i]->getPosition() == 2 && this->sensorList[i]->getValue() == true) {

		  //Serial.println("tourner fort gauche");
		  motorList[0]->setDirection(true);
		  motorList[1]->setDirection(false);
		  motorList[0]->setSpeed(200);
		  motorList[1]->setSpeed(200);
		  delay(20);
		  motorList[0]->setSpeed(100);
		  motorList[1]->setSpeed(100);
		  i = 20;
		  //delay(250);
	  }
      else if (this->sensorList[i]->getType() == SensorType::infraR && this->sensorList[i]->getPosition() == -1 && this->sensorList[i]->getValue() == true) {
       
		//Serial.println("tourner droite");
		motorList[0]->setDirection(true);
		motorList[1]->setDirection(true);
		motorList[0]->setSpeed(0);
		motorList[1]->setSpeed(200);
		delay(20);
		motorList[1]->setSpeed(100);
		i = 20;
        //delay(250);
      }
	  else if (this->sensorList[i]->getType() == SensorType::infraR && this->sensorList[i]->getPosition() == -2 && this->sensorList[i]->getValue() == true) {

		  //Serial.println("tourner fort droite");
		  motorList[0]->setDirection(false);
		  motorList[1]->setDirection(true);
		  motorList[0]->setSpeed(200);
		  motorList[1]->setSpeed(200);
		  delay(20);
		  motorList[0]->setSpeed(100);
		  motorList[1]->setSpeed(100);
		  i = 20;
		  //delay(250);
	  }
      else if (this->sensorList[0]->getValue() == false && this->sensorList[1]->getValue() == false && this->sensorList[2]->getValue() == false && this->sensorList[3]->getValue() == false && this->sensorList[4]->getValue() == false && this->sensorList[5]->getValue() == false && this->sensorList[6]->getValue() == false){

		//Serial.println("Tout droit");
        motorList[0]->setDirection(true);
        motorList[1]->setDirection(true);
        motorList[0]->setSpeed(200);
        motorList[1]->setSpeed(200);
		delay(20);
		motorList[0]->setSpeed(100);
		motorList[1]->setSpeed(100);
		i = 20;
      }
      delay(50);
    }
  }
  while (buttonPanel->analyze() != 5);
  delay(200);
  this->motorList[0]->setSpeed(0);
  this->motorList[1]->setSpeed(0);
}

//************************************************************************
//	Program line follower
//	Arguments : the buton panel object, the two leds strip objects
//	Return : nothing
//************************************************************************

void Program::lineFollower(ControlPanel *const buttonPanel, Led *const ledFront, Led *const ledBack) {

  int premierCapt = 0;
  int etat0 = 0, etat1 = 0, etat = 0;
  int i = 0;

  ledFront->setColor(254, 0, 27);//orange foncé
  ledFront->setColor(254, 0, 27);

  for (int i = 0; i < this->sensorList.size(); i++) {
    if (this->sensorList[i]->getType() != SensorType::line) {

      premierCapt++;
    }
  }
  do {
    updateSensor("line");

	if (this->sensorList[premierCapt]->getValue() == true && this->sensorList[premierCapt + 1]->getValue() == false) {
	  
      etat = 1;

    }

    else if (this->sensorList[premierCapt + 1]->getValue() == true && this->sensorList[premierCapt]->getValue() == true && etat == 1) {
		
      etat= 0;
    }

    else if (this->sensorList[premierCapt + 1]->getValue() == true && this->sensorList[premierCapt]->getValue() == false) {
	  
      etat = 2;
    }

    else if (this->sensorList[premierCapt + 1]->getValue() == true && this->sensorList[premierCapt]->getValue() == true && etat == 2 ) {
	  
      etat = 0;
    }
    else if (this->sensorList[premierCapt + 1]->getValue() == false && this->sensorList[premierCapt]->getValue() == false && (etat == 1 || etat == 2)) {

      etat = etat;
    }
	else {
		
		etat = 0;
	}

    switch (etat)
    {
      case 0 :
        
          //Serial.println("Tourner tout droit");
          motorList[0]->setDirection(true);
          motorList[1]->setDirection(true);
		  motorList[1]->setSpeed(150);
		  motorList[0]->setSpeed(150);
		  delay(30);
          motorList[0]->setSpeed(80);
          motorList[1]->setSpeed(80);
        
        delay(50);
        break;
      case 1 :
        
          //Serial.println("Tourner gauche");
          motorList[0]->setDirection(true);
          motorList[1]->setDirection(true);
		  motorList[0]->setSpeed(0);
		  motorList[1]->setSpeed(150);
		  delay(30);
		  motorList[1]->setSpeed(80);
        
        delay(50);
        break;
      case 2 :
     
          //Serial.println("Tourner droite");
          motorList[0]->setDirection(true);
		  motorList[0]->setSpeed(150);
		  delay(30);
		  motorList[0]->setSpeed(80);
          motorList[1]->setDirection(true);
		  motorList[1]->setSpeed(0);
        
        delay(80);
      default:

        break;
    }
   
	Serial.println(etat);
	
  }
  while (buttonPanel->analyze() != 5);
  delay(200);
  this->motorList[0]->setSpeed(0);
  this->motorList[1]->setSpeed(0);
}


//************************************************************************
//	Joystick program
//	Arguments : the button panel object, the two leds strip objects
//	Return : nothing
//************************************************************************

void Program::joystick(ControlPanel *const buttonPanel, Led *const ledFront, Led *const ledBack) {

  ledFront->setColor(136, 29, 66);
  ledBack->setColor(136, 29, 66);
  bool loop = true;
  int state = 0;
  this->motorList[0]->setDirection(true);
  this->motorList[1]->setDirection(true);

  while (loop) {

    delay(250);

    switch (buttonPanel->analyze()) {

      case 1 : // rightBtn
        ledFront->setColor(88, 0, 41);//bleu foncé
        ledBack->setColor(88, 0, 41);
        if (state != 1) {
          Serial.print("Case 1 first time");
          this->motorList[0]->setDirection(true);
          this->motorList[1]->setDirection(true);
          delay(5);
          this->motorList[0]->setSpeed(125);
          this->motorList[1]->setSpeed(0);
        }
        break;

      case 2: // leftBtn
        ledFront->setColor(44, 255, 117);//bleu ciel
        ledBack->setColor(44, 255, 117);
        if (state != 2) {
          Serial.print("Case 2 first time");
          this->motorList[0]->setDirection(true);
          this->motorList[1]->setDirection(true);
          delay(5);
          this->motorList[0]->setSpeed(0);
          this->motorList[1]->setSpeed(125);
        }
        break;

      case 3 : // downBtn
        ledFront->setColor(121, 249, 28);//violet
        ledBack->setColor(121, 249, 28);
        if (state != 3) {
          Serial.print("Case 3 first time");
          this->motorList[0]->setDirection(false);
          this->motorList[1]->setDirection(false);
          delay(5);
          this->motorList[0]->setSpeed(125);
          this->motorList[1]->setSpeed(125);
        }
        break;

      case 4 : // upBtn
        ledFront->setColor(129, 83, 20);//framboise
        ledBack->setColor(129, 83, 20);
        if (state != 4) {
          Serial.print("Case 4 first time");
          this->motorList[0]->setDirection(true);
          this->motorList[1]->setDirection(true);
          delay(5);
          this->motorList[0]->setSpeed(125);
          this->motorList[1]->setSpeed(125);
        }
        break;

      case 5 : // validateBtn
        loop = false;
        break;

      default:
        this->motorList[0]->setSpeed(0);
        this->motorList[1]->setSpeed(0);
        break;
    }
    state = buttonPanel->analyze();
  }
  this->motorList[0]->setSpeed(0);
  this->motorList[1]->setSpeed(0);
  delay(750);
}

//************************************************************************
//	Wifi Joystick
//	Arguments : the button panel object, the two leds strip objects, the data objects
//	Return : nothing
//************************************************************************

void Program::useWifi(ControlPanel *const buttonPanel, Led *const ledFront, Led *const ledBack, Data *const data) {
	ledFront->setColor(255, 10, 255);
	ledBack->setColor(255, 10, 255);

	while (buttonPanel->analyze() != 3) {
		*data = data->receiveData();
		int a = data->getA();
		int p = data->getP();
		switch (data->analyze()) {
		case 0: // sleep
			delay(5);
			this->motorList[0]->setDirection(true);
			this->motorList[1]->setDirection(true);
			this->motorList[1]->setSpeed(0);
			this->motorList[0]->setSpeed(0);

			// Print pour test 
			//Serial.println("ARRET");
			break;
		case 1: // up
			delay(5);
			this->motorList[0]->setDirection(true);
			this->motorList[1]->setDirection(true);
			this->motorList[1]->setSpeed(240);
			this->motorList[0]->setSpeed(240);

			// Print pour test 
			//Serial.println("up");
			break;
		case 2:
			delay(5);
			this->motorList[0]->setDirection(true);
			this->motorList[1]->setDirection(true);
			this->motorList[0]->setSpeed(240);
			this->motorList[1]->setSpeed(200);
			// Print pour test 
			//Serial.println("up right");
			break;
		case 3:
			delay(5);
			this->motorList[0]->setDirection(true);
			this->motorList[1]->setDirection(true);
			this->motorList[0]->setSpeed(200);
			this->motorList[1]->setSpeed(100);
			//Serial.println("droite"); 
			break;
		case 4:
			delay(5);
			this->motorList[0]->setDirection(false);
			this->motorList[1]->setDirection(false);
			this->motorList[0]->setSpeed(240);
			this->motorList[1]->setSpeed(200);
			//Serial.println(" down right");
			break;
		case 5:
			delay(5);
			this->motorList[0]->setDirection(false);
			this->motorList[1]->setDirection(false);
			this->motorList[0]->setSpeed(240);
			this->motorList[1]->setSpeed(240);
			//Serial.println("down");
			break;
		case 6:
			delay(5);
			this->motorList[0]->setDirection(false);
			this->motorList[1]->setDirection(false);
			this->motorList[0]->setSpeed(200);
			this->motorList[1]->setSpeed(240);
			//Serial.println("down left");
			break;
		case 7:
			delay(5);
			this->motorList[0]->setDirection(true);
			this->motorList[1]->setDirection(true);
			this->motorList[0]->setSpeed(100);
			this->motorList[1]->setSpeed(200);
			//Serial.println("left");
			break;
		case 8:
			delay(5);
			this->motorList[0]->setDirection(true);
			this->motorList[1]->setDirection(true);
			this->motorList[0]->setSpeed(200);
			this->motorList[1]->setSpeed(240);
			//Serial.println("upleft");
			break;
		default:
			this->motorList[0]->setDirection(true);
			this->motorList[1]->setDirection(true);
			this->motorList[1]->setSpeed(0);
			this->motorList[0]->setSpeed(0);
			break;
		}
	}
}

//************************************************************************
//	User program
//	Arguments : none
//	Return : nothing
//************************************************************************

void Program::arduino() {

}

//************************************************************************
//	Sensor data updating function
//	Arguments : the type of sensor to update ("distance" or "line")
//	Return : nothing
//************************************************************************

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


//bool Program::checkRight() {
//  bool result = false;
//  for (int i = 0; i < this->sensorList.size(); i++)
//  {
//    if (this->sensorList[i]->getValue() && this->sensorList[i]->getPosition() < 0)
//    {
//      result = true;
//    }
//  }
//
//  return result;
//}

//bool Program::checkLeft() {
//  bool result = false;
//  for (int i = 0; i < this->sensorList.size(); i++)
//  {
//    if (this->sensorList[i]->getValue() && this->sensorList[i]->getPosition() > 0)
//    {
//      result = true;
//    }
//  }
//
//  return result;
//}

//bool Program::checkCenter() {
//  bool result = false;
//  for (int i = 0; i < this->sensorList.size(); i++)
//  {
//    if (this->sensorList[i]->getValue() && this->sensorList[i]->getPosition() == 0)
//    {
//      result = true;
//    }
//  }
//
//  return result;
//}

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
