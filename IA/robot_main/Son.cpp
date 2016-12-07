/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Son.cpp
 * Author: BenoitP
 * 
 * Created on 7 december 2016, 11:22
 */
#include "Son.h"
#include <StandardCplusplus.h>
#include <vector> 
#include "Arduino.h"


Son::Son() {          //Par defaut on fait rien.
}

Son::Son(int newPin) {
    this->pin = newPin;
    pinMode(this->pin, INPUT); //definition du pin Son
}


  
