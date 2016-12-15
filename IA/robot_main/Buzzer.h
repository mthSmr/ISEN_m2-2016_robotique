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

#include <vector>

#define WELCOMSONG 1    //Son de bienvenu
#define MENUNEXT 2      //A Chaque Changement De Menu
#define VALIDATE 3      //quand on appuis sur le bouton au milieu.


class Buzzer {

public:
    int pin;
    
public:
    //Son ne pas oublier la fonction qui défini le pin
    //Les fonctions qui jour les Buzzer.
    Buzzer();
    Buzzer(int); //definition du pin speaker
    
    void PlaySon();
    void PlaySon(int);

    void PlayMelody();
    void PlayMelody(int);
    
};

#endif /* Buzzer_H */
