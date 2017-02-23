/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Buzzer.h
 */

#ifndef BUZZER_H
#define BUZZER_H

#include "vector"

#define WELCOMSONG 0    //Son de bienvenu
#define MENUNEXT 1      //A Chaque Changement De Menu
#define VALIDATE 2      //quand on appuis sur le bouton au milieu.


class Buzzer {

private:
    int pin;						//Used to store the pin to which the buzzer will be attached
	int delayRythme = 300;			//Used to ...
	int delayAttente = 100;			//Used to ...

	std::vector<float> welcomeSong; //Vector of notes constituing the Welcome melody
	std::vector<float> menuNext;	//Vector of notes constituing the Menu next melody
	std::vector<float> validate;	//Vector of notes constituing the Valifdate melody
    
public:

	float doo = 523.25;				//The notes and the corresponding frequencies
	float doH = 554.37;
	float ree = 587.33;
	float reH = 622.25;
	float mii = 659.26;
	float faa = 698.46;
	float faH = 739.99;
	float sol = 783.99;
	float solH = 830.61;
	float laa = 880;
	float laH = 932.33;
	float sii = 987.77;

    Buzzer();						//Buzzer constructor
    Buzzer(int);					//Buzzer constructor with pin assignement

	void setDelayRythme(int time);	//Setters
	void setDelayAttente(int time);
    
	//Custom method

    void playSon(float);
	void playSon(float frequency, int time);
	void linkKey(char key); //TODO
	void playKey(char key);	//TODO

	void playNote(int octave, char note);
	void playNote(int octave, char note, char tone);
	void playMode();		//TODO

	void createMelody();	//TODO
	void playMelody(int melody);
    void playMusic(std::vector<float>);
    
};

#endif /* Buzzer_H */
