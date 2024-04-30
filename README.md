# 4180-Final-Project: The Money Machine
Repo for final project for a class, a bluetooth robot that uses sonar to detect and annoy roommates
By Wesley Swanson

## Ok but what is the money machine?

Well, it plays Money Machine by 100 gecs a lot, but that's the byproduct of my "very good design decisions". Basically, I wanted to make something goofy with the robot chassis that I didn't use

Said goofy thing is a robot to annoy my roommates, using a sonar to detect motion in front of the robot which plays a horrendously downsampled Money Machine and LEDs to the beat when motion is detected

Also said robot is Bluetooth controlled so anyone with a Bluefruit app can annoy the people around them!
But I mainly annoyed myself when building this thing

Such is the life of the engineer

## Parts List

* mbed LPC1768
* White Solderless Breadboard
* Sparkfun Shadow Chassis ROB-13301
* Sparkfun Hobby Gearmotor ROB-13302
* Sparkfun Rubber Tire Pair, 65mm ROB-13259
* Sparkfun Speaker COM-11089
* Sparkfun Mono Audio Amp Breakout - TPA2005D1 BOB-11044
* Sparkfun Ultrasonic Distance Sensor HC-SR04 SEN-15569
* SparkFun Motor Driver - Dual TB6612FNG ROB -14450
* Sparkfun DC Barrel Jack Adapter PRT - 10811
* Adafruit Bluefruit LE - UART Friend 2479

## Wiring The Robot

Connect battery pack to + and - (6V power, all chips support it)

### Motor Driver
* VM -> + rail
* VCC -> + rail
* GND -> - rail
* AO1 -> right motor + pin
* AO2 -> right motor - pin
* BO1 -> left motor + pin
* BO2 -> left motor - pin
* PWMA -> p22 mbed
* PWMB -> p21 mbed
* AI1 -> p6 mbed
* AI2 -> p5 mbed
* BI1 -> p7 mbed
* BI2 -> p8 mbed
* STBY -> + rail
### Bluetooth
* Vin -> + rail
* GND -> - rail
* CTS -> - rail
* TXO -> p27 mbed
* RXI -> p28 mbed
### Sonar
* Vcc -> + rail
* GND -> - rail
* Trig -> p12 mbed
* Echo -> p13 mbed
### Amp + Speaker
* IN+ -> p18 mbed
* IN- -> - rail
* PWR+ -> + rail
* PWR- -> - rail
* OUT+ -> + on the speaker
* OUT- -> - on the speaker
### Mbed
* GND -> - on the rail (bind battery and mbed grounds)
* Vin -> + on the rail

## Current Code Functionality

By connecting your phone to the Adafruit Bluefruit chip in UART, you can drive the robot. Up on the pad is up but left is down, right is left turn, and down is right turn. This needs to be patched at some point.

With a 500mm (half a meter) change in front of the sonar, the speaker will load up and play the first 28 seconds of Money Machine by 100 gecs. The sonar is very sensitive and the sound cone will detect basically any motion in front of it.
This may be a problem if you wish to contain your sanity. 

## Future Work

Make some patch updates and only have the LEDs play when Money Machine is loaded in

Add an LED controller and a lot more LEDs

Get a better speaker

Add WD40 to the wheels

Program a robot dance routine

Build an interface for a user to input any song/color pattern into the robot for custom annoyances
