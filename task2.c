#include "master.h"

void initUsart()
{
	DDRA=0xff;
	DDRD=0xff;
	UCSR0A=0x00;
	UCSR0B=0x98;
	UCSR0C=0x06;
	UBRR0H=0;
	UBRR0L=103;
	SREG=0x80;
}
void decidingRunningMode(){
	USART1_Transmit_String("$I\r"); 
	LCD_Transmit_String(1,2," Running Mode"); // x=1,y=2 인 위치에 char 문자 출력
	TIMSK = 0x00;
	if(flag=='G')   //forward
		{
		isForward = 1;
		if(isRotateLeft == 1){
			goForwardLeft();
		}
		else if(isRotateLeft== 0){
			goForwardRight();
		}
		else if(isRotateLeft== -1){
			goForward();
		}
	}
	if(flag=='B')   //back
	{
		isForward = 0;
		if(isRotateLeft == 1){
			goBackwardLeft();
		}
		else if(isRotateLeft == 0){
			goBackwardRight();
		}
		else if(isRotateLeft == -1){
			goBackward();
		}
	}
	
	if(flag=='L')   //left
	{
		isRotateLeft = 1;
		if(isForward == 1){
			goForwardLeft();
		}
		else if(isForward == 0){
			goBackwardLeft();
		}
	}
	if(flag=='R')    //right
	{
		isRotateLeft = 0;
		if(isForward == 1){
			goForwardRight();
		}
		else if(isForward == 0){
			goBackwardRight();
		}
	}
	if(flag=='Q')
	{	TIMSK = (1 << TOIE0);
		isForward = -1;
		isRotateLeft = -1;
		stop();
	}
}