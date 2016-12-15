cmake_minimum_required(VERSION 3.6)
project(robot_main)

set(robot_main_BOARD uno)
set(robot_main_PORT /dev/ttyUSB0)

set(SOURCE_FILES
    .vs/robot_main/v14/.suo
    __vm/.robot_main.vsarduino.h
    __vm/Compile.vmps.xml
    __vm/Configuration.Debug.vmps.xml
    __vm/Configuration.Release.vmps.xml
    __vm/Upload.vmps.xml
    Debug/board.buildinfo
    Debug/Button.cpp.d
    Debug/Button.cpp.o
    Debug/ControlPanel.cpp.d
    Debug/ControlPanel.cpp.o
    Debug/core.a
    Debug/Led.cpp.d
    Debug/Led.cpp.o
    Debug/Menu.cpp.d
    Debug/Menu.cpp.o
    Debug/Motor.cpp.d
    Debug/Motor.cpp.o
    Debug/Program.cpp.d
    Debug/Program.cpp.o
    Debug/robot_main.cpp.d
    Debug/robot_main.cpp.o
    Debug/robot_main.elf
    Debug/robot_main.hex
    Debug/robot_main.ino.elf
    Debug/robot_main.ino.hex
    Debug/Sensor.cpp.d
    Debug/Sensor.cpp.o
    Release/board.buildinfo
    Release/Button.cpp.d
    Release/Button.cpp.o
    Release/ControlPanel.cpp.d
    Release/ControlPanel.cpp.o
    Release/core.a
    Release/Led.cpp.d
    Release/Led.cpp.o
    Release/Menu.cpp.d
    Release/Menu.cpp.o
    Release/Motor.cpp.d
    Release/Motor.cpp.o
    Release/Program.cpp.d
    Release/Program.cpp.o
    Release/robot_main.cpp.d
    Release/robot_main.cpp.o
    Release/robot_main.elf
    Release/robot_main.hex
    Release/robot_main.ino.elf
    Release/robot_main.ino.hex
    Release/Sensor.cpp.d
    Release/Sensor.cpp.o
    Button.cpp
    Button.h
    ControlPanel.cpp
    ControlPanel.h
    Led.cpp
    Led.h
    Menu.cpp
    Menu.h
    Motor.cpp
    Motor.h
    Program.cpp
    Program.h
    robot_main.ino
    robot_main.sln
    robot_main.vcxproj
    robot_main.vcxproj.filters
    Sensor.cpp
    Sensor.h
    SensorType.h)

add_executable(robot_main ${SOURCE_FILES})