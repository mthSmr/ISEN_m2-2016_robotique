/*
   To change this license header, choose License Headers in Project Properties.
   To change this template file, choose Tools | Templates
   and open the template in the editor.
*/

/*
   File:   Program.h
   Author: Mathilde

   Created on 22 novembre 2016, 14:32
*/

#ifndef PROGRAM_H
#define PROGRAM_H

#include "vector"
#include "Motor.h"
#include "Sensor.h"
#include "Button.h"
#include "Led.h"
#include <Arduino.h>
#include "Data.h"
#include "Wifi.h"


class Program {

    std::vector<Motor*> motorList;		//used to store the motor list
    std::vector<Sensor*> sensorList;	//used to store the sensor list
    std::vector<Led*> ledList;			//used to store the led strips list
    ControlPanel* controls;				//used to store the control panel

  public:

	//Constructors
    Program();
    Program(int, int);

    //getters
    std::vector<Motor*> getMotorList();
    std::vector<Sensor*> getSensorList();
    std::vector<Led*> getLedList();
    ControlPanel getControls();

    //setters
    void setControls(ControlPanel* newControlPanel);

    //utilitaire
    void addMotor(Motor *const);		//add a motor object in the motor vector
    void addSensor(Sensor *const);		//add a sensor object in the sensor vector
    void addLed(Led *const);			//add a led strip object in the sensor vector

    //for demo
    void dodger(ControlPanel *const, Led *const, Led *const);			//obstacle doger program
    void lineFollower(ControlPanel *const, Led *const, Led  *const);	//lie follower program
    void joystick(ControlPanel *const , Led *const, Led *const);		//joystick program
	void useWifi(ControlPanel *const buttonPanel, Led *const leds, Led *const, Data *const);		//joystick with wi fi

    //user programs
    void arduino();			//slot for the user program

    //others
    //bool checkLeft();							//
    //bool checkRight();						//
    //bool checkCenter();						//
    void updateSensor(String sensorToUpdate);	//
//    void checkLineSensor();
};

#endif /* PROGRAM_H */

