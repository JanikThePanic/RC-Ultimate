#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "../../packet.h"

RF24 radio(7, 8);				 // pins for nrf CE, CSN
const byte address[6] = "00013"; // address to use over nrf

// declare packet struct
packet data;

void reset()
{
	// set joysticks
	data.joystick1.button = 0;
	data.joystick2.button = 0;
	data.joystick1.x = 128;
	data.joystick2.x = 128;
	data.joystick1.y = 128;
	data.joystick2.y = 128;
	// set potentiometers
	data.potentiometer1 = 0;
	data.potentiometer2 = 0;
	// set buttons
	data.button1 = 0;
	data.button2 = 0;
	data.button3 = 0;
	// set switchs
	data.switch1 = 0;
	data.switch2 = 0;
}

void setup()
{
	Serial.begin(9600);
	// config and start nrf
	radio.begin();
	radio.setAutoAck(false);
	radio.setDataRate(RF24_250KBPS);
	radio.openReadingPipe(0, address);
	radio.setPALevel(RF24_PA_MIN);
	radio.startListening();

	// set defualt joystick stats
	reset();
}

void loop()
{
	reset();

	if (radio.available())
	{
		radio.read(&data, sizeof(data));
	}

	// see joystick1
	Serial.print("x1: ");
	Serial.print(data.joystick1.x);
	Serial.print(" ");
	Serial.print("y1: ");
	Serial.print(data.joystick1.y);
	Serial.println();

	// see joystick2
	// Serial.print("x2: ");
	// Serial.print(data.joystick2.x);
	// Serial.print(" ");
	// Serial.print("y2: ");
	// Serial.print(data.joystick2.y);
	// Serial.println();

	// see switchs
	// Serial.print("switch1: ");
	// Serial.print(data.switch1);
	// Serial.print(" ");
	// Serial.print("switch2: ");
	// Serial.print(data.switch2);
	// Serial.println();

	// see buttons
	// Serial.print("button1: ");
	// Serial.print(data.button1);
	// Serial.print(" ");
	// Serial.print("button2: ");
	// Serial.print(data.button2);
	// Serial.print(" ");
	// Serial.print("button3: ");
	// Serial.print(data.button3);
	// Serial.println();
}