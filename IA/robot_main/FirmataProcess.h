// FirmataProcess.h

#ifndef _FIRMATAPROCESS_h
#define _FIRMATAPROCESS_h

#include <Lib\Wire\Wire.h>
#include <Lib\Firmata\Firmata.h>

#define I2C_WRITE                   B00000000
#define I2C_READ                    B00001000
#define I2C_READ_CONTINUOUSLY       B00010000
#define I2C_STOP_READING            B00011000
#define I2C_READ_WRITE_MODE_MASK    B00011000
#define I2C_10BIT_ADDRESS_MODE_MASK B00100000
#define I2C_MAX_QUERIES             8
#define I2C_REGISTER_NOT_SPECIFIED  -1

// the minimum interval for sampling analog input
#define MINIMUM_SAMPLING_INTERVAL 10

//	Case Scratch functions
#define MOTOR 0xA1
#define LED 0xA2
#define BUZZER 0xA2

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class FirmataProcess
{
 protected:

 public:

	 /* analog inputs */
	 int analogInputsToReport = 0;  // bitwise array to store pin reporting

	/* pins configuration */
	 byte pinConfig[TOTAL_PINS];         // configuration of every pin
	 byte portConfigInputs[TOTAL_PORTS]; // each bit: 1 = pin in INPUT, 0 = anything else
	 int  pinState[TOTAL_PINS];           // any value that has been written

	/* digital input ports */
	 byte reportPINs[TOTAL_PORTS];       // 1 = report this port, 0 = silence
	 byte previousPINs[TOTAL_PORTS];     // previous 8 bits sent

	/* timer variables */
	 unsigned long currentMillis;        // store the current value from millis()
	 unsigned long previousMillis;       // for comparison with currentMillis
	 unsigned int samplingInterval = 19; // how often to run the main loop (in ms)

	/* i2c data */
	 struct i2c_device_info {
		 byte addr;
		 int reg;
		 byte bytes;
	 };

	 /* for i2c read continuous more */
	 i2c_device_info query[I2C_MAX_QUERIES];

	 byte i2cRxData[32];
	 boolean isI2CEnabled = false;
	 signed char queryIndex = -1;
	 // default delay time between i2c read request and Wire.requestFrom()
	 unsigned int i2cReadDelayTime = 0;

	 boolean isResetting = false;

	 /*==============================================================================
	 * FUNCTIONS
	 *============================================================================*/
	 
	 FirmataProcess();

	 void init();
};


#endif

