// FirmataProcess.h

#ifndef _FIRMATAPROCESS_h
#define _FIRMATAPROCESS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Firmata\Firmata.h"


class FirmataProcess
{
 protected:
	byte portConfigInputs[TOTAL_PORTS]; // each bit: 1 = pin in INPUT, 0 = anything else

 public:
	void init();
	void run();
};


#endif

