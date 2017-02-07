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
#include <Arduino.h>

using namespace std;

//************************************************************************
//						Constructors
//************************************************************************
Buzzer::Buzzer() {          
}

//************************************************************************
//	Constructor with parameters
//	Arguments : the pin you want to attach to contro the buzzer
//	Return : nothing
//************************************************************************

Buzzer::Buzzer(int newPin) {
    this->pin = newPin;
    pinMode(this->pin, INPUT); 

	welcomeSong.push_back(doo);		
	welcomeSong.push_back(doo);
	welcomeSong.push_back(sii);
	welcomeSong.push_back(sii);	

	menuNext.push_back(doo);

	validate.push_back(doo);
	validate.push_back(doo*2);
}


//************************************************************************
//						Setters
//************************************************************************
void Buzzer::setDelayRythme(int time) {
	delayRythme = time;
}

void Buzzer::setDelayAttente(int time) {
	delayAttente = time;
}

//************************************************************************
//						Specific methods
//************************************************************************

//************************************************************************
//	Play Sound
//	Arguments : the frequency of the note you want to play
//	Return : nothing
//************************************************************************

void Buzzer::playSon(float frequency){          
  
  if(frequency>10 && frequency<20000){ 
        tone(this->pin,frequency); 
		delay(delayRythme);
    }
    noTone(this->pin);
   
 }

//************************************************************************
//	Play sound (overloaded)
//	Arguments : the frequency and the time of the note you play
//	Return : nothing
//************************************************************************

void Buzzer::playSon(float frequency, int time) {

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

//************************************************************************
//	
//	Arguments : 
//	Return : 
//************************************************************************

void Buzzer::linkKey(char key) {

}

//************************************************************************
//	
//	Arguments : 
//	Return : 
//************************************************************************

void Buzzer::playKey(char key) {

}


//************************************************************************
//	
//	Arguments : 
//	Return : 
//************************************************************************

//	Fonction playNote	//
/*
La gamme par d�faut pour le buzzer est la 4 (celle avec le la/A 880Hz)(cf le wiki des octaves)
	==> L'octave 4 en musique = � l'octave 0 dans le code. 

Pour simplifier la th�orie musical toussa toussa on passe � l'octave sup�ieure en
multipliant par 2 et � l'ocatve inf�rieure en divisant par 2.
*/
void Buzzer::playNote(int octave, char note) {   

	if (octave < 1) {		// on limite le nombre d'octave par s�curit�
		octave = 1;
	}
	else if (octave > 7) {
		octave = 7;
	}

	octave = floor(octave)-4;			//on emp�che les puissances � virgules et on ram�ne l'octave 4 � 0 (cf le gros commentaire au dessus)
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

//************************************************************************
//	
//	Arguments : 
//	Return : 
//************************************************************************

void Buzzer::playNote(int octave, char note, char tone) {   //surcharge pour les demi-tons

	if (octave < 1) {		// on limite le nombre d'octave par s�curit�
		octave = 1;
	}
	else if (octave > 7) {
		octave = 7;
	}

	octave = floor(octave)-4;			//on emp�che les puissances � virgules et on ram�ne l'octave 4 � 0 (cf le gros commentaire au dessus)
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

//************************************************************************
//	
//	Arguments : 
//	Return : 
//************************************************************************

void Buzzer::playMode() {	//TODO: mode piano grace � la fct linkKey

}

//************************************************************************
//	
//	Arguments : 
//	Return : 
//************************************************************************

void Buzzer::createMelody() {	//TODO:

}

//************************************************************************
//	Play music
//	Arguments : a vector of note
//	Return : nothing
//************************************************************************

void Buzzer::playMusic(std::vector<float> melody) {

	for (int i = 0; i < melody.size(); i++ )
	{
		playSon(melody[i]);
		delay(delayAttente);
	}

	//int song_welcom[]={doo,2,doo,2,sii,1,sii,1}; //Faire une fonction pour optimiser le son.
}

//************************************************************************
//	Play default melody
//	Arguments : 0->WelcomeSound; 1->menuNext; 3->validate
//	Return : nothing
//************************************************************************

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
