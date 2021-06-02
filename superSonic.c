#include "master.h"

/* initializing global variable*/
frontSensorData = 0;
//rearSensorData = 0;

unsigned int getEcho(void)
{
	Trigger_ON; _delay_us(10); Trigger_OFF;  // 10uS
	while(Echo==0x00); TCCR1B=0x02; TCNT1=0x00;
	while(Echo!=0x00); TCCR1B=0x08;
	return (TCNT1/58); //cm
}
void hc_sr04_init(void)
{
	DDRF=0x03;               // PF0 ouput Trigger, PF2 input Echo
	TCCR1B=0x08;             // Set timer up in CTC mode
	TCCR0 = 0x1F;
	OCR0 = 243;
}
void testSupersonic(void){
	hc_sr04_init();
	DDRB = 0xff;
	frontSensorData = getEcho();
	_delay_ms(100);
	PORTB = frontSensorData;
}
void showDistance(void){
		char distance[10];
		sprintf(distance, "%d", frontSensorData);
		USART1_Transmit_String("$I\r"); 
		LCD_Transmit_String(1,2,"Show Distance");
		USART1_Transmit('\r'); 
		LCD_Transmit_String(2,2, distance); 
		USART1_Transmit('\r'); 
		_delay_ms(100);
}