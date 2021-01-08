# FotoTrap - an open hardware foto trap

FotoTrap is an open source / open hardware project to build a high speed fotography trigger and a foto trap to take fotos of animals in the wild.

## Usage of High Speed Mode

### Preparation
1. Connect you room light to the relais. Do this in such a way that the light is turned off, when the relais is pulled up.
2. Connect your flash to the pc cable. If there is no connector for the pc sync cable, use a horse shoe adapter.
Make sure to connect the flash correctly to the horse shoe adapter. The front side of the flash must be headed to the closed side of the horse shoe adapter (like mounting the flash from the rear end of your camera).
3. Connect your camera to the trigger cable (stereo jack).
4. Connect the FotoTrap to a power supply. Either connect a 9V battery to Gnd and Vin of the Arduino on the Bread Board or, connect the Arduino to an USB power supply.
5. Turn on your flash, choose the lowest flash energy possible (this will result in the shortest exposure time).
6. Turn on your camera. Choose camera settings so that the sutter is opened and closed via the trigger cable (remote electronic trigger).
7. Do a manual focus and go into bulb mode.

### Take the picture

![high speed image](images/highspeed.jpeg "a ballon captured just in the moment when it pops")

1. Press the green button. This will pull the relais, so the light is turned off. And the shutter will be opened. The LED will start to blink.
2. After the LED has stopped blinking the FotoTrap is listening for any sharp noise.
3. Take a needle and pop a balloon, take a hammer and smash a glass,...
4. The sound will be registered by the microphone and a flash will be triggered. The shutter will be closed and the relais will be released, so that the light will be turned back on.
5. Inspect your foto and adjust distance of flash etc. You might find it use full to go for indirect lighting.
6. You might need to adjust the sensitivity of the microphone. You can do so by adjusting the trimmer on the microphone module. Be careful when turning the trimmer. There are two green LEDs on the module. The first LED is the power on LED, this should be constantly on. The second LED is flushed whenever the microphone detects a sound. So you can watch this second LED to find the best position of the trimmer.

## Build the FotoTrap

### Housing

The FotoTrap is put in a box to house all the components.

![housing](images/housing.jpeg "two buttons, a microphone and a remote trigger cable for shutter and flush")

From the outside you see a red button. Pressing the red button turns on the motion-detection-mode. In this mode the camera is triggered when the PIR detects a motion.

The green button triggers the high-speed-fotography-mode. In this mode the flash is triggered when the microphone detects a sound. The microphone is below the green button. Under the PIR you see a status LED.

There are two cables the radio jack cable to trigger the camera and the pc sync cable to trigger the flash.

The FotoTrap is build with an Arduino nano, that is installed on a bread board together with some opto-couplers. Microphone, and PIR are attached to the housing. Jumper wires connect detectors, buttons and status LED to the bread board. The trigger wires are soldered to multipin connectors which are placed directly on the bread board. A cord grip is used to prevent that the triggers are pulled out fromt the bread board.

![overview of the inside](images/inside.jpeg "general setupu of the FotoTrap")

The microphone module and the PIR have trimmers to adjust for their sensitivity. (on the PIR there are two trimmers, one for sensitivity, the other for the time, when the PIR is set to waiting mode after detecting a motion.)

The sensors are hot glued to the housing, as well as the relais. Buttons are just screwed to the front panel.

![sensors and relais](images/sensors.jpeg "componets simply hot glued to the housing")

We use a breadboard to build up the control circuit. This is the easies way and it allows for changes later on.

![breadboard](images/breadboard.jpeg "The circuit is based on an Arduino Nano and build on a breadboard")

The Arduino is placed so that the USB plug is positioned to the rear of the box. So the USB cable can easily be connected to reprogram the microcontroller.

The pins in the trigger cables need to be shortcutted in order to trigger the flash or the camera respectively. This is done by optocouplers which form the central part in the circuit (besides the Arduino).

![optocouplers](images/optocoupler.jpeg "The optocouplers shortcut the pins between the trigger cables")

### Components

1. Arduino nano with an ATmega328. I bought this on [Amazon](https://smile.amazon.de/gp/product/B078SBBST6/ref=ppx_yo_dt_b_asin_title_o08_s01?ie=UTF8&psc=1). Order a couple of these, they are cheap, and you might damage some during setup. There is an excellent Tutoria on how to solder the pins to the Arduino nano on [youtube](https://www.youtube.com/watch?v=wDbUChzxIrE).

![Arduino](images/arduino.png)
2. A microphone module like the youmile detecor module, which can be purchased on [Amazon](https://smile.amazon.de/gp/product/B07Q1BYDS7/ref=ppx_yo_dt_b_asin_title_o07_s00?ie=UTF8&psc=1). The microphone is connected to the breadboard to provide Vin (5V+) and GND. The signal is provided by the OUT Pin, it is directly connected to a digital-read-pin on the Arduino. There are two green LED on the microphone controller. The first LED is on when the micorophone is connected to power, the second LED is flushed when a sound is detectd. The sensitivity can be adjusted with the trimmer / potentiometer. ATTENTION: The signal goes to LOW when a sound is detected. ![microphone](images/microphone.png).
3. The infrared motion detector. I use a module from AZDelivery on [Amazon](https://smile.amazon.de/gp/product/B07CNBYRQ7/ref=ppx_yo_dt_b_asin_title_o08_s01?ie=UTF8&psc=1). The semispherical cap can be removed, then you see the printing of the lables of pins (again Vin, GND and OUT). On the module there is a jumper bridge and two trimmers. The jumper should be set to the edge of the board, then the circuit is in binary detection mode. The two potentiometers set sensitivity and a timer for the detection interval. We will not need the latter, because we will time the detection interval on the Arduino

![PIR](images/PIR.png)

![PIR module](images/PIRmodule.png)

4. The Relais is also from AZDelivery and can be purchased on [Amazon](https://smile.amazon.de/gp/product/B07TYG14N6/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1) as well. Again we have Vin and GND and a signal pin. As the relais is not a detector but an actor, we connect the IN pin to a digital-write-pin on the Arduino. The consumer is connected to the screw terminals. You will only use two of the three terminals. Either the two at the top, or the two at the bottom. This depends wether you want to open or close the circuit when the relais is pulled up.

![Relais](images/relais.png)

5. The optocoupler are central for the project. I used PC817 from [Amazon](https://smile.amazon.de/gp/product/B07X46SYQT/ref=ppx_yo_dt_b_asin_title_o09_s00?ie=UTF8&psc=1).

![DIP optocoupler with 4 pins](images/DIPOptocoupler.png)

![Schematic](images/schematic.png)

6. A red status LED.

7. A micro button in DIP packaging to be installed directly on the breadboard (for testing purposes).

8. Several resistors. Use a [color code calculatur](https://www.digikey.de/en/resources/conversion-calculators/conversion-calculator-resistor-color-code). To find the right resistors.
3x 240 &Omega; for the pull up buttons. 3x 560 &Omega; for the opto couplers. 1x 100 &Omega; for the red LED.

9. A green and a red button, e.g. from [Amazon](https://www.amazon.de/gp/product/B077FH7TGD/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1)

![Button](images/button.png)

10. A horse shoe flash adapter from [Amazon](https://www.amazon.de/gp/product/B005GR28MK/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)

![horseshoe](images/horseshoe.png)

### Circuit

Find the Fritzing file in this project.

![circuit](images/circuit.png)
