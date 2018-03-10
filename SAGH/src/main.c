/*
 * SAGH.c
 *
 * Created: 15/2/2018 10:16:05 PM
 *  Author: Moath
 *		v0.1.0
 */ 
/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#define F_CPU 8000000UL

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <main.h>

bool FirstTime = true;
bool flipFlag = true;

uint16_t TimeStamp1;
uint16_t TimeStamp2;
uint16_t TimeDelta;
uint16_t SignalBufferLocation = 0;
uint16_t SignalBuffer[300];

#define ENABLE_TIMER0 true	
#define ENABLE_TIMER1 true

int main (void)
{
	/* Calibrate Internal RC Oscillator */
	OSCCAL = 0xAB;
	
	/* Turnoff Watch Dog Timer */
	WDT_off();
	
// 	/* System Clock Initialization. */
// 	sysclk_init();
// 	PRR = (0 << PRSPI);
// 	board_init();
// 	sysclk_enable_module(POWER_RED_REG0,PRTIM0);

	/* Initializes the IOPORT service */
	ioport_init();
	/* Initializes the USART */
	USART_Init(UBRR);
	
	//LED_init();
	
	 nokia_lcd_init();
	 nokia_lcd_clear();
	 nokia_lcd_write_string("START",1);
	 nokia_lcd_set_cursor(0, 10);
	 nokia_lcd_write_string("TEST", 3);
	 nokia_lcd_render();
	 
	#if ENABLE_TIMER0
		Timer0_Conf();
		TIMER0_FREQ = TIMER0_36KHz;
	#endif
	
	#if ENABLE_TIMER1
		Timer1_Conf();
	#endif
	
	/* Enable Global Interrupt. */
	cpu_irq_enable();

	
	while (1)
	{
		
	}
}


/* Timer1 overflow interrupt handler */
ISR(TIMER1_OVF_vect)
{
	nop(); /* no operation */
}

/* dummy handler */
ISR(BADISR_vect)
{
	nokia_lcd_clear();
	nokia_lcd_write_string("ERR",1);
	nokia_lcd_render();
}

/* Timer0 compare interrupt handler */
EMPTY_INTERRUPT(TIMER0_COMPA_vect);

/* Timer1 input capture interrupt handler */
ISR(TIMER1_CAPT_vect)
{
	if (FirstTime)
		{
			CLEAR_TIMER1
			TimeStamp1 = 0;
			
			flipFlag ? (TIMER1_RISING) : (TIMER1_FALLING);
			flipFlag = !flipFlag;
			FirstTime = false;
		}
		
		else if (FirstTime == false)
		{
			TimeStamp2 = ICR1;
			TimeDelta = TimeStamp2 - TimeStamp1;
			SignalBuffer[SignalBufferLocation] = TimeDelta;
			SignalBufferLocation++;
			TimeStamp1 = 0;
			
			flipFlag ? (TIMER1_RISING) : (TIMER1_FALLING);
			flipFlag = !flipFlag;
			
			CLEAR_TIMER1
		}
}
