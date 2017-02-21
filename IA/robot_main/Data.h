#ifndef Data_h
#define Data_h
#include "Data.h"
#include <Arduino.h>
#include <SoftwareSerial.h>  
#define ESP8266 Serial2

class Data
{
public: 
    int a; // Angle
    int p; // Puissance 
    int memory=0;
public:
    /////////////////////Constructors////////////////////
    Data();
    Data(int,int);
    /////////////////////Setters////////////////////
    void setData(int,int);
    void setA(int);
    void setP(int);
    /////////////////////Getters////////////////////
    int getA();
    int getP();
    ///////////////////////
    int analyze(); //Function that analyze the data and return a use case
    Data receiveData(); // Function that receive a string from device and return a Data object
};

#endif
