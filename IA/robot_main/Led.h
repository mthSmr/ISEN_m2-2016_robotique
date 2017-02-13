/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Led.h /!\ works only for the adafruit RGB LED 
 */

#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
#include "StandardCplusplus.h"
#include "vector"

class Led {

	public:
		private: int pin;				//the pin to which the LED is attached
    
    public:
      int number;						//the number of leds that are on the same pin
      std::vector<int> color {r,v,b};	//used to store the color parameters 
      Adafruit_NeoPixel strip;			//used to instanciate a serie of leds
      int r;							//the RGB levels, each from 0 to 255
      int v;
      int b;
    //TODO: classe color ac nom, code rvb convertisseur hexa
	public:
		Led(int, int);					//Constructor
		bool init();					//Initialisation of the Adafruit neopixel function
		std::vector<int> getColor();	//Getter
		void setColor(int, int, int);	//Setter
};

#endif /* LED_H */

