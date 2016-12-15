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

#include <vector>
#include "Motor.h"
#include "Arduino.h"
#include "Sensor.h"
#include "Button.h"
#include "Led.h"


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
	ControlPanel* getControls();

	//setters
	void setControls(ControlPanel* newControlPanel);

    //utilitaire
    void addMotor(Motor *const);
    void addSensor(Sensor *const);
	void addLed(Led *const);
    
    //for demo
    void dodger(ControlPanel *const, Led *const);
    void lineFollower(ControlPanel *const, Led *const);
    void joystick(ControlPanel *const buttonPanel, Led *const leds);
    
    //user programs
    void firmataProcess(ControlPanel *const buttonPanel, Led *const leds);
    void arduino();

	//others
    bool checkLeft();
    bool checkRight();
    bool checkCenter();
    void updateSensor();
    void updateSensorUnder();
    bool checkLineLeft();
    bool checkLineRight();

};

#endif /* PROGRAM_H */

