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

#include <StandardCplusplus.h>
#include <vector>

#define WELCOMSONG 1    //Son de bienvenu
#define MENUNEXT 2      //A Chaque Changement De Menu
#define VALIDATE 3      //quand on appuis sur le bouton au milieu.


class Buzzer {

private:
    int pin;

	int doo = 523.25;
	int doH = 554.37;
	int ree = 587.33;
	int reH = 622.25;
	int mii = 659.26;
	int faa = 698.46;
	int faH = 739.99;
	int sol = 783.99;
	int solH = 830.61;
	int laa = 880;
	int laH = 932.33;
	int sii = 987.77;

	int delayRythme = 300;
	int delayAttente = 100;

	std::vector<int> welcomeSong; 
	std::vector<int> menuNext;
	std::vector<int> validate;
    
public:
    //Son ne pas oublier la fonction qui défini le pin
    //Les fonctions qui jour les Buzzer.
    Buzzer();
    Buzzer(int); //definition du pin speaker

	void setDelayRythme(int time);
	void setDelayAttente(int time);
    
    void playSon(int);
	void playSon(int frequency, int time);
	void linkKey(char key); //TODO
	void playKey(char key);	//TODO

	void playNote(int octave, char note);
	void playNote(int octave, char note, char tone);
	void playMode();		//TODO

	void createMelody();	//TODO
	void playMelody(int melody);
    void playMusic(std::vector<int>);
    
};

#endif /* Buzzer_H */
