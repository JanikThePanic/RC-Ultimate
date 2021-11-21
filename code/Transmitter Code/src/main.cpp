#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "../../packet.h"

RF24 radio(7, 8);				 // pins for nrf CE, CSN
const byte address[6] = "00013"; // address to use over nrf

// define pins for joysticks
#define joystick001Button 2
#define joystick002Button 3
#define joystick001X A1
#define joystick001Y A2
#define joystick002X A3
#define joystick002Y A4
// define pins for potentiometers
#define potentiometer001 A5
#define potentiometer002 A6
// define pins for buttons
#define button001 4
#define button002 5
#define button003 6
// define pins for switchs
#define switch001 9
// turns out, u can not use the 10th digital pin when using SPI as it is the SS pin
// so instead we will be using A0
#define switch002 A0

// declare packet struct
packet data;

void setup()
{
	// config and start nrf
	radio.begin();
	radio.setAutoAck(false);
	radio.setDataRate(RF24_250KBPS);
	radio.openWritingPipe(address);
	radio.setPALevel(RF24_PA_MIN);
	radio.stopListening();

	// set pin modes
	pinMode(joystick001Button, INPUT_PULLUP);
	pinMode(joystick002Button, INPUT_PULLUP);
	pinMode(switch001, INPUT_PULLUP);
	pinMode(switch002, INPUT_PULLUP);
	pinMode(button001, INPUT_PULLUP);
	pinMode(button002, INPUT_PULLUP);
	pinMode(button003, INPUT_PULLUP);
}

void loop()
{
	// read joysticks
	data.joystick1.button = !digitalRead(joystick001Button);
	data.joystick2.button = !digitalRead(joystick002Button);
	data.joystick1.x = map(analogRead(joystick001X), 0, 1023, 0, 255);
	data.joystick2.x = map(analogRead(joystick001X), 0, 1023, 0, 255);
	data.joystick1.y = map(analogRead(joystick001Y), 0, 1023, 0, 255);
	data.joystick2.y = map(analogRead(joystick002Y), 0, 1023, 0, 255);
	// read potentiometers
	data.potentiometer1 = map(analogRead(potentiometer001), 0, 1023, 0, 255);
	data.potentiometer2 = map(analogRead(potentiometer002), 0, 1023, 0, 255);
	// read buttons
	data.button1 = !digitalRead(button001);
	data.button2 = !digitalRead(button002);
	data.button3 = !digitalRead(button003);
	// read switchs
	data.switch1 = !digitalRead(switch001);
	data.switch2 = !digitalRead(switch002);

	// send packet over nrf
	radio.write(&data, sizeof(data));
}