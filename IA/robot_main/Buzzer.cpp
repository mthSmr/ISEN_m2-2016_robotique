/*
   To change this license header, choose License Headers in Project Properties.
   To change this template file, choose Tools | Templates
   and open the template in the editor.
*/

/*
   File:   Buzzer.cpp
   Author: BenoitP

   Created on 7 december 2016, 11:22
*/
#include "Buzzer.h"
#include <StandardCplusplus.h>
#include <vector>
#include "Arduino.h"


Buzzer::Buzzer() {          //Par defaut on fait rien.
}

Buzzer::Buzzer(int newPin) {
  this->pin = newPin;
  pinMode(this->pin, OUTPUT); //definition du pin Buzzer
}

void Buzzer::PlaySon() {         //Par defaut on fait rien

}

void Buzzer::PlaySon(int frequency) {         //Joue un seul Son

  if (frequency != 0) {
    tone(this->pin, frequency); //A MODIFIER VITE PAR CE QU'IL FAUT TESTER MA
  } else
  {
    noTone(this->pin);
  }
}

void Buzzer::PlayMelody(int melody) {
  int doo = 523;
  int ree = 587;
  int mii = 659;
  int faa = 698;
  int sol = 783;
  int laa = 880;
  int sii = 987;

  int delayRythme = 300;
  int delayAttente = 100;

  int song_welcom[] = {doo, 2, doo, 2, sii, 1, sii, 1}; //Faire une fonction pour optimiser le son.


  switch (melody)
  {
    case WELCOMSONG: //[1]
      this->PlaySon(doo); //do
      delay(delayRythme);
      this->PlaySon(0);
      delay(delayAttente);
      this->PlaySon(doo); //do
      delay(delayRythme);
      this->PlaySon(0);
      delay(delayAttente);
      this->PlaySon(sii); //do
      delay(delayRythme / 2);
      this->PlaySon(0);
      delay(delayAttente / 2);
      this->PlaySon(sii); //do
      delay(delayRythme / 2);
      this->PlaySon(0);
      delay(delayAttente / 2);
      break;
    case MENUNEXT: //A TESTER... [2]
      this->PlaySon(doo); //do
      delay(delayRythme / 2);
      this->PlaySon(0);
      break;

    case FACILE:     // [4]
      this->PlaySon(587.33); //ré
      delay(250);
      this->PlaySon(783.99);  //sol
      delay(250);
      this->PlaySon(783.99);      //sol
      delay(250);
      this->PlaySon(698.46); //fa
      delay(250);
      this->PlaySon(587.33);  //ré
      delay(250);
      this->PlaySon(622.25); //ré#
      delay(500);
      this->PlaySon(783.99);    //sol
      delay(500);
      this->PlaySon(698.46); //fa
      delay(500);
      this->PlaySon(587.33);  //ré
      delay(250);
      this->PlaySon(622.25); //ré#
      delay(500);
      this->PlaySon(0);

      break;


    default:
    case VALIDATE: //A TESTER... [3]
      this->PlaySon(doo); //do
      delay(delayRythme / 2);
      this->PlaySon(0);
      delay(delayRythme / 2);
      this->PlaySon(mii); //do
      delay(delayRythme / 2);
      this->PlaySon(0);
      delay(delayRythme / 2);
      this->PlaySon(sol); //do
      delay(delayRythme / 2);
      this->PlaySon(0);
      delay(delayRythme / 2);
      this->PlaySon(doo * 2); //do
      delay(delayRythme / 2);
      this->PlaySon(0);
      break;
      //On Joue Rien...
      break;
  }


}

