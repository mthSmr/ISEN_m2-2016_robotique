/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.h
 * Author: Mathilde
 *
 * Created on 18 octobre 2016, 15:11
 */

#include "Led.h"
#include "ControlPanel.h"
#include "Program.h"

#ifndef MENU_H
#define MENU_H

class Menu {
    int choice;
    int locations;
    
public:    
    Menu();
    Menu(int);
    
    //getters
    int getLocations();
     
    //utilitary
    void runMenu(Program const*, ControlPanel const*, Led const*);
    void runChoice(Program const*, ControlPanel const*, Led const*);
    
private:
    //setters
    void setLocations(int);
    
};

#endif /* MENU_H */

