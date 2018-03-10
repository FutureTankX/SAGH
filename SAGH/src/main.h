/*
 * main.h
 *
 * Created: 15/2/2018 11:59:05 PM
 *  Author: Moath
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <util/delay.h>
#include <asf.h>
#include <conf_timer.h>
#include <conf_uart.h>
#include <io/io.h>
#include <LCD/nokia5110.h>


#define HIGH 1
#define LOW 0

void WDT_off(void);

void WDT_off(void)
{
	cpu_irq_disable();
	/* Clear WDRF in MCUSR */
	MCUSR &=~ _BV(WDRF);
	/* Write logical one to WDCE and WDE */
	/* Keep old pre-scaler setting to prevent unintentional time-out */
	WDTCSR |= _BV(WDCE) | _BV(WDE);
	/* Turn off WDT */
	WDTCSR = 0x00;
	cpu_irq_enable();
}

#endif /* MAIN_H_ */