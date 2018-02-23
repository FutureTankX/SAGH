/*
 * conf_timer.h
 *
 * Created: 15/2/2018 11:38:26 PM
 *  Author: Moath
 */ 

#define _BV(bit) \
(1 << (bit))

#ifndef CONF_TIMER_H_
#define CONF_TIMER_H_

void Timer_Conf() {
	PRR = (0 << PRTIM0);
	DDRD |= _BV(PD6);
	TCCR0A = _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
	TCCR0B =_BV(CS00);
	OCR0A = 255/2;
}

#endif /* CONF_TIMER_H_ */