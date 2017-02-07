// 
// 
// 

#include "EmotionSprite.h"

/*

EmotionSprite::EmotionSprite() {

}

EmotionSprite::EmotionSprite(String name, int pattern_number, int pattern_delay, vector<int> emotion_array_eye) {
	this->name = name;
	this->pattern_number = pattern_number;
	this->pattern_delay = pattern_delay;
	this->emotion_array_eye = emotion_array_eye;
}

//Procédure qui permettera d'initialier les tableaux contenant les indices des patterns
//Paramètres : 
//indexOfEmotion : tableau contenant les indices 
//sizeOfArray : taille du tableau 
//array : le tableau qui sera ensuite associé au tableau d'emotion 
void EmotionSprite::SetEmotion_array_eye(int indexOfEmotion[], int sizeOfArray, vector<int> emotion_array_eye) {
	for (int i = 0; i < 23; i++) {
		if (i < sizeOfArray) this->emotion_array_eye[i] = emotion_array_eye[i];
		else this->emotion_array_eye[i] = -1;
	}
}

void EmotionSprite::SetName(String name) {
	this->name = name;
}

void EmotionSprite::SetPattern_number(int pattern_number) {
	this->pattern_number = pattern_number;
}

void EmotionSprite::SetPattern_delay(int pattern_delay) {
	this->pattern_delay = pattern_delay;
}

void EmotionSprite::init() {
	Serial.begin(115200);

	//setup led

	//Instancification de la structure emotion avec differentes emotions 

	emotion[0].name = "happy";
	emotion[0].pattern_number = sizeof(indexOfHappyEye1) / 2;
	emotion[0].pattern_delay = 150; //150
	initialization(indexOfHappyEye1, emotion[0].pattern_number, emotion[0].emotion_array_eye);

	emotion[1].name = "inLove";
	emotion[1].pattern_number = sizeof(indexOfInLoveEye1) / 2;
	emotion[1].pattern_delay = 150; //150
	initialization(indexOfInLoveEye1, emotion[1].pattern_number, emotion[1].emotion_array_eye);

	emotion[2].name = "eyeCloses";
	emotion[2].pattern_number = sizeof(indexOfEyeClosesEye1) / 2;
	emotion[2].pattern_delay = 150;
	initialization(indexOfEyeClosesEye1, emotion[2].pattern_number, emotion[2].emotion_array_eye);

	emotion[3].name = "crazyEye";
	emotion[3].pattern_number = sizeof(indexOfCrazyEye1) / 2;
	emotion[3].pattern_delay = 150;
	initialization(indexOfCrazyEye1, emotion[3].pattern_number, emotion[3].emotion_array_eye);

	emotion[4].name = "deadEye";
	emotion[4].pattern_number = sizeof(indexOfDeadEye1) / 2;
	emotion[4].pattern_delay = 150;
	initialization(indexOfDeadEye1, emotion[4].pattern_number, emotion[4].emotion_array_eye);

	emotion[5].name = "snowEye";
	emotion[5].pattern_number = sizeof(indexOfSnowEye1) / 2;
	emotion[5].pattern_delay = 150;
	initialization(indexOfSnowEye1, emotion[5].pattern_number, emotion[5].emotion_array_eye);

	emotion[6].name = "starEye";
	emotion[6].pattern_number = sizeof(indexOfStarEye1) / 2;
	emotion[6].pattern_delay = 150;
	initialization(indexOfStarEye1, emotion[6].pattern_number, emotion[6].emotion_array_eye);

	emotion[7].name = "ALLREDEye";
	emotion[7].pattern_number = sizeof(indexOfALLREDEye1) / 2;
	emotion[7].pattern_delay = 150;
	initialization(indexOfALLREDEye1, emotion[7].pattern_number, emotion[7].emotion_array_eye);

	indexOfEmotion = 0;

	compteur = -1;

	pinMode(dataIn, OUTPUT);
	pinMode(clock, OUTPUT);
	pinMode(load, OUTPUT);

	//beginSerial(9600);
	digitalWrite(13, HIGH);

	//initiation of the max 7219
	maxAll(max7219_reg_scanLimit, 0x07);
	maxAll(max7219_reg_decodeMode, 0x00);  // using a led matrix (not digits)
	maxAll(max7219_reg_shutdown, 0x01);    // not in shutdown mode
	maxAll(max7219_reg_displayTest, 0x00); // no display test
	for (e = 1; e <= 8; e++) {    // empty registers, turn all LEDs off 
		maxAll(e, 0);
	}
	maxAll(max7219_reg_intensity, 0x0f & 0x0f);    // the first 0x0f is the value you can set
												   // range: 0x00 to 0x0f 
}

//Fonction qui va afficher le pattern
//Paramètres : 
//emotionInAction : l'emotion sur lequel on est 
//patternCounter : pour savoir à quelle valeur le compteur de l'émotion on est 
//Si le patternCounter est égale à la taille du tableau, alors nous sommes à la fin de l'émotion et la fonction renvera -1, sinon elle envoie emotionInAction.pattern_number-1  
int EmotionSprite::printPattern(Emotion emotionInAction,int patternCounter) {

	int arrayEye[8];

	int testEnd;

	testEnd = this->pattern_number - 1;

	int nextIndexOfEmotion;

	for (int i = 0; i<8; i++) {
		arrayEye[i] = Eyes[this->emotion_array_eye[patternCounter]][i];
	}

	printOnePattern(arrayEye, 1);
	printOnePattern(arrayEye, 4);

	delay(this->pattern_delay);

	if (patternCounter >= testEnd) {
		testEnd = -1;
	}
	return testEnd;


	
}*/