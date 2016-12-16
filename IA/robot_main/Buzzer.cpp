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
  int doo=523;
  int ree=587;
  int mii=659;
  int faa=698;
  int sol=783;
  int laa=880;
  int sii=987;

  int delayRythme=300;
  int delayAttente=100;

  int song_welcom[]={doo,2,doo,2,sii,1,sii,1}; //Faire une fonction pour optimiser le son.
  
  
  switch (melody)
    {
      case WELCOMSONG:
              this->PlaySon(doo); //do
              delay(delayRythme);
              this->PlaySon(0);
              delay(delayAttente);
              this->PlaySon(doo); //do
              delay(delayRythme);
              this->PlaySon(0);
              delay(delayAttente);
              this->PlaySon(sii); //do
              delay(delayRythme/2);
              this->PlaySon(0);
              delay(delayAttente/2);
              this->PlaySon(sii); //do
              delay(delayRythme/2);
              this->PlaySon(0);
              delay(delayAttente/2);
        break;
      default:
       //On Joue Rien...
       break;
}
  
  
}
  
