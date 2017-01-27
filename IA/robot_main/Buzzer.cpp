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

//#include <StandardCplusplus.h>
//#include <vector> 

#include "Adafruit_NeoPixel.h"

#include "Buzzer.h"
#include "Arduino.h"


Buzzer::Buzzer() {          //Par defaut on fait rien.
}

Buzzer::Buzzer(int newPin) {
    this->pin = newPin;
    pinMode(this->pin, INPUT); //definition du pin Buzzer

	welcomeSong.push_back(doo);		//définition des melodies préenregistrées
	welcomeSong.push_back(doo);
	welcomeSong.push_back(sii);
	welcomeSong.push_back(sii);	

	menuNext.push_back(doo);

	validate.push_back(doo);
	validate.push_back(doo*2);
}

void Buzzer::setDelayRythme(int time) {
	delayRythme = time;
}

void Buzzer::setDelayAttente(int time) {
	delayAttente = time;
}

void Buzzer::playSon(float frequency){          //Joue un seul Son
  
  if(frequency>10 && frequency<20000){ 
        tone(this->pin,frequency); 
		delay(delayRythme);
    }
    noTone(this->pin);
   
 }

void Buzzer::playSon(float frequency, int time) {          //Joue un seul Son

	if (frequency>10 && frequency<20000) {
		tone(this->pin, frequency); 
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

void Buzzer::playKey(char key) {	//TODO: jouer une note à l'appuis d'une touche associée

}


//	Fonction playNote	//
/*
La gamme par défaut pour le buzzer est la 4 (celle avec le la/A 880Hz)(cf le wiki des octaves)
	==> L'octave 4 en musique = à l'octave 0 dans le code. 

Pour simplifier la théorie musical toussa toussa on passe à l'octave supéieure en
multipliant par 2 et à l'ocatve inférieure en divisant par 2.
*/
void Buzzer::playNote(int octave, char note) {   

	if (octave < 1) {		// on limite le nombre d'octave par sécurité
		octave = 1;
	}
	else if (octave > 7) {
		octave = 7;
	}

	octave = floor(octave)-4;			//on empèche les puissances à virgules et on ramène l'octave 4 à 0 (cf le gros commentaire au dessus)
	int delta = pow(2, octave);

	if(note == 'c'){
		playSon(this->doo*delta);
	}
	else if(note == 'd')
	{
		playSon(this->ree*delta);
	}
	else if (note == 'e')
	{
		playSon(this->mii*delta);
	}
	else if (note == 'f')
	{
		playSon(this->faa*delta);
	}
	else if (note == 'g')
	{
		playSon(this->sol*delta);
	}
	else if (note == 'a')
	{
		playSon(this->laa*delta);
	}
	else if (note == 'b')
	{
		playSon(this->sii*delta);
	}

	delay(delayRythme);
	noTone(this->pin);

}

void Buzzer::playNote(int octave, char note, char tone) {   //surcharge pour les demi-tons

	if (octave < 1) {		// on limite le nombre d'octave par sécurité
		octave = 1;
	}
	else if (octave > 7) {
		octave = 7;
	}

	octave = floor(octave)-4;			//on empèche les puissances à virgules et on ramène l'octave 4 à 0 (cf le gros commentaire au dessus)
	int delta = pow(2, octave);

	if ( (note == 'c' && tone == 'h') || (note == 'd' && tone == 'b') )
	{
		playSon(this->doH*delta);
	}
	else if ((note == 'd' && tone == 'h') || (note == 'e' && tone == 'b'))
	{
		playSon(this->reH*delta);
	}
	else if ((note == 'f' && tone == 'h') || (note == 'g' && tone == 'b'))
	{
		playSon(this->faH*delta);
	}
	else if ((note == 'g' && tone == 'h') || (note == 'a' && tone == 'b'))
	{
		playSon(this->solH*delta);
	}
	else if ((note == 'a' && tone == 'h') || (note == 'b' && tone == 'b'))
	{
		playSon(this->laH*delta);
	}

	delay(delayRythme);
	noTone(this->pin);

}

void Buzzer::playMode() {	//TODO: mode piano grace à la fct linkKey

}

void Buzzer::createMelody() {	//TODO:

}


void Buzzer::playMusic(std::vector<float> melody) {

	for (auto note : melody)
	{
		playSon(note);
		delay(delayAttente);
	}

	//int song_welcom[]={doo,2,doo,2,sii,1,sii,1}; //Faire une fonction pour optimiser le son.
}

void Buzzer::playMelody(int melody) {
	switch (melody)
	{
	case 0: playMusic(welcomeSong);
		break;
	case 1: playMusic(menuNext);
		break;
	case 2: playMusic(validate);
	default:
		break;
	}

}

  
