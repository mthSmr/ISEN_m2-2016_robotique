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

class Buzzer {

public:
    int pin;
    
public:
    //Son ne pas oublier la fonction qui défini le pin
    //Les fonctions qui jour les Buzzer.
    Buzzer();
    Buzzer(int); //definition du pin speaker
    
    
};

#endif /* Buzzer_H */
