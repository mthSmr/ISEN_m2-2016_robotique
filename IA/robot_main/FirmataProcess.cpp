// 
// 
// 

#include "FirmataProcess.h"
#include "Firmata\Firmata.h"


void FirmataProcess::init()
{
	//Firmata setup 
	Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);
	Firmata.attach(DIGITAL_MESSAGE, digitalWriteCallback);
	Firmata.attach(SET_PIN_MODE, setPinModeCallback);
	Firmata.begin(57600);
}

void outputPort(byte portNumber, byte portValue, byte forceSend)
{
	// pins not configured as INPUT are cleared to zeros
	portValue = portValue & portConfigInputs[portNumber];
	// only send if the value is different than previously sent
	if (forceSend || previousPINs[portNumber] != portValue) {
		Firmata.sendDigitalPort(portNumber, portValue);
		previousPINs[portNumber] = portValue;
	}
}

void FirmataProcess::run()
{
	//firmata loop
	byte i;

	for (i = 0; i < TOTAL_PORTS; i++) {
		outputPort(i, readPort(i, 0xff));
	}
	while (Firmata.available()) {
		Firmata.processInput();
	}
}





