
/* 
 * File:   Sensor.h
 * Author: Mathilde
 *
 * Created on 11 octobre 2016, 14:05
 */

#ifndef SENSOR_H
#define SENSOR_H


#include "SensorType.h"

class Sensor {
    
    SensorType type;
    int digitalPin;
    int analogPin;
    int cap;
    
    

public:
    int position;
    bool value;
    Sensor();
    Sensor(int, int, int, SensorType, int);
    
    //getter
    bool getValue();
    SensorType getType();
    int getPosition();
    int getCap();

    //utilitaire
    void read();
    
private:
    //setter
    void setType(SensorType type);
    void setPosition(int pos );
    void setCap(int);
    /* /!\should not exist/!\ --> you don't want to set a value for your sensor
    void setValue(float value);
     */

};

#endif /* SENSOR_H */

