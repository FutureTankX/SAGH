/*
 * main.h
 *
 * Created: 15/2/2018 11:59:05 PM
 *  Author: Moath
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000

#include <asf.h>
#include <conf_timer.h>
#include <conf_uart.h>
#include <io/io.h>
#include <delay/delay_x.h>
#include <LCD/nokia5110.h>



#define HIGH 1
#define LOW 0

uint16_t AC_ON[]={3484,
	1626,
	537,
	1284,
	537,
	1248,
	538,
	382,
	539,
	383,
	538,
	383,
	537,
	1248,
	538,
	382,
	539,
	382,
	538,
	1292,
	537,
	1247,
	538,
	383,
	538,
	1248,
	537,
	382,
	539,
	382,
	538,
	1249,
	537,
	1247,
	538,
	426,
	538,
	1249,
	537,
	1249,
	538,
	381,
	539,
	383,
	537,
	1249,
	537,
	330,
	591,
	382,
	538,
	1293,
	536,
	383,
	539,
	382,
	539,
	383,
	538,
	384,
	538,
	383,
	538,
	383,
	538,
	384,
	538,
	427,
	538,
	383,
	538,
	382,
	537,
	383,
	536,
	383,
	538,
	382,
	538,
	353,
	568,
	382,
	538,
	427,
	538,
	382,
	538,
	1248,
	538,
	382,
	536,
	384,
	537,
	1249,
	537,
	383,
	537,
	383,
	537,
	1292,
	536,
	1218,
	568,
	381,
	538,
	383,
	538,
	383,
	538,
	383,
	537,
	384,
	537,
	382,
	538,
	1291,
	538,
	1247,
	537,
	1249,
	537,
	384,
	537,
	383,
	536,
	383,
	538,
	383,
	538,
	383,
	537,
	422,
	544,
	1248,
	537,
	383,
	538,
	1248,
	538,
	383,
	537,
	382,
	537,
	383,
	538,
	384,
	537,
	428,
	537,
	384,
	537,
	382,
	538,
	383,
	537,
	384,
	537,
	383,
	539,
	381,
	537,
	383,
	538,
	427,
	538,
	382,
	538,
	384,
	537,
	382,
	538,
	383,
	537,
	384,
	537,
	384,
	538,
	384,
	537,
	428,
	538,
	383,
	539,
	382,
	538,
	383,
	538,
	382,
	537,
	384,
	538,
	383,
	538,
	383,
	538,
	427,
	538,
	382,
	538,
	383,
	538,
	382,
	537,
	383,
	538,
	382,
	538,
	383,
	537,
	384,
	537,
	1293,
	537,
	383,
	538,
	1248,
	537,
	1250,
	536,
	383,
	538,
	384,
	537,
	1219,
	568,
	383,
538};

void WDT_off(void);
void mark(uint16_t time);
void space(uint16_t time);

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

void mark(uint16_t time) {
	TCCR0A |= _BV(COM0A0);
	_delay_us(time);
}

void space(uint16_t time) {
	TCCR0A &=~ _BV(COM0A0);
	_delay_us(time);
}

#endif /* MAIN_H_ */