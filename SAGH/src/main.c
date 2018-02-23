/*
 * SAGH.c
 *
 * Created: 15/2/2018 10:16:05 PM
 * Author : Moath
 * v0.0.1
 */ 

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#define F_CPU 20000000UL

#include <asf.h>
#include <main.h>
#include <util/delay.h>

#define ENABLE_TIMER0 1


int main (void)
{
	OSCCAL = 0xAC; //Calibrate Internal RC Oscillator
	
	/* system clock initialization. */
	sysclk_init();
	board_init();
	ioport_init();
	
	#if ENABLE_TIMER0
	Timer_Conf();
	#endif
	
	PWM_DUTYCYCLE = 128;	
	while (1);
	{
	
	}
}

// ISR(TIMER0_COMPA_vect)
// {
// 	//TIMSK0 = _BV(OCIE0A)
// } 