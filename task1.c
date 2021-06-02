/*********************************task1.c********************************************
					   		running mode function
**************************************************************************************/
#include "master.h"
isForward = -1; //0 : go backward mode, 1 : go forwardmode
isRotateLeft = -1; //0 : rotate right	1 : rotate left


void stop(){
	PORTA = 0x00;
}
void goForward(){
	PORTA = 0b01010101;
}
void goBackward(){
	PORTA = 0b10101010;
	PORTD = 0xff;
}
/****Rotation*****/
void goForwardLeft(){
	PORTA = 0b01010001;
}
void goForwardRight(){
	PORTA = 0b01010100;
}
void goBackwardLeft(){
	PORTA = 0b10100010;
	PORTD = 0xff;
}
void goBackwardRight(){
	PORTA = 0b10101000;
	PORTD = 0xff;
}
