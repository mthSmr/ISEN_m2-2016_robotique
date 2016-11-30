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

#include "Led.h"
#include "Menu.h"
#include "Button.h"
#include "ControlPanel.h"



Menu::Menu() {
    this->locations = 0;
    this->choice =-1;
}

Menu::Menu(int locationsNbr){
    this->locations = locationsNbr;
    this->choice = -1;
}



//getters / setters

int Menu::getLocations(){
    return this->locations;
}

void Menu::setLocations(int locationsNbr){
    this->locations = locationsNbr;
}



//utilitary

void Menu::runChoice(Program const *robot, ControlPanel const *buttonPanel, Led const *leds){
        
        
        switch(this->choice){
            
            case 0 : // bleu:evitement d'obstacle
                robot->dodger(buttonPanel, leds);
                break;
                
            case 1 : // orange:suiveur de ligne
                break;
                
            case 2: //user progrm
                
                break;
                
            case 3 : // 
                break;
                
            default:
                break;
        }
    
}

void Menu::runMenu(Program const *robot, ControlPanel const *buttonPanel, Led const *leds){
     int tempChoice = 0; 
     switch(buttonPanel->analyze()){
        
            case 1 : // rightBtn
                this->choice++;
                delay(250);
                break;
                
            case 2: // leftBtn
                this->choice--;
                delay(250);
                break;
                
            case 3 : // downBtn
                delay(250);
                break;
                
            case 4 : // upBtn
                delay(250);
                break;
                
            case 5 : // validateBtn
                this->choice=tempChoice;
                runChoice(robot,buttonPanel,leds);
                break;
                
            default:
                break;
        }

        tempChoice = abs(choice)%locations;
        
        if (tempChoice == 0){
          leds->setColor(0, 128, 255);//bleu:evitement d'obstacle
          
        }
        if(tempChoice == 1){
          leds->setColor(231, 1, 62);//orange:suiveur de ligne
        }
        
    
}

