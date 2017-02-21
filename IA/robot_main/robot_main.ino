
#include "StandardCplusplus.h"
#include "vector"
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
#include "Data.h"

using namespace std;
int choice = -1;
int locations = 4;

int encoder1Pos = 0;
int encoder2Pos = 0;

//------Motors-------://
Motor motor_l = Motor(9,8,10);	
Motor motor_r = Motor(7,6,5);

//------Sensors-------://
Sensor sensorAvG = Sensor(35, A9, 300, SensorType::infraR, 2);
Sensor sensorAvMG = Sensor(37, A10, 300, SensorType::infraR, 1);
Sensor sensorAvM = Sensor(39, A11, 300, SensorType::infraR, 0);
Sensor sensorAvMD = Sensor(41, A12, 300, SensorType::infraR, -1);
Sensor sensorAvD = Sensor(43, A13, 300, SensorType::infraR, -2);
Sensor sensorArG = Sensor(45, A14, 300, SensorType::infraR, 10);
Sensor sensorArD = Sensor(47, A15, 300, SensorType::infraR, -10);
Sensor sensorLineLeft = Sensor(40, A0, 500, SensorType::line, 1);
Sensor sensorLineRight = Sensor(42, A1, 500, SensorType::line, -1);

//------LEDs-------://
Led frontLeds = Led(44, 6);
Led backLeds = Led(12, 2);

//------buttons-------://
Button btn_up = Button(22);
Button btn_left = Button(23);
Button btn_right = Button(24);
Button btn_down = Button(25);
Button btn_valid = Button(26);
    
//------Controls-------://
ControlPanel controls(5);

//------Son------------://
Buzzer speaker_main = Buzzer(11);

//------menu-------://
Menu menu = Menu(locations);
    
//------robot-------://
Program robot = Program(2,9);

//------wi-fi-------://
Wifi wifi = Wifi();
Data data = Data(0, 0);

void setup() {

	//------wifi initialization-------:// to use only one time to set the wi fi parameters
	wifi.init();
	wifi.createWifiAccessPoint("Robot_V2_qui_cours", "txrobotic");

    //------motor init-------://
    motor_l.init();
    motor_r.init();

    //------LEDs init-------://
    frontLeds.init();
	backLeds.init();
    
    //------Controls init-------://
    controls.addButton(btn_right);
    controls.addButton(btn_left);
    controls.addButton(btn_down);
    controls.addButton(btn_up);
    controls.addButton(btn_valid);

    robot.addMotor(&motor_l);
    robot.addMotor(&motor_r);
    robot.addSensor(&sensorAvG);
	robot.addSensor(&sensorAvMG);
    robot.addSensor(&sensorAvM);
    robot.addSensor(&sensorAvMD);
	robot.addSensor(&sensorAvD);
	robot.addSensor(&sensorArG);
	robot.addSensor(&sensorArD);
	robot.addSensor(&sensorLineLeft);
	robot.addSensor(&sensorLineRight);
	robot.addLed(&frontLeds);
	robot.addLed(&backLeds);
	robot.setControls(&controls);

    frontLeds.setColor(0,0,0);
	backLeds.setColor(0,0,0);

    //-------Welcoming sound----://
    //speaker_main.playMelody(WELCOMSONG);

	//Initialization of the serial communication at 9600 baud
	Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:

  //------menu-------://
	menu.runMenu(&robot, &controls, &frontLeds, &backLeds, &speaker_main, &data);
}
