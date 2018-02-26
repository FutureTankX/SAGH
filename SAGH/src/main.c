/*
 * SAGH.c
 *
 * Created: 15/2/2018 10:16:05 PM
 *  Author: Moath
 *		v0.0.4
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

volatile bool flag;


#define ENABLE_TIMER0 true	
#define ENABLE_TIMER1 true


int main (void)
{
	/* Calibrate Internal RC Oscillator */
	OSCCAL = 0xAB;
	
// 	/* System Clock Initialization. */
// 	sysclk_init();
// 	PRR = (0 << PRSPI);
// 	board_init();
// 	sysclk_enable_module(POWER_RED_REG0,PRTIM0);

	/* Initializes the IOPORT service */
	ioport_init();
	/* Enable Global Interrupt. */
	cpu_irq_enable();
	
	LED_init();
	
	#if ENABLE_TIMER0
		Timer0_Conf();
		TIMER0_FREQ = TIMER0_36KHz;
	#endif
	
	#if ENABLE_TIMER1
		Timer1_Conf();
	#endif

	
	while (1)
	{
		
	}
}


/*Timer1 input capture interrupt handler*/
ISR(TIMER1_CAPT_vect)  
{
	cpu_irq_disable();
	flag = !flag;
	LED(flag);
	delay_ms(200);
	cpu_irq_enable();
} 