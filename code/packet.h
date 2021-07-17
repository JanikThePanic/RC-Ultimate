// struct for joystick
struct joystick
{
	byte x;
	byte y;
	byte button;
};

// stuct of the packet that will be send
struct packet
{
	joystick joystick1;
	joystick joystick2;
	byte potentiometer1;
	byte potentiometer2;
	byte switch1;
	byte switch2;
	byte button1;
	byte button2;
	byte button3;
};
