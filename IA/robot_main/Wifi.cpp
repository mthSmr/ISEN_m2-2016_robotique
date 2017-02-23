#include <SoftwareSerial.h>
#include "Wifi.h"
#include "Data.h"
#define ESP8266 Serial2

Wifi::Wifi()
{
 this->SSID = "ProjetRobotique";
 this->PASSWORD = "txrobotic";
 }

Wifi::Wifi(String newSSID,String newPASSWORD)
{
SSID=newSSID;
PASSWORD=newPASSWORD;
}

void Wifi::init(){
  ESP8266.begin(115200);
  //Serial.begin(115200);
}
void Wifi::createWifiAccessPoint(String ssid, String PASSWORD)
{
	//while (!ESP8266.find("eady")) {

		Serial.println("test 1");
		//ESP8266.begin(115200);
		while (!Serial2);
		ESP8266.println("AT+RST");
		delay(200);
		Serial.println("test 2");

		//Serial.println(ESP8266.readString());
	//}
	if(ESP8266.findUntil("r", "y") )
	//if(ESP8266.find("ready"))
    {
    	ESP8266.println("AT+RST");
    	delay(200);
    	ESP8266.println("AT+CWMODE=2");
    	delay(200);
    	ESP8266.println("AT+CWSAP=\"" + ssid + "\",\"" + PASSWORD + "\"" +",5,3");
    	delay(250);
    	ESP8266.println("AT+CIPMUX=1");
    	delay(200);
    	ESP8266.println("AT+CIPSERVER=1,998");
    	delay(200);
     Serial.println("test 3");
    }
    else
    {
        Serial.println("Fail");
        delay(200);
        FAIL_8266 = true;
    }
    Serial.println("test 4");
}
boolean Wifi::checkConnexion()
{
ESP8266.println("AT+CIPSTATUS");

  if (ESP8266.find("+CIPSTATUS:0")){
    return true;
  }else{
    return false;
  }
}

void Wifi::sendData (int id, String data) {
int LENGTH=data.length();
ESP8266.println("AT+CIPSEND="+String(id)+","+String(LENGTH));
delay(100);
ESP8266.println(data);
}
