#include "master.h"
# if 1
void USART1_Init(unsigned int ubrr){
	UBRR1H = (unsigned char)(ubrr >> 8); 
	UBRR1L = (unsigned char)ubrr; 
	UCSR1B =(1<<RXEN) | (1<<TXEN);
	UCSR1C = (1<<USBS) | (3 << UCSZ0);
}
void USART1_Transmit(char data){
	while(!((UCSR1A)&(1<<UDRE1))); 
	UDR1 = data; 
}

char USART1_Receive(){
	while(!(UCSR1A &(1<<RXC1)));
	return UDR1; 
}
void USART1_Transmit_String(char *str){
	while(*str != '\0')
	USART1_Transmit(*str++);
}

void LCD_Transmit(int x, int y, char data) {
	USART1_Transmit_String("$G,"); 
	USART1_Transmit((char)(x+48)); 
	USART1_Transmit(',');
	USART1_Transmit((char)(y+48)); 
	USART1_Transmit('\r'); 
	USART1_Transmit_String("$T,"); 
	USART1_Transmit(data); 
}

void LCD_Transmit_String(int x, int y, char* String){//print string on LCD
	USART1_Transmit_String("$G,"); 
	USART1_Transmit((char)(x+48)); 
	USART1_Transmit(',');
	USART1_Transmit((char)(y+48)); 
	USART1_Transmit('\r'); 
	USART1_Transmit_String("$T,"); 
	while(*String)
	{
		USART1_Transmit(*String++); 
	}
}

#endif
