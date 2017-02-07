/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Button.h
 * Author: Mathilde
 *
 * Created on 17 octobre 2016, 17:45
 */



#ifndef BUTTON_H
#define BUTTON_H

class Button {

public:
    int pin;			//Used to store the pin assignement of the button	
    int value;			//Used to store the value of the button when we analyse it
    
public:
    Button();			//Basic constructor of the class Button
    Button(int pin);	//Constructor of the class Button with the pin assignement
    int getValue();		//Get the value of the  button and store it in the value member
    void readValue();	//Read the value of the button: HIGH if not pressed, LOW if pressed
};

#endif /* BUTTON_H */

