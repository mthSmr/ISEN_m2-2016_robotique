
/* Author = helscream (Omer Ikram ul Haq)
Last edit date = 2014-10-08
Website: http://hobbylogs.me.pn/?p=47
Location: Pakistan
Ver: 0.1 beta --- Start
Ver: 0.2 beta --- Bug fixed for calculating "angle_y_accel" and "angle_x_accel" in "Gyro_header.ino" file
*/


#include "Emotions.h"

// Defining constants
#define dt 20                       // time difference in milli seconds
#define rad2degree 57.3              // Radian to degree conversion
#define Filter_gain 0.95             // e.g.  angle = angle_gyro*Filter_gain + angle_accel*(1-Filter_gain)
#define BUFFER_SIZE 32


//LED
int dataIn = 30; //DIN 
int load = 31;   //CS  
int clock = 32;  //CLK 
int maxInUse = 1;    //change this variable to set how many MAX7219's you'll use
int e = 0;    
//Variable globales : 

//Tableaux d'entiers contenant les indices des pattern que l'on va utiliser 

//Pour l'oeil gauche

int indexOfHappyEye1[]={0,1,2,1,0,3,4,3,0};
int indexOfInLoveEye1[]={0,9,10,10,11,11,10,10,11,11,10,10,11,11,10,10,11,11,10,10,10,9,0};
int indexOfEyeClosesEye1[]={0,5,6,7,8,8,8,8,8,8,8,7,6,5,0};
int indexOfCrazyEye1[]={0,3,4,19,20,21,22,23,24,25,26,27,28,29,4,3,0};
int indexOfDeadEye1[]={0,6,7,44,45,45,45,45,45,44,7,6,0};
int indexOfSnowEye1[]={47,48,49,46,46,46,46,49,48,47};
int indexOfStarEye1[]={51,51,52,52,53,53,52,52};
int indexOfALLREDEye1[]={54};


//Pour l'oeil droit

//int indexOfHappyEye2[]={0,1,2,1,0,3,4,3,0};
int indexOfCrazyEye2[]={0,3,4,29,28,27,26,25,24,23,22,21,20,19,4,3,0};
int indexOfSadEye2[]={0,5,6,34,37,38,39,38,40,34,35,34,35,6,5,0};


//Compteur qui va être incrémenté à chaque fois qu'on va rentrer dans mon état 
int compteur;

// Indice du tableau du pattern joué en ce moment 
int indexOfEmotion;

//Emotion qui est en train de joué 
Emotion emotionPlayed;


                     // define max7219 registers
byte max7219_reg_noop        = 0x00;
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;



void setup() {
  Serial.begin(115200);

//setup led

 //Instancification de la structure emotion avec differentes emotions 

  emotion[0].name="happy";
  emotion[0].pattern_number=sizeof(indexOfHappyEye1)/2;
  emotion[0].pattern_delay=150; //150
  initialization(indexOfHappyEye1,emotion[0].pattern_number,emotion[0].emotion_array_eye_1);

  emotion[1].name="inLove";
  emotion[1].pattern_number=sizeof(indexOfInLoveEye1)/2;
  emotion[1].pattern_delay=150; //150
  initialization(indexOfInLoveEye1,emotion[1].pattern_number,emotion[1].emotion_array_eye_1);

  emotion[2].name="eyeCloses";
  emotion[2].pattern_number=sizeof(indexOfEyeClosesEye1)/2;
  emotion[2].pattern_delay=150;
  initialization(indexOfEyeClosesEye1,emotion[2].pattern_number,emotion[2].emotion_array_eye_1);

  emotion[3].name="crazyEye";
  emotion[3].pattern_number=sizeof(indexOfCrazyEye1)/2;
  emotion[3].pattern_delay=150;
  initialization(indexOfCrazyEye1,emotion[3].pattern_number,emotion[3].emotion_array_eye_1);

  emotion[4].name="deadEye";
  emotion[4].pattern_number=sizeof(indexOfDeadEye1)/2;
  emotion[4].pattern_delay=150;
  initialization(indexOfDeadEye1,emotion[4].pattern_number,emotion[4].emotion_array_eye_1);

  emotion[5].name="snowEye";
  emotion[5].pattern_number=sizeof(indexOfSnowEye1)/2;
  emotion[5].pattern_delay=150;
  initialization(indexOfSnowEye1,emotion[5].pattern_number,emotion[5].emotion_array_eye_1);

  emotion[6].name="starEye";
  emotion[6].pattern_number=sizeof(indexOfStarEye1)/2;
  emotion[6].pattern_delay=150;
  initialization(indexOfStarEye1,emotion[6].pattern_number,emotion[6].emotion_array_eye_1);

  emotion[7].name="ALLREDEye";
  emotion[7].pattern_number=sizeof(indexOfALLREDEye1)/2;
  emotion[7].pattern_delay=150;
  initialization(indexOfALLREDEye1,emotion[7].pattern_number,emotion[7].emotion_array_eye_1);
 
  indexOfEmotion=0;

  compteur=-1;
  
  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(load,   OUTPUT);

  //beginSerial(9600);
  digitalWrite(13, HIGH); 

  //initiation of the max 7219
  maxAll(max7219_reg_scanLimit, 0x07);      
  maxAll(max7219_reg_decodeMode, 0x00);  // using a led matrix (not digits)
  maxAll(max7219_reg_shutdown, 0x01);    // not in shutdown mode
  maxAll(max7219_reg_displayTest, 0x00); // no display test
   for (e=1; e<=8; e++) {    // empty registers, turn all LEDs off 
    maxAll(e,0);
  }
  maxAll(max7219_reg_intensity, 0x0f & 0x0f);    // the first 0x0f is the value you can set
                                                  // range: 0x00 to 0x0f  

}
void loop() {

//indexOfEmotion = 11;
emotionPlayed=emotion[indexOfEmotion];

  //entier qui permettra de vérifier si on est à la fin de l'émotion 
  int testEndEmotion;

  //incrémentation de ma variable compteur 
  compteur=compteur+1;
  
  //On affiche le pattern
  testEndEmotion=printPattern(emotionPlayed, compteur, 1);

  //test pour savoir si on est à la fin de l'émotion, dans ces cas la, indexOfEmotion prendra une valeur random dans le tableau l'Emotion
   if (testEndEmotion==-1) {
    if (indexOfEmotion<10) {
      indexOfEmotion=random(0,7);
      Serial.println(indexOfEmotion);
    }
    else {
      indexOfEmotion=random(0,7);
    }
    compteur=-1;
    //indexOfEmotion=indexOfEmotion+1;
    //Serial.println(indexOfEmotion);
    testEndEmotion=0;
   }

  
}


//************************************************* Fonction à la con en lien avec les leds parce que la création du cpp est galère ***************************************//

//Procédure qui permettera d'initialier les tableaux contenant les indices des patterns
//Paramètres : 
//indexOfEmotion : tableau contenant les indices 
//sizeOfArray : taille du tableau 
//array : le tableau qui sera ensuite associé au tableau d'emotion 

void initialization(int indexOfEmotion[],int sizeOfArray, int array[]) {

  for (int i=0;i<23;i++) {
    if (i<sizeOfArray) {
      array[i]=indexOfEmotion[i];       
    }
    else {
      array[i]=-1; 
    }
  }
}

//Fonction qui va afficher le pattern
//Paramètres : 
//emotionInAction : l'emotion sur lequel on est 
//patternCounter : pour savoir à quelle valeur le compteur de l'émotion on est 
//Si le patternCounter est égale à la taille du tableau, alors nous sommes à la fin de l'émotion et la fonction renvera -1, sinon elle envoie emotionInAction.pattern_number-1  

int printPattern(Emotion emotionInAction, int patternCounter, int partFace) {

  int arrayEye1[8];
  int arrayEye2[8];

  int testEnd;

  testEnd=emotionInAction.pattern_number-1;

  int nextIndexOfEmotion;

  for (int i=0;i<8;i++) {
    arrayEye1[i]=Eyes[emotionInAction.emotion_array_eye_1[patternCounter]][i];
  }

  printOnePattern(arrayEye1,1);
  
  if (emotionInAction.name!="sad" and emotionInAction.name!="crazy") {
    printOnePattern(arrayEye1,4);
  }
  else {
    if (emotionInAction.name=="crazy") {
      for (int i=0;i<8;i++) {
        arrayEye2[i]=Eyes[indexOfCrazyEye2[patternCounter]][i];
      }
    }
    else {
      for (int i=0;i<8;i++) {
        arrayEye2[i]=Eyes[indexOfSadEye2[patternCounter]][i];
      }
    }
    printOnePattern(arrayEye2,4);
  }

  
  delay(emotionInAction.pattern_delay);

   if (patternCounter>=testEnd) {
     testEnd=-1;   
  }
  return testEnd;
}

//procédure qui va afficher un pattern. 
//Paramètres :
//un tableau de 8 valeurs de LED
//le nombre de la plaque de LED a controller :
//1 : Yeux gauche
//2 : Bouche gauche
//3 : Bouche gauche
//4 : Yeux droit
void printOnePattern (int value[8],int part) {
  int i;
  for (i=0;i<8;i++) {
    maxOne(part,i+1,value[i]);
  }
}

void maxAll (byte reg, byte col) {    // initialize  all  MAX7219's in the system
  int c = 0;
  digitalWrite(load, LOW);  // begin     
  for ( c =1; c<= maxInUse; c++) {
  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
    }
  digitalWrite(load, LOW);
  digitalWrite(load,HIGH);
}

void maxOne(byte maxNr, byte reg, byte col) {    //MaxNr = Number of the MAX  | reg = Value in the line | col | wich column ?
//maxOne is for adressing different MAX7219's, 
//whilele having a couple of them cascaded

  int c = 0;
  digitalWrite(load, LOW);  // begin     

  for ( c = maxInUse; c > maxNr; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
  }

  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data 

  for ( c =maxNr-1; c >= 1; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
  }

  digitalWrite(load, LOW); // and load da shit
  digitalWrite(load,HIGH); 
}

void putByte(byte data) {
  byte i = 8;
  byte mask;
  while(i > 0) {
    mask = 0x01 << (i - 1);      // get bitmask
    digitalWrite( clock, LOW);   // tick
    if (data & mask){            // choose bit
      digitalWrite(dataIn, HIGH);// send 1
    }else{
      digitalWrite(dataIn, LOW); // send 0
    }
    digitalWrite(clock, HIGH);   // tock
    --i;                         // move to lesser bit
  }
}














