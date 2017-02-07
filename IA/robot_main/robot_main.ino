
#include "StandardCplusplus.h"
#include "vector"

#include <Arduino.h>
#include "Program.h"
#include "SensorType.h"
#include "Sensor.h"
#include "Motor.h"
#include "Button.h"
#include "ControlPanel.h"
#include "Menu.h"
#include "Led.h"
#include "Buzzer.h"




using namespace std;
int choice = -1;
int locations = 3;

//------Motors-------://
	Motor motor_l = Motor(9,8,10);	
	Motor motor_r = Motor(7,6,5);


//------Sensors-------://
	Sensor sensorAvG = Sensor(37, A10, 150, SensorType::infraR, 1); 
	Sensor sensorAvM = Sensor(39, A11, 150, SensorType::infraR, 0);
	Sensor sensorAvD = Sensor(41, A12, 150, SensorType::infraR, -1);
	Sensor sensorArG = Sensor(45, A14, 150, SensorType::infraR, 10);
	Sensor sensorArD = Sensor(47, A15, 150, SensorType::infraR, -10);
  Sensor sensorLineLeft = Sensor(40, A0, 500, SensorType::line, 1);
  Sensor sensorLineRight = Sensor(42, A1, 500, SensorType::line, -1);

//------LEDs-------://
    Led frontLeds = Led(44,6);
	  Led *const frontLeds_p = &frontLeds;

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
    Program robot = Program(2,7);


void setup() {
    
    //------motor init-------://
    motor_l.init();
    motor_r.init();

    //------LEDs init-------://
    frontLeds.init();
    
    //------Controls init-------://
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
	  robot.setControls(&controls);

    frontLeds.setColor(0,0,0);

    //-------Son de bienvenu----://
    //speaker_main.playMelody(WELCOMSONG);
	
	//Initialisation de la communication série à 9600 Baud
	Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //------Partie de CrashTEST------//

  //------menu-------://
  menu.runMenu(&robot,&controls,&frontLeds, &speaker_main );
  //robot.dodger(&controls,&frontLeds);
  
//speaker_main.playMelody(WELCOMSONG);
//   std::vector<float> marioMusic;
//   marioMusic.push_back(speaker_main.sii);
//   marioMusic.push_back(speaker_main.sii);
//   marioMusic.push_back(0);
//   marioMusic.push_back(speaker_main.sii);
//   marioMusic.push_back(0);
//   marioMusic.push_back(speaker_main.sol);
//   marioMusic.push_back(speaker_main.sii);
//   marioMusic.push_back(0);
//   marioMusic.push_back(speaker_main.sol * 2);
//    
//   speaker_main.playMusic(marioMusic);
}
