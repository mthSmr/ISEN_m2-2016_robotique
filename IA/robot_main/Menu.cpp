/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.cpp
 * Author: Mathilde
 * 
 * Created on 18 octobre 2016, 15:11
 */
#include "Menu.h"
#include "Led.h"
#include "Button.h"
#include "ControlPanel.h"
#include "Buzzer.h"



Menu::Menu() {
    this->locations = 0;
    this->choice = 0;
    this->tempChoice = 0;
}

Menu::Menu(int locationsNbr){
    this->locations = locationsNbr;
    this->choice = 0;
    this->tempChoice = 0;
}



//getters / setters

int Menu::getLocations(){
    return this->locations;
}

void Menu::setLocations(int locationsNbr){
    this->locations = locationsNbr;
}



//utilitary

void Menu::runChoice(Program *const robot, ControlPanel *const buttonPanel, Led *const leds){
        
        Serial.print("choice = ");
            Serial.println(this->choice);
        switch(this->choice){
            
            case 0 : // bleu:evitement d'obstacle
                robot->dodger(buttonPanel, leds);
                break;
                
            case 1 : // orange:suiveur de ligne
                robot->joystick(buttonPanel, leds);
                break;
                
            case 2: //	user progrm
                
                break;
                
            case 3 : // scratch programmation
                break;
                
            default:
                break;
        }
    this->choice = 0;
    this->tempChoice = 0;
}

void Menu::runMenu(Program *const robot, ControlPanel *const buttonPanel, Led *const leds, Buzzer *const buzzer ){
  
     switch(buttonPanel->analyze()){
        
            case 1 : // rightBtn
                this->tempChoice++;
                buzzer->PlayMelody(MENUNEXT);
                delay(250);
                break;
                
            case 2: // leftBtn
                this->tempChoice--;
                buzzer->PlayMelody(MENUNEXT);
                delay(250);
                break;
                
            case 3 : // downBtn
                buzzer->PlayMelody(MENUNEXT);
                delay(250);
                break;
                
            case 4 : // upBtn
                buzzer->PlayMelody(MENUNEXT);
                delay(250);
                break;
                
            case 5 : // validateBtn
                buzzer->PlayMelody(VALIDATE);
                runChoice(robot,buttonPanel,leds);
                break;
                
            default:
                break;
        }

        choice = abs(this->tempChoice)%locations;
        
        if (choice == 0){
          leds->setColor(0, 128, 255);//bleu:evitement d'obstacle
          
        }
        if(choice == 1){
          leds->setColor(231, 1, 62);//orange:suiveur de ligne
        }
    
}

