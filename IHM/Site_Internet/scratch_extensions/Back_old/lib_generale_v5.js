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
*/

(function(ext) {

    /*==============================================================================
    * VARIABLES
    *============================================================================*/

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


        var MOTOR = 0xA1,
            LED = 0xA2,
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

    /*==============================================================================
    * INIT FONCTION
    *============================================================================*/

/*        function init() {

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
        }*/

    /*==============================================================================
    * SENDING FONCTION
    *============================================================================*/

/*        function processSysexMessage() {
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
        }*/

    /*==============================================================================
    * RECEPTION FUNCTION
    *============================================================================*/

/*        function processInput(inputData) {
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
        }*/

    /*==============================================================================
    * MOTOR FONCTIONS
    *============================================================================*/

/*        function motor(moteur, direction, pwmMot, temps){
            var msg = new Uint8Array([START_SYSEX, MOTOR, 1, moteur, direction, pwmMot, temps, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
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
            if (pwm > threshold) pwmMot = 255;
            if (pwm < 0) pwmMot = 0;
            if (temps > 120) temps = 120;        
            if (temps < 0) temps = 0;  

            motor(moteur, dir, pwmMot, temps); 
        }

        //----------------------------------------------------------------------------

        function mouvementVitesse(mvt, pwm) {
            var msg = new Uint8Array([START_SYSEX, MOTOR, 2, mvt, pwm, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.mouvementVitesse = function(mvt, pwm) {
            if (mvt == 'avancer') mvt = 0;
            else if (mvt == 'reculer') mvt = 1;
            else if (mvt == 'tourner') mvt = 2;
            else if (mvt == 'arrêt') mvt = 3;
            var threshold = 255;
            if (pwm > threshold) pwm = 255;
            if (pwm < 0) pwm = 0;
            mouvementVitesse(mvt, pwm);
        }

        //----------------------------------------------------------------------------
        
        function mouvementDistance(dir, distance) {
            var msg = new Uint8Array([START_SYSEX, MOTOR, 3, dir, distance, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.mouvementDistance = function(direction, distance) {
            if (direction == 'avance'){
                dir = 0;
            }
            else if (direction == 'recule'){
                dir = 1;
            }
            if (distance < 0 ) distance = 0;
            if (distance > 30) distance = 30;
            mouvementDistance(dir, distance);
        }

        //----------------------------------------------------------------------------

        function tourner(angle) {
            var msg = new Uint8Array([START_SYSEX, MOTOR, 4, angle, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.tourner = function(angle) {
            tourner(angle); // Repasse à 0 si l'angle est supérieur à 256. Allez savoir pourquoi
        }*/

    /*==============================================================================
    * LED FONCTIONS
    *============================================================================*/
        
/*        function couleurLed(numLed, R, G, B) {
            var msg = new Uint8Array([START_SYSEX,LED, 1, numLed, R, G, B,END_SYSEX]);
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

        //----------------------------------------------------------------------------

        function ledOn(numLed){
            var msg = new Uint8Array([START_SYSEX,LED, 2, numLed, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.ledOn = function(numLed, val){
            if (val == "On") etat = 1;
            if (val == "Off") etat = 0;
            ledOn(numLed);
        }

        //----------------------------------------------------------------------------

        function expression(emotion) {
            var msg = new Uint8Array([START_SYSEX,LED, 3, emotion,END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.expression = function(emotion) {
            expression(emotion);
        }*/

    /*==============================================================================
    * BUZZER FONCTIONS
    *============================================================================*/
    
/*        function playSon(frequency) {
            var msg = new Uint8Array([START_SYSEX, BUZZER,1, frequency, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.playSon(frequency)  {
            playSon(frequency);
        }

        //----------------------------------------------------------------------------

        function playNote(octave, note) {
            var msg = new Uint8Array([START_SYSEX, BUZZER,2, octave, note, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.playNote(octave,note)   {
            playNote(octave,note);
        }

        //----------------------------------------------------------------------------

        function playNoteDemiTone(octave, note, tone) {
            var msg = new Uint8Array([START_SYSEX, BUZZER,3, octave, note, tone, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.playNoteDemiTone(octave,note,tone)  {
            playNoteDemiTone(octave,note,tone);
        }

        //----------------------------------------------------------------------------

        function playSonDelay(frequency, time) {
            var msg = new Uint8Array([START_SYSEX, BUZZER,4, frequency, time, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.playSonDelay(frequency,time)    {
            playSonDelay(frequency,time);
        }

        //----------------------------------------------------------------------------

        function buzzerRythme(time) {
            var msg = new Uint8Array([START_SYSEX, BUZZER,5, time, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.buzzerRythme(time)  {
            buzzerRythme(time);
        }

        //----------------------------------------------------------------------------

        function buzzerAttente(time) {
            var msg = new Uint8Array([START_SYSEX, BUZZER,6, time, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.buzzerAttente(time) {
            buzzerAttente(time);
        }

        //----------------------------------------------------------------------------

        function playMelody(num) {
            var msg = new Uint8Array([START_SYSEX, BUZZER,7, num, END_SYSEX]);
            console.log(msg);
            device.send(msg.buffer);
        }

        ext.playMelody = function (numMelodie) {
            if (numMelodie < 0) numMelodie = 1;
            if (numMelodie > 10) numMelodie = 10;
            buzzer(numMelodie);
        }*/

    /*==============================================================================
    * BUTTON FONCTIONS
    *============================================================================*/

/*        ext.quandBouton = function(bouton, etatBouton){
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
        }*/

    /*==============================================================================
    * OTHER FONCTIONS
    *============================================================================*/

/*        function hasCapability(pin, mode) {
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
        };*/
    
    /*==============================================================================
    * UTILITY FONCTIONS
    *============================================================================*/


        ext.whenConnected = function() {
            if (notifyConnection) return true;
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
        var lang = 'fr';
        

        /*
         for (var i=0; i<vars.length; i++) {
         var pair = vars[i].split('=');
         if (pair.length > 1 && pair[0]=='lang')
         lang = pair[1];
         }
         */


    var blocks = {
        fr: [

            /*==============================================================================
            * BLOCKS LIB PRIMAIRE
            *============================================================================*/

                /*
                // MOTOR BLOCKS
                    [' ', '%m.direction de %n cm', 'mouvementDistance', 'avance', 20],
                    [' ', 'Tourner de %n degrés', 'tourner', 90],
                // LED BLOCKS
                    [' ', 'Régler la LED %m.numLed à R: %n G: %n B: %n', 'couleurLed', 1],
                    [' ', "Mettre l'expression faciale n°%m.emotion", 'expression', 1],
                // BUZZER BLOCKS
                    [' ', 'Jouer la mélodie %m.melodie', 'playMelody', 1],

                // OTHER
                    ['h', "Quand l'appareil est connecté", 'whenConnected'],
                    ['h', 'Quand le %m.bouton est %m.etatBouton', 'quandBouton', 'bouton 1', 'pressé'],
                    ['b', '%m.bouton pressé?', 'boutonPresse', 'bouton 1']
                */
                    
            /*==============================================================================
            * BLOCKS LIB COLLEGE
            *============================================================================*/

                // MOTOR BLOCKS
                    [' ', '%m.direction de %n cm', 'mouvementDistance', 'avance', 20],
                    [' ', 'Le moteur %m.quelMoteur %m.direction avec un PWM à %n pendant %n', 'motor','gauche','avance',20,5],
                    [' ', 'Tourner de %n degrés', 'tourner', 90],
                // LED BLOCKS
                    [' ', 'Régler la LED %m.numLed à R: %n G: %n B: %n', 'couleurLed', 1],
                    [' ', 'Mettre la LED n° %m.numLed sur %m.onOff', 'ledOn', '1', 'On'],
                    [' ', "Mettre l'expression faciale n°%m.emotion", 'expression', 1],
                // BUZZER BLOCKS
                    [' ','Octave : %n note : %n','playNote','bla','bla'],
                    [' ','Octave : %n note : %n tone : %n','playNoteDemiTone','bla','bla','bla'],
                    [' ','Frequency : %n Hz time : %n','playSonDelay','bla','bla'],
                    [' ','Rythme du buzzer : %n s','buzzerRythme','bla'],
                    [' ','Attente buzzer : %n s','buzzerAttente','bla'],
                    [' ', 'Jouer la mélodie %m.melodie', 'playMelody', 1],               
                // OTHER
                    ['h', "Quand l'appareil est connecté", 'whenConnected'],
                    ['h', 'Quand le %m.bouton est %m.etatBouton', 'quandBouton', 'bouton 1', 'pressé'],
                    ['b', '%m.bouton pressé?', 'boutonPresse', 'bouton 1']
                
            /*==============================================================================
            * BLOCKS OTHER
            *============================================================================*/

                //[' ', 'set %m.leds brightness to %n%', 'setLED', 'led A', 100],
                //[' ', 'change %m.leds brightness by %n%', 'changeLED', 'led A', 20],

                //[' ', 'rotate %m.servos to %n degrees', 'rotateServo', 'servo A', 180],
                //[' ', 'rotate %m.servos by %n degrees', 'changeServo', 'servo A', 20],
                //[' ', 'Mouvement du robot: %m.mvt avec un PWM à %n', 'mouvementVitesse', 'avancer',20],

                //['h', 'Quand le %m.bouton est %m.etatBouton', 'whenButton', 'bouton 1', 'pressé'],
                //['b', '%m.bouton pressé?', 'isButtonPressed', 'bouton 1'],

        ]
    };

    var menus = {
        fr: {
            //  BOUTON
            bouton: ['bouton 1', 'bouton 2', 'bouton 3', 'bouton 4', 'bouton 5'],
            etatBouton: ['pressé', 'relaché'],
            onOff: ['On', 'Off'],

            //  LED
            numLed: ['1','5','10','15','20','24'],
            emotion: [1,2,3], // rigole, étoiles dans les yeux, coeur coeur

            //  MOTEUR
            quelMoteur: ['gauche', 'droit'],
            direction: ['avance', 'recule'],
            mvt: ['avancer', 'reculer', 'tourner', 'arrêt'],

            //  BUZZER
            melodie: [1,2,3] // même si y'en a qu'une
        }
    };

    var descriptor = {
        blocks: blocks[lang],
        menus: menus[lang],
        url: ''
    };

    ScratchExtensions.register('Niveau Primaire', descriptor, ext, {type:'serial'});

})({});