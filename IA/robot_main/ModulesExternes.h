#include "Arduino.h"
#ifndef MODULESEXTERNES_H
#define MODULESEXTERNES_H
#include "SensorType.h"
#include "PortType.h"

#include "dht.h"
#include <StandardCplusplus.h>
#include "Adafruit_NeoPixel.h"
#include "Led.h"

/*
 *  BASE Des Capteurs Modules Externes : 
 *     N°     Nom                   Type        
 *     1      TemperatureSensor     MakeBlock
 *     2      HumiditySensor        MakeBlock
 *     3      TouchSensor           MakeBlock
 *     4      PIRSensor             Makeblock
 *     5      Undefined             Undefined
 *     
 *     Mappage du RJ12 :              Fils Banc de test:
 *     
 *     1      -> Analogique I         Blanc
 *        2   -> Analogique II        Noir
 *     3      -> VCC 5V               Rouge
 *        4   -> GND                  Vert
 *     5      -> SDA                  Jaune
 *        6   -> SCL                  Bleu
 */

class ModulesExternes {

private:
    int analogPin;  //detection des capteurs par rapport à cet attribut
    int DATA;  
    int temperature;
    int humidite;
    int touche;
    int pir;
    
    PortType porttype;
    SensorType sensortype;

public:
    ModulesExternes();
    
    //getter
    int getAnalogPin();
    int getDATA();
    int getTemperature();
    int gethumidity();
    int getTouche();
    int getPir();
    


    //setter
    void setAnalogPin(int);
    void setDATA(int);
    void setTemperature(int);
    void sethumidity(int);
    void setTouche(int);
    void setPir(int);
    void setPortType(PortType porttype); 
    void setSensorType(SensorType sensortype);
    
    //utilitaire
    void initPIR();
    dht runTemperature();
    int runTouch();
    void runPIR();
    void demotouch(Led *const led);   
    int DataModulesExternes(int, int);
};
#endif
