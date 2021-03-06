/*
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

(function(ext) {

    var PIN_MODE = 0xF4,
        REPORT_DIGITAL = 0xD0,
        REPORT_ANALOG = 0xC0,
        DIGITAL_MESSAGE = 0x90,
        START_SYSEX = 0xF0,
        END_SYSEX = 0xF7,
        QUERY_FIRMWARE = 0x79,
        REPORT_VERSION = 0xF9,
        ANALOG_MESSAGE = 0xE0,
        ANALOG_MAPPING_QUERY = 0x69,
        ANALOG_MAPPING_RESPONSE = 0x6A,
        CAPABILITY_QUERY = 0x6B,
        CAPABILITY_RESPONSE = 0x6C;

        MOTOR = 0xA1;
        LED = 0xA2;
        BUZZER = 0xA3;

    var INPUT = 0x00,
        OUTPUT = 0x01,
        ANALOG = 0x02,
        PWM = 0x03,
        SERVO = 0x04,
        SHIFT = 0x05,
        I2C = 0x06,
        ONEWIRE = 0x07,
        STEPPER = 0x08,
        ENCODER = 0x09,
        SERIAL = 0x0A,
        PULLUP = 0x0B,
        IGNORE = 0x7F,
        TOTAL_PIN_MODES = 13;

    var LOW = 0,
        HIGH = 1;

    var MAX_DATA_BYTES = 4096;
    var MAX_PINS = 128;

    var parsingSysex = false,
        waitForData = 0,
        executeMultiByteCommand = 0,
        multiByteChannel = 0,
        sysexBytesRead = 0,
        storedInputData = new Uint8Array(MAX_DATA_BYTES);

    var digitalOutputData = new Uint8Array(16),
        digitalInputData = new Uint8Array(16),
        analogInputData = new Uint16Array(16);

    var analogChannel = new Uint8Array(MAX_PINS);
    var pinModes = [];
    for (var i = 0; i < TOTAL_PIN_MODES; i++) pinModes[i] = [];

    var majorVersion = 0,
        minorVersion = 0;

    var connected = false;
    var notifyConnection = false;
    var device = null;
    var inputData = null;

    // TEMPORARY WORKAROUND
    // Since _deviceRemoved is not used with Serial devices
    // ping device regularly to check connection
    var pinging = false;
    var pingCount = 0;
    var pinger = null;

    var hwList = new HWList();
    
    var buttonList = ["bouton 1", 22, "bouton 2", 24, "bouton 3", 25, "bouton 4", 23, "bouton 5", 26];

    function HWList() {
        this.devices = [];

        this.add = function(dev, pin) {
            var device = this.search(dev);
            if (!device) {
                device = {name: dev, pin: pin, val: 0};
                this.devices.push(device);
            } else {
                device.pin = pin;
                device.val = 0;
            }
        };

        this.search = function(dev) {
            for (var i=0; i<this.devices.length; i++) {
                if (this.devices[i].name === dev)
                    return this.devices[i];
            }
            return null;
        };
    }

    function init() {

        for (var i = 0; i < 16; i++) {
            var output = new Uint8Array([REPORT_DIGITAL | i, 0x01]);
            device.send(output.buffer);
        }

        queryCapabilities();

        // TEMPORARY WORKAROUND
        // Since _deviceRemoved is not used with Serial devices
        // ping device regularly to check connection
        pinger = setInterval(function() {
            if (pinging) {
                if (++pingCount > 6) {
                    clearInterval(pinger);
                    pinger = null;
                    connected = false;
                    if (device) device.close();
                    device = null;
                    return;
                }
            } else {
                if (!device) {
                    clearInterval(pinger);
                    pinger = null;
                    return;
                }
                queryFirmware();
                pinging = true;
            }
        }, 100);
    }

    function hasCapability(pin, mode) {
        if (pinModes[mode].indexOf(pin) > -1)
            return true;
        else
            return false;
    }

    function queryFirmware() {
        var output = new Uint8Array([START_SYSEX, QUERY_FIRMWARE, END_SYSEX]);
        device.send(output.buffer);
    }

    function queryCapabilities() {
        console.log('Querying ' + device.id + ' capabilities');
        var msg = new Uint8Array([
            START_SYSEX, CAPABILITY_QUERY, END_SYSEX]);
        device.send(msg.buffer);
    }

    function queryAnalogMapping() {
        console.log('Querying ' + device.id + ' analog mapping');
        var msg = new Uint8Array([
            START_SYSEX, ANALOG_MAPPING_QUERY, END_SYSEX]);
        device.send(msg.buffer);
    }

    function setDigitalInputs(portNum, portData) {
        digitalInputData[portNum] = portData;
    }

    function setAnalogInput(pin, val) {
        analogInputData[pin] = val;
    }

    function setVersion(major, minor) {
        majorVersion = major;
        minorVersion = minor;
    }

    function processSysexMessage() {
        switch(storedInputData[0]) {
            case CAPABILITY_RESPONSE:
                for (var i = 1, pin = 0; pin < MAX_PINS; pin++) {
                    while (storedInputData[i++] != 0x7F) {
                        pinModes[storedInputData[i-1]].push(pin);
                        i++; //Skip mode resolution
                    }
                    if (i == sysexBytesRead) break;
                }
                queryAnalogMapping();
                break;
            case ANALOG_MAPPING_RESPONSE:
                for (var pin = 0; pin < analogChannel.length; pin++)
                    analogChannel[pin] = 127;
                for (var i = 1; i < sysexBytesRead; i++)
                    analogChannel[i-1] = storedInputData[i];
                for (var pin = 0; pin < analogChannel.length; pin++) {
                    if (analogChannel[pin] != 127) {
                        var out = new Uint8Array([
                            REPORT_ANALOG | analogChannel[pin], 0x01]);
                        device.send(out.buffer);
                    }
                }
                notifyConnection = true;
                setTimeout(function() {
                    notifyConnection = false;
                }, 100);
                break;
            case QUERY_FIRMWARE:
                if (!connected) {
                    clearInterval(poller);
                    poller = null;
                    clearTimeout(watchdog);
                    watchdog = null;
                    connected = true;
                    setTimeout(init, 500); // ADD avant 200
                }
                pinging = false;
                pingCount = 0;
                break;
        }
    }

    function processInput(inputData) {
        for (var i=0; i < inputData.length; i++) {
            if (parsingSysex) {
                if (inputData[i] == END_SYSEX) {
                    parsingSysex = false;
                    processSysexMessage();
                } else {
                    storedInputData[sysexBytesRead++] = inputData[i];
                }
            } else if (waitForData > 0 && inputData[i] < 0x80) {
                storedInputData[--waitForData] = inputData[i];
                if (executeMultiByteCommand !== 0 && waitForData === 0) {
                    switch(executeMultiByteCommand) {
                        case DIGITAL_MESSAGE:
                            setDigitalInputs(multiByteChannel, (storedInputData[0] << 7) + storedInputData[1]);
                            break;
                        case ANALOG_MESSAGE:
                            setAnalogInput(multiByteChannel, (storedInputData[0] << 7) + storedInputData[1]);
                            break;
                        case REPORT_VERSION:
                            setVersion(storedInputData[1], storedInputData[0]);
                            break;
                    }
                }
            } else {
                if (inputData[i] < 0xF0) {
                    command = inputData[i] & 0xF0;
                    multiByteChannel = inputData[i] & 0x0F;
                } else {
                    command = inputData[i];
                }
                switch(command) {
                    case DIGITAL_MESSAGE:
                    case ANALOG_MESSAGE:
                    case REPORT_VERSION:
                        waitForData = 2;
                        executeMultiByteCommand = command;
                        break;
                    case START_SYSEX:
                        parsingSysex = true;
                        sysexBytesRead = 0;
                        break;

                }
            }
        }
    }

    function pinMode(pin, mode) {
        var msg = new Uint8Array([PIN_MODE, pin, mode]);
        device.send(msg.buffer);
    }

    function analogRead(pin) {
        if (pin >= 0 && pin < pinModes[ANALOG].length) {
            return Math.round((analogInputData[pin] * 100) / 1023);
        } else {
            var valid = [];
            for (var i = 0; i < pinModes[ANALOG].length; i++)
                valid.push(i);
            console.log('ERROR: valid analog pins are ' + valid.join(', '));
            return;
        }
    }

    function digitalRead(pin) {
        if (!hasCapability(pin, INPUT)) {
            console.log('ERROR: valid input pins are ' + pinModes[INPUT].join(', '));
            return;
        }
        pinMode(pin, INPUT);
        return (digitalInputData[pin >> 3] >> (pin & 0x07)) & 0x01;
    }

    function analogWrite(pin, val) {
        if (!hasCapability(pin, PWM)) {
            console.log('ERROR: valid PWM pins are ' + pinModes[PWM].join(', '));
            return;
        }
        if (val < 0) val = 0;
        else if (val > 100) val = 100;
        val = Math.round((val / 100) * 255);
        pinMode(pin, PWM);
        var msg = new Uint8Array([
            ANALOG_MESSAGE | (pin & 0x0F),
            val & 0x7F,
            val >> 7]);
        device.send(msg.buffer);
        console.log(msg);
    }

    function digitalWrite(pin, val) {
        if (!hasCapability(pin, OUTPUT)) {
            console.log('ERROR: valid output pins are ' + pinModes[OUTPUT].join(', '));
            return;
        }
        var portNum = (pin >> 3) & 0x0F;
        if (val == LOW)
            digitalOutputData[portNum] &= ~(1 << (pin & 0x07));
        else
            digitalOutputData[portNum] |= (1 << (pin & 0x07));
        pinMode(pin, OUTPUT);
        var msg = new Uint8Array([
            DIGITAL_MESSAGE | portNum,
            digitalOutputData[portNum] & 0x7F,
            digitalOutputData[portNum] >> 0x07]);
        device.send(msg.buffer);
        console.log(msg);
    }
    
    // pour la catégorie LED, 3 fonctions: couleurLed, ledOn et expression
    // donc dans le msg: Start_Sysex, LED, NUMERO DE LA FONCTION, arguments...

    function couleurLed(numLed, R, G, B) {
        var msg = new Uint8Array([START_SYSEX,LED, 1, numLed, R, G, B,END_SYSEX]);
        console.log(msg);
        device.send(msg.buffer);
    }
    
    function ledOn(numLed){
        var msg = new Uint8Array([START_SYSEX,LED, 2, numLed, END_SYSEX]);
        console.log(msg);
        device.send(msg.buffer);
    }

    function motor(quelMoteur, direction, pwmMot, temps){
        var msg = new Uint8Array([START_SYSEX, MOTOR, moteur, dir, pwmMot, temps, END_SYSEX]);
        console.log(msg);
        device.send(msg.buffer);

    }

    function buzzer(numMelodie) {
        var msg = new Uint8Array([START_SYSEX,BUZZER, numMelodie,END_SYSEX]);
        console.log(msg);
        device.send(msg.buffer);
    }
    
    function expression(emotion) {
        var msg = new Uint8Array([START_SYSEX,LED, 3, emotion,END_SYSEX]);
        console.log(msg);
        device.send(msg.buffer);
    }

    ext.couleurLed = function(numLed, R, G, B){
        var threshold = 255;
        if (R > threshold) R = 255;
        if (R < 0) R = 0;
        if (G > threshold) G = 255;
        if (G < 0) G = 0;
        if (B > threshold) B = 255;
        if (B < 0) B = 0;       
        couleurLed(numLed, R, G, B); 
    }
    
    ext.ledOn = function(numLed, val){
        if (val == "On") etat = 1;
        if (val == "Off") etat = 0;
        ledOn(numLed);
    }

    ext.motor = function(quelMoteur, direction, pwmMot, temps){
        //var moteur;
        //var dir;
        if (quelMoteur == 'gauche'){
            moteur = 0;
        }
        else if (quelMoteur == 'droit'){
            moteur = 1;
        }

        if (direction == 'avance'){
            dir = 0;
        }
        else if (direction == 'recule'){
            dir = 1;
        }
        var threshold = 255;
        if (pwmMot > threshold) pwmMot = 255;
        if (pwmMot < 0) pwmMot = 0;
        if (temps > 120) temps = 120;        
        if (temps < 0) temps = 0;  

        motor(moteur, dir, pwmMot, temps); 
    }

    ext.buzzer = function (numMelodie) {
        if (numMelodie < 0) numMelodie = 1;
        if (numMelodie > 10) numMelodie = 10;
        buzzer(numMelodie);
    }
    
    ext.expression = function(emotion) {
        expression(emotion);
    }

    ext.whenConnected = function() {
        if (notifyConnection) return true;
        return false;
    };

    ext.analogWrite = function(pin, val) {
        analogWrite(pin, val);
    };

    ext.digitalWrite = function(pin, val) {
        if (val == menus[lang]['outputs'][0])
            digitalWrite(pin, HIGH);
        else if (val == menus[lang]['outputs'][1])
            digitalWrite(pin, LOW);
    };

    ext.analogRead = function(pin) {
        return analogRead(pin);
    };

    ext.digitalRead = function(pin) {
        return digitalRead(pin);
    };

    ext.whenAnalogRead = function(pin, op, val) {
        if (pin >= 0 && pin < pinModes[ANALOG].length) {
            if (op == '>')
                return analogRead(pin) > val;
            else if (op == '<')
                return analogRead(pin) < val;
            else if (op == '=')
                return analogRead(pin) == val;
            else
                return false;
        }
    };

    ext.whenDigitalRead = function(pin, val) {
        if (hasCapability(pin, INPUT)) {
            if (val == menus[lang]['outputs'][0])
                return digitalRead(pin);
            else if (val == menus[lang]['outputs'][1])
                return digitalRead(pin) === false;
        }
    };

    ext.connectHW = function(hw, pin) {
        hwList.add(hw, pin);
    };

    ext.readInput = function(name) {
        var hw = hwList.search(name);
        if (!hw) return;
        return analogRead(hw.pin);
    };

    // ext.whenButton = function(btn, state) {
    //     var hw = hwList.search(btn);
    //     if (!hw) return;
    //     if (state === 'pressed')
    //         return digitalRead(hw.pin);
    //     else if (state === 'released')
    //         return !digitalRead(hw.pin);
    // };

    // ext.isButtonPressed = function(btn) {
    //     var hw = hwList.search(btn);
    //     if (!hw) return;
    //     return digitalRead(hw.pin);
    // };
    
    ext.quandBouton = function(bouton, etatBouton){
        var indice = buttonList.indexOf(bouton); 
        var pin = buttonList[indice+1];
        if (!pin) return;
        if (etatBouton === 'pressé')
            return digitalRead(pin);
        else if (etatBouton === 'relaché')
            return !digitalRead(pin);
    }
    
    ext.boutonPresse = function(bouton) {
        var indice = buttonList.indexOf(bouton); 
        var pin = buttonList[indice+1];
        if (!pin) return;
        return digitalRead(pin);
    }

    ext.whenInput = function(name, op, val) {
        var hw = hwList.search(name);
        if (!hw) return;
        if (op == '>')
            return analogRead(hw.pin) > val;
        else if (op == '<')
            return analogRead(hw.pin) < val;
        else if (op == '=')
            return analogRead(hw.pin) == val;
        else
            return false;
    };

    ext.mapValues = function(val, aMin, aMax, bMin, bMax) {
        var output = (((bMax - bMin) * (val - aMin)) / (aMax - aMin)) + bMin;
        return Math.round(output);
    };

    ext._getStatus = function() {
        if (!connected)
            return { status:1, msg:'Disconnected' };
        else
            return { status:2, msg:'Connected' };
    };

    ext._deviceRemoved = function(dev) {
        console.log('Device removed');
        // Not currently implemented with serial devices
    };

    var potentialDevices = [];
    ext._deviceConnected = function(dev) {
        potentialDevices.push(dev);
        if (!device)
            tryNextDevice();
    };

    var poller = null;
    var watchdog = null;
    function tryNextDevice() {
        device = potentialDevices.shift();
        if (!device) return;

        device.open({ stopBits: 0, bitRate: 57600, ctsFlowControl: 0 });
        console.log('Attempting connection with ' + device.id);
        device.set_receive_handler(function(data) {
            var inputData = new Uint8Array(data);
            processInput(inputData);
        });

        poller = setInterval(function() {
            queryFirmware();
        }, 1000);

        watchdog = setTimeout(function() {
            clearInterval(poller);
            poller = null;
            device.set_receive_handler(null);
            device.close();
            device = null;
            tryNextDevice();
        }, 5000);
    }

    ext._shutdown = function() {
        // TODO: Bring all pins down
        if (device) device.close();
        if (poller) clearInterval(poller);
        device = null;
    };

    // Check for GET param 'lang'
    var paramString = window.location.search.replace(/^\?|\/$/g, '');
    var vars = paramString.split("&");
    var lang = 'en';
    /*
     for (var i=0; i<vars.length; i++) {
     var pair = vars[i].split('=');
     if (pair.length > 1 && pair[0]=='lang')
     lang = pair[1];
     }
     */

    var blocks = {
        en: [
            ['h', 'when device is connected', 'whenConnected'],
            //[' ', 'connect %m.hwOut to pin %n', 'connectHW', 'led A', 3],
            //[' ', 'connect %m.hwIn to analog %n', 'connectHW', 'rotation knob', 0],
            ['-'],
            //[' ', 'set %m.leds %m.outputs', 'digitalLED', 'led A', 'on'],
            //[' ', 'set %m.leds brightness to %n%', 'setLED', 'led A', 100],
            //[' ', 'change %m.leds brightness by %n%', 'changeLED', 'led A', 20],
            //['-'],
            //[' ', 'rotate %m.servos to %n degrees', 'rotateServo', 'servo A', 180],
            //[' ', 'rotate %m.servos by %n degrees', 'changeServo', 'servo A', 20],
            //['-'],
            //['h', 'Quand le %m.bouton est %m.etatBouton', 'whenButton', 'bouton 1', 'pressé'],
            //['b', '%m.bouton pressé?', 'isButtonPressed', 'bouton 1'],
            ['h', 'Quand le %m.bouton est %m.etatBouton', 'quandBouton', 'bouton 1', 'pressé'],
            ['b', '%m.bouton pressé?', 'boutonPresse', 'bouton 1'],
            //['-'],
            //['h', 'when %m.hwIn %m.ops %n%', 'whenInput', 'rotation knob', '>', 50],
            //['r', 'read %m.hwIn', 'readInput', 'rotation knob'],
            //['-'],
            //[' ', 'set pin %n %m.outputs', 'digitalWrite', 1, 'on'],
            //[' ', 'set pin %n to %n%', 'analogWrite', 3, 100],
            //['-'],
            //['h', 'when pin %n is %m.outputs', 'whenDigitalRead', 1, 'on'],
            //['b', 'pin %n on?', 'digitalRead', 1],
            //['-'],
            //['h', 'when analog %n %m.ops %n%', 'whenAnalogRead', 1, '>', 50],
            //['r', 'read analog %n', 'analogRead', 0],
            ['-'],
            //['r', 'map %n from %n %n to %n %n', 'mapValues', 50, 0, 100, -240, 240],
            [' ', 'Régler la LED %m.numLed à R: %n G: %n B: %n', 'couleurLed', 1],
            [' ', 'Mettre la LED n° %m.numLed sur %m.onOff', 'ledOn', '1', 'On'],
            ['-'],
            [' ', 'Le moteur %m.quelMoteur %m.direction avec un PWM à %n pendant %n', 'motor','gauche','avance',20,5],
            ['-'],
            [' ', 'Jouer la mélodie %m.melodie', 'buzzer', 1],
            [' ', "Mettre l'expression faciale n°%m.emotion", 'expression', 1]
        ]
    };

    var menus = {
        en: {
            bouton: ['bouton 1', 'bouton 2', 'bouton 3', 'bouton 4', 'bouton 5'],
            etatBouton: ['pressé', 'relaché'],
            //hwIn: ['rotation knob', 'light sensor', 'temperature sensor'],
            //hwOut: ['led A', 'led B', 'led C', 'led D', 'button A', 'button B', 'button C', 'button D', 'servo A', 'servo B', 'servo C', 'servo D'],
            onOff: ['On', 'Off'],
            //ops: ['>', '=', '<'],
            //servos: ['servo A', 'servo B', 'servo C', 'servo D'],
            numLed: ['1','5','10','15','20','24'],
            quelMoteur: ['gauche', 'droit'],
            direction: ['avance', 'recule'],
            melodie: [1,2,3],
            emotion: [1,2,3] // rigole, étoiles dans les yeux, coeur coeur
        }
    };

    var descriptor = {
        blocks: blocks[lang],
        menus: menus[lang],
        url: ''
    };

    ScratchExtensions.register('Notre extension de foufou', descriptor, ext, {type:'serial'});

})({});

/*    fr: [
 ['h', "Quand l'appareil est connecté", 'whenConnected'],
 [' ', 'Connecté %m.hwOut au pin %n', 'connectHW', 'LED A', 3],
 [' ', 'Connecté %m.hwIn au pin analogue %n', 'connectHW', 'Potentiomètre', 0],
 ['-'],
 [' ', 'Régler %m.leds LED %m.output Sortie', 'digitalLED', 'LED A', 'ON'],
 [' ', 'Régler %m.leds Luminosité de la LED à %n%', 'setLED', 'LED A', 100],
 [' ', 'Changer %m.leds Luminosité de la LED de %n%', 'changeLED', 'LED A', 20],
 ['-'],
 [' ', 'Tourner %m.servos Servo Moteur à %n degrés', 'rotateServo', 'Servo Moteur A', 180],
 [' ', 'Tourner %m.servos Servo Moteur de %n degrés', 'changeServo', 'Servo Moteur A', 20],
 ['-'],
 ['h', 'Quand %m.buttons Bouton est %m.btnStates', 'whenButton', 'Bouton A', 'Appuyé'],
 ['b', 'Le %m.buttons est-il pressé?', 'isButtonPressed', 'Bouton A'],
 ['-'],
 ['h', 'Quand %m.hwIn %m.ops %n%', 'whenInput', 'Potentiomètre', '>', 50],
 ['r', 'Lire %m.hwIn', 'readInput', 'Potentiomètre'],
 ['-'],
 [' ', 'Régler le Pin %n %m.outputs Sortie', 'digitalWrite', 1, 'ON'],
 [' ', 'Régler le Pin %n à %n%', 'analogWrite', 3, 100],
 ['-'],
 ['h', 'Quand le Pin %n est %m.outputs Sortie', 'whenDigitalRead', 1, 'ON'],
 ['b', 'Le Pin %n est-il démarré?', 'digitalRead', 1],
 ['-'],
 ['h', 'Quand le Pin analogique est %n %m.ops %n%', 'whenAnalogRead', 1, '>', 50],
 ['r', 'Lire le Pin Analogique %n', 'analogRead', 0],
 ['-'],
 ['r', 'Mapper %n de %n %n à %n %n', 'mapValues', 50, 0, 100, -240, 240]
 ]*/

/*        fr: {
 buttons: ['Bouton A', 'Bouton B', 'Bouton C', 'Bouton D'],
 btnStates: ['Appuyé', 'Relâché'],
 hwIn: ['Potentiomètre', 'Capteur de Lumière', 'Capteur de Temperature'],
 hwOut: ['LED A', 'LED B', 'LED C', 'LED D', 'Bouton A', 'Bouton B', 'Bouton C', 'Bouton D', 'Servo Moteur A', 'Servo Moteur B', 'Servo Moteur C', 'Servo Moteur D'],
 leds: ['LED A', 'LED B', 'LED C', 'LED D'],
 outputs: ['ON', 'OFF'],
 ops: ['>', '=', '<'],
 servos: ['Servo Moteur A', 'Servo Moteur B', 'Servo Moteur C', 'Servo Moteur D']
 }*/