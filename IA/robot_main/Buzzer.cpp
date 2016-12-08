/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Buzzer.cpp
 * Author: BenoitP
 * 
 * Created on 7 december 2016, 11:22
 */
#include "Buzzer.h"
#include <StandardCplusplus.h>
#include <vector> 
#include "Arduino.h"

//Les Mélodies





Buzzer::Buzzer() {          //Par defaut on fait rien.
}

Buzzer::Buzzer(int newPin) {
    this->pin = newPin;
    pinMode(this->pin, INPUT); //definition du pin Buzzer
}

void Buzzer::PlaySon(){          //Par defaut on fait rien
  
}

void Buzzer::PlaySon(int frequency){          //Joue un seul Son
  
  if(frequency!=0){ 
        tone(this->pin,frequency); //A MODIFIER VITE PAR CE QU'IL FAUT TESTER MA
    } else
    {
      noTone(this->pin);
    }
  }

void Buzzer::PlayMelody(int melody){

  switch (melody)
    {
      case WELCOMSONG:
              this->PlaySon(523); //do
              delay(300);
              this->PlaySon(0);
              delay(100);
              this->PlaySon(523); //do
              delay(300);
              this->PlaySon(0);
              delay(100);
              this->PlaySon(523); //do
              delay(300);
              this->PlaySon(0);
              delay(100);
        break;
      default:
       //On Joue Rien...
       break;
}
  
  
}
  
