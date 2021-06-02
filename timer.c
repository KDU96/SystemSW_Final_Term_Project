#include "master.h"

void Timer_Init()
{
	TCCR0 = (4 << CS0);
	TIMSK = (1 << TOIE0);
	TCNT0 = 6;
	msec = 0;
	sec = 0;
}