/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Program.h
 * Author: Mathilde
 *
 * Created on 22 novembre 2016, 14:32
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include <cstdlib>
#include <vector>
#include "Motor.h"
#include "Sensor.h"
#include "Button.h"
#include "Led.h"
#include "Arduino.h"

class Program {
	
  std::vector<Motor*> motorList;
  std::vector<Sensor*> sensorList;
  std::vector<Led*> ledList;
  ControlPanel* controls;
    
public:
    
    Program();
    Program(int,int);

	//getters
	std::vector<Motor*> getMotorList();
	std::vector<Sensor*> getSensorList();
	std::vector<Led*> getLedList();
	ControlPanel getControls();

	//setters
	void setControls(ControlPanel* newControlPanel);

    //utilitaire
    void addMotor(Motor *const);
    void addSensor(Sensor *const);
	void addLed(Led *const);
    
    //for demo
    void dodger(ControlPanel *const, Led *const);
    void lineFollower();
    void joystick(ControlPanel *const buttonPanel, Led *const leds);
    
    //user programs
    void arduino();

	//others
    bool checkLeft();
    bool checkRight();
    bool checkCenter();
    void updateSensor();

};

#endif /* PROGRAM_H */

