/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Led.h
 */

#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h> //Ajouter en local ce truc crétin !!! 
#include <StandardCplusplus.h>
#include <vector>


class Led {

public:
    private: int pin;
    
    public:
      int number;
      bool state;
      bool blink;
      std::vector<int> color {r,v,b};
      Adafruit_NeoPixel strip;
      int r; 
      int v;
      int b;
    //TODO: classe color ac nom, code rvb convertisseur hexa

    
 
    
public:
    Led(int, int);
    bool init();
    std::vector<int> getColor();
    void setColor(int, int, int);

};

#endif /* LED_H */

