/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Led.cpp
 * Author: Mathilde
 * 
 * Created on 25 octobre 2016, 16:29
*/

#include <Adafruit_NeoPixel.h>
#include <StandardCplusplus.h>
#include <vector>
#include "Led.h"
#include "Arduino.h"


Led::Led(int newPin, int newNumber) {
    this->pin = newPin;
    this->number = newNumber;
    this->state = false;
    this->blink = false;
    this->color = {0,0,0};
}

bool Led::init(){

    this->strip = Adafruit_NeoPixel(this->number, this->pin, NEO_GRB + NEO_KHZ800);
    this->strip.begin();// Initialise toute les led à 'off'
    this->strip.show(); //display   
}

std::vector<int> Led::getColor(){
   return this->color;
}

void Led::setColor(int newR, int newV, int newB){
    this->color = {newR, newV, newB};

    int cpt;
    for(cpt = 0; cpt < this->number; cpt++){
      this->strip.setPixelColor(cpt,newR, newV, newB);
    }
    this->strip.show();
}


