#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "../../packet.h"

RF24 radio(7, 8);				 // start nrf object with pins for CE and CSN
const byte address[6] = "00013"; // address to use over nrf

int lostConnectionCounter;

// declare packet struct
packet data;

// default positions of controller
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
	data.potentiometer1 = 1;
	data.potentiometer2 = 1;
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

	// start with 0 lost connection packets
	lostConnectionCounter = 0;
	// set the varibles to the defualt controller stats
	reset();
}

void loop()
{

	if (radio.available())
	{
		// assign the data we catch to the data struct
		radio.read(&data, sizeof(data));
		// if we get data, we can reset the no connection counter
		lostConnectionCounter = 0;
	}
	else
	{
		// if it doesnt catch any data, we  will upper the count of no data
		lostConnectionCounter++;
		// after not seeing data 15 times, we can assume we lost connection
		if (lostConnectionCounter >= 15)
		{
			Serial.println("Lost Connection");
			// set the varibles to the defualt controller stats
			// this avoids a robot for example from driving into a wall after losing connection
			reset();
		}
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

	// see joystick buttons
	// Serial.print("joystick1: ");
	// Serial.print(data.joystick1.button);
	// Serial.print(" ");
	// Serial.print("joystick1: ");
	// Serial.print(data.joystick2.button;
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