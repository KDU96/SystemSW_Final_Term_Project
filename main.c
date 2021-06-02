#include "master.h"

ISR(USART0_RX_vect)
{
	flag=UDR0;
}

ISR(TIMER0_OVF_vect)
{
	msec++;
	if(msec == 1000){
		msec = 0;	sec++;
	}
}
int main(void)
{
	DDRB = 0xff;
	PORTB = 0x00;
	/*initialization*/
	initUsart();
	//hc_sr04_init();
	stop();
	USART1_Init(MYUBRR);
	Timer_Init();
	/*************Initialization for Solving Maze Problem**************/
	PathLog pl;
	PathLogInit(&pl);
	findPath(&pl);
	findPathDecision(pl);
#if 1
	while(1){
		solvingMaze(flagBuffer, 4);
		_delay_ms(100);

		while(1){
			decidingRunningMode();
			PORTB = sec;
			if(sec == 30){
				sec = 0;	break;
			}	
		}
	}
	#endif
}