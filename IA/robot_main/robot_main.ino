
#include <StandardCplusplus.h>
#include <vector>

#include "Arduino.h"
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
int locations = 2;

//------Motors-------://
    Motor motor_l = Motor(9,8,10);
    Motor motor_r = Motor(7,6,5);
//    Motor *const motor_l_p = &motor_l;
//    Motor *const motor_r_p = &motor_r;

//------Sensors-------://
    Sensor sensorAvG = Sensor(37, A10, 130, SensorType::infraR, -1); 
    Sensor sensorAvM = Sensor(39, A11, 130, SensorType::infraR, 0);
    Sensor sensorAvD = Sensor(41, A12, 130, SensorType::infraR, 1);
    //Sensor *const sensorAvG_p = &sensorAvG;
    //Sensor *const sensorAvM_p = &sensorAvM;
    //Sensor *const sensorAvD_p = &sensorAvD;

    Sensor sensorDessG = Sensor(40, A0, 990, SensorType::lum, 10);
    Sensor sensorDessD = Sensor(42, A1, 700, SensorType::lum, 11);

//------LEDs-------://
    Led frontLeds = Led(44,5);
	  //Led *const frontLeds_p = &frontLeds;

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
    Menu menu = Menu(3);
    
//------robot-------://
    Program robot = Program(2,3);


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
    robot.addSensor(&sensorDessG);
    robot.addSensor(&sensorDessD);
	  robot.addLed(&frontLeds);
	  robot.setControls(&controls);

    frontLeds.setColor(0,0,0);

    //-------Son de bienvenu----://
    speaker_main.PlayMelody(WELCOMSONG);
}

void loop() {
  //------Partie de CrashTEST------//

  //------menu-------://
    
    menu.runMenu(&robot,&controls,&frontLeds, &speaker_main);
    //robot.lineFollower(&controls,&frontLeds);
    //robot.dodger(&controls,&frontLeds);
}
