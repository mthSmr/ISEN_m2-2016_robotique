#ifndef Wifi_h
#define Wifi_h
#include "Data.h"
#include <Arduino.h>
#include <SoftwareSerial.h>  
#define ESP8266 Serial2
class Wifi
{
public:
    boolean FAIL_8266 = false;
    String SSID = "ProjetRobotique";
    String PASSWORD = "txrobotic";
    /////////////////////Constructors////////////////////
    Wifi();
    Wifi(String,String);
    ///////////////////////////////////////////////////////
    void init(); // initialization Function
    void createWifiAccessPoint(String,String); // Create a Wifi access point with SSID and PASSWORD in Arguments
    boolean checkConnexion(); // Checks connexion with devices
    void sendData (int ,String); // Send a String to int device
};
    
#endif
