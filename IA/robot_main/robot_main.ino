
#include "Interrupt.h"
#include "StandardCplusplus.h"
#include "vector"

//#include <Arduino.h>
#include "Program.h"
#include "SensorType.h"
#include "Sensor.h"
#include "Motor.h"
#include "Button.h"
#include "ControlPanel.h"
#include "Menu.h"
#include "Led.h"
#include "Buzzer.h"
#include "Wifi.h"
#include "ModulesExternes.h"
#include "dht.h"

/* MODULE EXTERNE DEFINE */

#define CAPTEURTOUCHE 3
#define CAPTEURTEMPERATURE 1
#define CAPTEURHUMIDITE 2


using namespace std;
int choice = -1;
int locations = 4;

//------Motors-------://
	Motor motor_l = Motor(9,8,10);
	Motor motor_r = Motor(7,6,5);


//------Sensors-------://
/*	V2	*/
/*
Sensor sensorAvG = Sensor(37, A10, 100, SensorType::infraR, 1); 
Sensor sensorAvM = Sensor(39, A11, 100, SensorType::infraR, 0);
Sensor sensorAvD = Sensor(41, A12, 100, SensorType::infraR, -1);
Sensor sensorArG = Sensor(45, A14, 100, SensorType::infraR, 10);
Sensor sensorArD = Sensor(47, A15, 100, SensorType::infraR, -10);
Sensor sensorLineLeft = Sensor(40, A0, 500, SensorType::line, 1);
Sensor sensorLineRight = Sensor(42, A1, 500, SensorType::line, -1);
*/
/*	V3	*/	
Sensor sensorAvD = Sensor(37, A9, 300, SensorType::infraR, -2);		
Sensor sensorAvMD = Sensor(35, A10, 300, SensorType::infraR, -1);	
Sensor sensorAvM = Sensor(39, A11, 300, SensorType::infraR, 0);		
Sensor sensorAvMG = Sensor(41, A12, 300, SensorType::infraR, 1);	
Sensor sensorAvG = Sensor(43, A13, 300, SensorType::infraR, 2);		
Sensor sensorArG = Sensor(47, A14, 300, SensorType::infraR, 10);
Sensor sensorArD = Sensor(49, A15, 300, SensorType::infraR, -10);
Sensor sensorLineLeft = Sensor(40, A0, 500, SensorType::line, 1);
Sensor sensorLineRight = Sensor(42, A1, 500, SensorType::line, -1);

//------LEDs-------://
/*	V2	*/
/*
Led frontLeds = Led(44, 5);
Led backLeds = Led(12, 5);
*/
/*	V3	*/
Led backLeds = Led(12, 5);
Led frontLeds = Led(44, 6);

//------buttons-------://
Button btn_up = Button(22);
Button btn_left = Button(23);
Button btn_right = Button(24);
Button btn_down = Button(25);
Button btn_valid = Button(26);
    
//------Controls-------://
ControlPanel controls(5);

//------Son------------://
Buzzer speaker = Buzzer(11);

//------menu-------://
Menu menu = Menu(locations);
    
//------robot-------://
Program robot = Program(2,7);

//------wi-fi-------://
Wifi wifi = Wifi();
Data data = Data(0, 0);


void setup() {
    
	//------Wifi init-------://
	wifi.init();
	wifi.createWifiAccessPoint("Robot_Thoma", "txrobotic");

    //------motor init-------://
    motor_l.init();
	motor_l.initControl(5, 0.7575, -1.7575, 0.0307, 0.0712);
    motor_r.init();
	motor_r.initControl(4, 0.8187, -1.8187, 0.0279, 0.0682);

    //------LEDs init-------://
    frontLeds.init();
	backLeds.init();
    
    //------Add component to robot-------://
    controls.addButton(btn_right);
    controls.addButton(btn_left);
    controls.addButton(btn_down);
    controls.addButton(btn_up);
    controls.addButton(btn_valid);

    robot.addMotor(&motor_l);
    robot.addMotor(&motor_r);

    robot.addSensor(&sensorAvG);
    robot.addSensor(&sensorAvM);
    robot.addSensor(&sensorAvD);
	robot.addSensor(&sensorArG);
	robot.addSensor(&sensorArD);
	robot.addSensor(&sensorLineLeft);
	robot.addSensor(&sensorLineRight);

	robot.addLed(&frontLeds);
	robot.addLed(&backLeds);

	robot.setControls(&controls);
	robot.setData(&data);
	robot.setBuzzer(&speaker);

	//------turning bot-------://
    backLeds.setColor(255,255,255);
	frontLeds.setColor(255, 255, 255);

	//------ModulesExternes------://
	ModulesExternes Module1;
	ModulesExternes Module2;

    //-------Son de bienvenu----://
    //speaker_main.playMelody(WELCOMSONG);
	
	//Initialisation de la communication s�rie � 9600 Baud
	Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  //------Partie de CrashTEST------//

	robot.testAsserv(1000);

  //------menu-------://
  menu.runMenu(&robot,&controls,&frontLeds, &backLeds, &speaker);
  //robot.dodger(&controls,&frontLeds);

}
