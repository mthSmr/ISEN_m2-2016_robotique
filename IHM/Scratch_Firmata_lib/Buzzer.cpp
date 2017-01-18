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

#include <StandardCplusplus.h>
#include <vector> 

#include <Adafruit_NeoPixel.h>

#include "Buzzer.h"
#include "Arduino.h"


Buzzer::Buzzer() {          //Par defaut on fait rien.
}

Buzzer::Buzzer(int newPin) {
    this->pin = newPin;
    pinMode(this->pin, INPUT); //definition du pin Buzzer

	welcomeSong.push_back(doo);		//définition des melodies préenregistrées
	welcomeSong.push_back(0);
	welcomeSong.push_back(doo);
	welcomeSong.push_back(0);
	welcomeSong.push_back(sii);
	welcomeSong.push_back(0);
	welcomeSong.push_back(sii);	

	menuNext.push_back(doo);

	validate.push_back(doo);
	validate.push_back(0);
	validate.push_back(mii);
	validate.push_back(0);
	validate.push_back(sol);
	validate.push_back(0);
	validate.push_back(doo*2);
}

void Buzzer::setDelayRythme(int time) {
	delayRythme = time;
}

void Buzzer::setDelayAttente(int time) {
	delayAttente = time;
}

void Buzzer::playSon(int frequency){          //Joue un seul Son
  
  if(frequency>10 && frequency<20000){ 
        tone(this->pin,frequency); //A MODIFIER VITE PAR CE QU'IL FAUT TESTER MA
		delay(5000);
		noTone(this->pin);
    } else
    {
      noTone(this->pin);
    }
 }

void Buzzer::playSon(int frequency, int time) {          //Joue un seul Son

	if (frequency>10 && frequency<20000) {
		tone(this->pin, frequency); //A MODIFIER VITE PAR CE QU'IL FAUT TESTER MA
		delay(time*1000);
		noTone(this->pin);
	}
	else
	{
		noTone(this->pin);
	}
}

void Buzzer::linkKey(char key) {	//TODO: associer une note à une touche clavier

}

void Buzzer::playSon(char key) {	//TODO: jouer une note à l'appuis d'une touche associée

}


//	Fonction playNote	//
/*
La gamme par défaut pour le buzzer est la 4 (celle avec le la/A 880Hz)(cf le wiki des octaves)
	==> L'octave 4 en musique = à l'octave 0 dans le code. 

Pour simplifier la théorie musical toussa toussa on passe à l'octave supéieure en
multipliant par 2 et à l'ocatve inférieure en divisant par 2.
*/
void Buzzer::playNote(String note, int octave) {   

	if (octave < 1) {		// on limite le nombre d'octave par sécurité
		octave = 1;
	}
	else if (octave > 7) {
		octave = 7;
	}

	octave = floor(octave)-4;			//on empèche les puissances à virgules et on ramène l'octave 4 à 0 (cf le gros commentaire au dessus)
	int delta = pow(2, octave);

	if(note == "do" || note == "c"){
		playSon(this->doo*delta);
	}
	else if (note == "doH" || note == "cH")
	{
		playSon(this->doH*delta);
	}
	else if(note == "re" || note == "d")
	{
		playSon(this->ree*delta);
	}
	else if (note == "reH" || note == "dH")
	{
		playSon(this->reH*delta);
	}
	else if (note == "mi" || note == "e")
	{
		playSon(this->mii*delta);
	}
	else if (note == "fa" || note == "f")
	{
		playSon(this->faa*delta);
	}
	else if (note == "faH" || note == "fH")
	{
		playSon(this->faH*delta);
	}
	else if (note == "sol" || note == "g")
	{
		playSon(this->sol*delta);
	}
	else if (note == "solH" || note == "gH")
	{
		playSon(this->solH*delta);
	}
	else if (note == "la" || note == "a")
	{
		playSon(this->laa*delta);
	}
	else if (note == "laH" || note == "aH")
	{
		playSon(this->laH*delta);
	}
	else if (note == "si" || note == "b")
	{
		playSon(this->sii*delta);
	}

	delay(delayRythme);
	noTone(this->pin);

}

void Buzzer::playMode() {	//TODO: mode piano grace à la fct linkKey

}

void Buzzer::createMelody() {	//TODO:

}


void Buzzer::playMelody(std::vector<int> melody) {

	for each (int note in melody)
	{
		playSon(note);
	}

	//int song_welcom[]={doo,2,doo,2,sii,1,sii,1}; //Faire une fonction pour optimiser le son.

}

  
