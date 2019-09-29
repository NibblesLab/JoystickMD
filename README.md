# JoystickMD
**pre-release version**

This is the project to make a joystick for Megadrive/Genesis Mini by Arduino.
I don't have SEGA's 6B-stick, then I am using the MSX compatible stick now.
I will renew this project when I get a 6B-stick.

## Prepare the project
1. Arduino

Arduino Leonardo or compatible is accepted.

2. Library

[Arduino Joystick Library](https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-2.0) must be installed.
Backup original "Joystick.cpp" and "Joystick.h" files, then put the same files contains in this project instead of originals.

3. PID/VID

Megadrive/Genesis Mini can accept the restricted devices.
We must set the acceptable ID (VID and PID) the Arduino.
Please refer [how to change VID/PID](https://forum.arduino.cc/index.php?topic=532127.0).

## Compile the sketch
"JoystickMD.ino" is the sample sketch.
I use the Sparkfun's pro micro.
Modify the source by matching your board.

## API
### Axis
Megadrive/Genesis Mini have 2 available axis, X and Y.
API's axis value have 16 bits, but Mini needs only lower 8 bits(unsigned).
Please note to use APIs, `Joystick.setXAxisRange()`/`Joystick.setXAxis()`/`Joystick.setYAxisRange()`/`Joystick.setYAxis()`.

### Number corresponding to the button
Megadrive/Genesis Mini's Gamepad has 10 buttons.
The numbers and buttons table to use `Joystick.setButton()`/`Joystick.pressButton()`/`Joystick.releaseButton()` API as follows:

|Number|Button|
|:-:|:-:|
|0|Y|
|1|B|
|2|A|
|3|X|
|4|Z|
|5|C|
|8|MODE|
|9|START|

## Let's fun ;-)
