/*
 * SAGH.c
 *
 * Created: 15/2/2018 10:16:05 PM
 *  Author: Moath
 *		v0.0.3
 */ 
/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#define F_CPU 8000000UL

#include <asf.h>
#include <main.h>
#include <util/delay.h>


#define ENABLE_TIMER0 1


int main (void)
{
	OSCCAL = 0xAB; //Calibrate Internal RC Oscillator
	
	/* system clock initialization. */
	sysclk_init();
	board_init();
	ioport_init();
	
	#if ENABLE_TIMER0
	Timer_Conf();
	#endif
	TIMER0_FREQ = TIMER0_36KHz;

	while (1)
	{
		
		LED(HIGH);
		delay_ms(500);
		LED(LOW);
		delay_ms(500);
	}
}

// ISR(TIMER0_COMPA_vect)
// {
// 	//TIMSK0 = _BV(OCIE0A)
// } 