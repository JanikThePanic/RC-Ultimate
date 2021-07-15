#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "../../packet.h"

RF24 radio(7, 8);				 // pins for nrf CE, CSN
const byte address[6] = "00013"; // address to use over nrf

// declare packet struct
packet data;

void setup()
{
	Serial.begin(9600);
	// config and start nrf
	radio.begin();
	radio.setAutoAck(false);
	radio.setDataRate(RF24_250KBPS);
	radio.openWritingPipe(address);
	radio.setPALevel(RF24_PA_MIN);
	radio.stopListening();
}

void loop()
{

	// send packet over nrf
	radio.write(&data, sizeof(data));
}