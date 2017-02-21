
#include <SoftwareSerial.h>
#include "Wifi.h"
#include "Data.h"
#define ESP8266 Serial2


Data::Data() {

}

Data::Data(int newA, int newP) {
    this-> a=newA;
    this-> p=newP;
}
int Data::getA(){
    return this->a;
}

int Data::getP() {
    return this->p;
}
void Data::setA(int newA){
    this->a=newA;
}
void Data::setP(int newP){
    this->p=newP;
}
void Data::setData(int newA,int newP){
    this->a=newA;
    this->p=newP;
}
int Data::analyze(){
    if (this->p==0 && this->a==0 ) {
        this->memory=0;
        return 0;
    }else if (this->p >0 && this->a >(-30) && this->a <30) {
    // Cas marche avant 
      this->memory=1;
      return 1 ;
    }else if (this->a>30 && this->a<60 && this->p>0)
    {
      // Cas  droite
     this-> memory=2;
      return 2;
    }else if (this->a>60)
    {
      // Cas arriere
      this->memory=3;
      return 3;
    }else if (this->a<60 && this->a>30  && this->p<0 )
    {
      // Cas gauche 
      this->memory=4;
      return 4;
    }else if (this->a>(-30) &&this->a<30 && this->p<0)
    {
      // Cas gauche 
      this->memory=5;
      return 5;
    }else if (this->a<(-30) &&this->a>(-60) &&this-> p<0 )
    {
      // Cas gauche 
      this->memory=6;
      return 6;
    }else if (this->a<(-60) )
    {
      // Cas gauche 
      this->memory=7;
      return 7;
    }else if (this->a>(-60) && this->a<(-30) && this->p>0 )
    {
      // Cas gauche 
      this->memory=8;
      return 8;
    }
    else{
      return memory;
    }
}
Data Data::receiveData() {

Data newData(0,0);
  int power=0;
  int angle=0;
  if(ESP8266.available()) 
     {
        if(ESP8266.find("+IPD,"))
        {
            String action;
            int connexionId = ESP8266.read()-48;
            ESP8266.find("Pw=");
           power=ESP8266.parseInt();
            // delay(250);
            ESP8266.find("Angle=");
           angle=ESP8266.parseInt();
          angle=(angle)/10;
        }
      newData.setData(angle,power);
    }
  return newData;
}

