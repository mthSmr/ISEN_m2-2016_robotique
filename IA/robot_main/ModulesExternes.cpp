#include "ModulesExternes.h"
#include "Arduino.h"
#include "dht.h"
#include "Adafruit_NeoPixel.h"
#include "Led.h"
#include <StandardCplusplus.h>


#define DEBUGON 0 //mettre a zero pour supprimer le debug dans le port Serie
#define DEBUGTEMPE 0
#define DEBUGHUMI 0

//Initialisation/Switch//
ModulesExternes::ModulesExternes(){
}

int ModulesExternes::getAnalogPin(){
  return analogPin;
}
int ModulesExternes::getDATA(){
  return DATA;
}
int ModulesExternes::getTemperature(){
  return temperature;
}
int ModulesExternes::gethumidity(){
  return humidite;
}
int ModulesExternes::getTouche(){
  return touche;
}
int ModulesExternes::getPir(){
  return pir;
}

int ModulesExternes::DataModulesExternes(int portModuleExterne, int numeroCapteurBaseTX )
{  //port Module Externe : 1 ou 2 (a l'arriere du robot)
   //numero CapteurBaseTX : 1 - ... (C.F Base TX dabs Modules externes.h)

   /*Fonctionement : identification du port    -> Definition des pin utilisable
   *                 identification du capteur -> Definition du mode de fontionement des pin si dessu
                     Récuperation de la DATA
   */

   //DEFINITION DU PORT :: dans le robot TX 4 Ports possible 1 2 3 ou 4  dans V3 seul 1 et 2 sont accéssible
    int pinI=0;  //les pin de lecture data
    int pinII=0; 
    switch(portModuleExterne)
      { case 1: //port 1 associé à A2 et A3 ce sont les pin de lecture de DATA du port 1
          pinI=A4; 
          pinII=A5;
          break;
        case 2: //port 2 associé à A4 et A5 ce sont les pin de lecture de DATA du port 2
          pinI=A2;
          pinII=A3;
          break;
        //Casse 3 et 4 à faire + default
      }

    switch(numeroCapteurBaseTX)
       { case 1: // 1      TemperatureSensor     MakeBlock
          dht DHT1;
          digitalWrite(pinII, LOW);
          this->analogPin = pinI; //je lui dit de lire le pinI
          DHT1=this->runTemperature();
          this->DATA=DHT1.temperature;
          delay(150);
          
          if(DEBUGON==1)
            {
          Serial.print("Appel du l'Etat du 'TemperatureSensor' sur le port : ");
          Serial.print(portModuleExterne);
          Serial.println();
          Serial.print("Le 'TemperatureSensor' affiche une température de ");
          Serial.print(DHT1.temperature);
          Serial.print("°C");
          Serial.println();
          delay(150);
             }
             
          //lecture du capteur de temperature => temperature               
          break;
          
         case 2: // 2      HumiditySensor        Makeblock
          dht DHT2;
          digitalWrite(pinII, LOW);
          this->analogPin = pinI; //je lui dit de lire le pinI
          DHT2=this->runTemperature();
          this->DATA=DHT2.humidity;
          delay(150);
          
          if(DEBUGON==1)
            {
          Serial.print("Appel de l'humidite du 'HumiditySensor' sur le port : ");
          Serial.print(portModuleExterne);
          Serial.println();
          Serial.print("Le 'HumiditySensor' affiche une humidite de ");
          Serial.print(DHT2.humidity);
          Serial.print("%");
          Serial.println();
          delay(150);
            }
          //lecture du capteur de temperature => humidité
          break;

         case 3: //  3      TouchSensor           MakeBlock
          int currentState;
          
          this->analogPin = pinI; //je lui dit de lire le pinII
          currentState=this->runTouch();
          this->DATA=currentState;
          delay(10);
          
          if(DEBUGON==1)
            {
          Serial.print("Appel du l'Etat du 'TouchSensor' sur le port : ");
          Serial.print(portModuleExterne);
          Serial.println();
          Serial.print("Le 'TouchSensor' est a l'etat = ");
          Serial.print(currentState);
          Serial.println();
          delay(10);
            }
          
          //lecture du capteur de touché => touché
          break;

         //case 4: // 4      PIRSensor             Makeblock
          
        //Undefined (défaut) à faire
       }
       return(this->DATA);
}

void ModulesExternes::setPortType(PortType newPortType){
  this->porttype= newPortType;
  }

void ModulesExternes::setSensorType(SensorType newSensorType){
  this->sensortype = newSensorType;
  }

void ModulesExternes::setAnalogPin(int newAnalogPin){
  analogPin = newAnalogPin;
}
void ModulesExternes::setDATA(int newData){
  DATA = newData;
}
void ModulesExternes::setTemperature(int newTemp){
  temperature = newTemp;
}
void ModulesExternes::sethumidity(int newHumid){
  humidite = newHumid;
}
void ModulesExternes::setTouche(int newTouche){
  touche = newTouche;
}
void ModulesExternes::setPir(int newPir){
  pir = newPir;
}

//Temperature//
dht ModulesExternes::runTemperature(){
  dht DHT;
  pinMode(this->analogPin, OUTPUT);    //attribut de la classe => creation de l'objet avec 
  int chk = DHT.read11(this->analogPin);
  return DHT;
  }
  
//Touch//
int ModulesExternes::runTouch(){
    pinMode(analogPin, INPUT);
    boolean currentState = LOW;
    int counter = 0;
    currentState = digitalRead(this->analogPin);
    return currentState;
    }


//PIR//
void ModulesExternes::initPIR(){
    int calibrationTime = 30;
    pinMode(this->analogPin, INPUT);
    digitalWrite(this->analogPin, LOW);
    
    Serial.print("calibrating sensor ");
      for(int i = 0; i < calibrationTime; i++){
        Serial.print(".");
        delay(1000);
        }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
    }
   
void ModulesExternes::runPIR(){

          long unsigned int lowIn;  
          long unsigned int pause = 5000;  
          boolean lockLow = true;
          boolean takeLowTime;  
    
         if(digitalRead(this->analogPin) == HIGH){
         //DigitalWrite(ledPin, HIGH);   //les led représentent les états de sortie du capteur
         if(lockLow){  
         //S'assure que l'on attend une transition vers l'état bas avant toutes prochaines valeur de sortie
         lockLow = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(50);
         }         
         takeLowTime = true;
       }

     if(digitalRead(this->analogPin) == LOW){       
       //DigitalWrite(ledPin, LOW);  //Les led représentent les états de sortie du capteur

       if(takeLowTime){
        lowIn = millis();          //Met en mémoire le temps de la transition d'état de haut à bas
        takeLowTime = false;       //S'assurer que c'est seulement fait au début d'une phase état bas
        }
       //Si le capteur est à l'état bas pour une durée supérieure à une pause assignée
       //On supposera que tout mouvement est absent avant
       if(!lockLow && millis() - lowIn > pause){  
           //Makes sure this block of code is only executed again after 
           //Une nouvelle séquence mouvement a été détectée
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
  }
   
//demotouch//

void ModulesExternes::demotouch(Led *const led){
  if(runTouch() == HIGH){
  led->setColor(100,100,100);
  }
  else if(runTouch() == LOW){ 
  //éteindre leds avant
  led->setColor(0,0,0);
  }
}
 
