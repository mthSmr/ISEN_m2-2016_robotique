(function(ext) {
    // Code to be run when the user closes the window, reloads the page, etc.    
    ext._shutdown = function() {};
    
    // Shows the status of the extension 0 = red, 1 = yellow, and 2 = green
    ext._getStatus = function() {
        return {status: 2, msg: 'Ready'};
    };
    // Descriptions of the blocks and menus the extension adds
    var descriptor ={
    "extensionName": "s2a_fm - Scratch to Arduino",
    "extensionPort": 50209,
    "url": "https://github.com/MrYsLab/PyMata",
    blocks: [
        [
            " ",
            "%m.pin_state Digital Pin %n for %m.digital_pin_mode",
            "digital_pin_mode",
            "Enable",
            "PIN",
            "Input"
        ],
        [
            " ",
            "%m.pin_state Analog Pin (A) %n for Input",
            "analog_pin_mode",
            "Enable",
            "PIN"
        ],
        [
            "",
            "DigitalWrite Set Pin %n to %m.high_low",
            "digital_write",
            "PIN",
            0
        ],
        [
            "",
            "AnalogWrite (PWM) Set Pin %n to %n",
            "analog_write",
            "PIN",
            "VAL"
        ],
        [
            "",
            "Play Tone on Pin: %n HZ: %n ms: %n",
            "play_tone",
            "PIN",
            1000,
            500
        ],
        [
            "",
            "Turn Tone Off for Pin: %n",
            "tone_off",
            "PIN"
        ],
        [
            "",
            "Move Servo on Pin %n Deg: %n",
            "set_servo_position",
            "PIN",
            90
        ],
        [
            "r",
            "Read Digital Pin %n",
            "digital_read",
            "PIN"
        ],
        [
            "r",
            "Read Analog Pin (A) %n",
            "analog_read",
            "PIN"
        ],
        [
            "",
            "Debugger %m.off_on",
            "debugger",
            "Off"
        ],
        [
            "",
            "Move Robot with speed %n during: %n cm",
            "set_servo_position",
            50,
            10
        ]
    ],
    "menus": {
        "pin_state": [
            "Enable",
            "Disable"
        ],
        "digital_pin_mode": [
            "Input",
            "Output",
            "PWM",
            "Servo",
            "Tone",
            "SONAR"
        ],
        "high_low": [
            "0",
            "1"
        ],
        "off_on": [
            "Off",
            "On"
        ]
    }
}
;
    // Register the extension
    ScratchExtensions.register('Test Lib', descriptor, ext);
})({});