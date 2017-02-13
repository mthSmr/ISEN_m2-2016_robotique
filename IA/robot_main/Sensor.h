
/*
   File:   Sensor.h
   Author: Mathilde

   Created on 11 octobre 2016, 14:05
*/

#ifndef SENSOR_H
#define SENSOR_H


#include "SensorType.h"

class Sensor {

  private:
    SensorType type;		//Store the type of the sensor
    int digitalPin;			//Store the digital pin attached to the sensor
    int analogPin;			//Store the analog pin attached to the sensor
    int cap;				//Store the threshold of the sensor
    int position;			//Store the position of the sensor
    bool value;				//Store the value of the sensor after the reading procedure

  public:

	//Constructors
    Sensor();
    Sensor(int, int, int, SensorType, int);

    //getter
    bool getValue();
    SensorType getType();
    int getPosition();
    int getCap();

    //setter
    void setType(SensorType type);
    void setPosition(int pos );
    void setCap(int);

    //utilitaire
    void read();	//Read the value of the sensor
};

#endif /* SENSOR_H */

