/*
 * conf_timer.h
 *
 * Created: 15/2/2018 11:38:26 PM
 *  Author: Moath
 */ 

#define _BV(bit) \
(1 << (bit))


/*--TIMER0 CONF--*/
#define TIMER0_OUT IOPORT_CREATE_PIN(PORTD,6)
#define TIMER0_FREQ OCR0A
/*--TIMER0 FREQ SELECT--*/
#define TIMER0_30KHz 132
#define TIMER0_33KHz 120
#define TIMER0_36KHz 110
#define TIMER0_38KHz 103
#define TIMER0_40KHz 99
#define TIMER0_56KHz 70
/*--Debug--*/
#define ENABLE_CLOCK_TIMER0 1
#define ENABLE_CTC_TIMER0 1


void Timer_Conf(void);


#ifndef CONF_TIMER_H_
#define CONF_TIMER_H_

void Timer_Conf() {
	
	#if ENABLE_CLOCK_TIMER0
	PRR = (0 << PRTIM0);
	#endif

	#if ENABLE_CTC_TIMER0
	ioport_set_pin_dir(TIMER0_OUT, IOPORT_DIR_OUTPUT);
	TCCR0A = _BV(COM0A0) | _BV(WGM01);
	TIMSK0 = _BV(OCIE0A);
	TCCR0B =_BV(CS00);
	#endif
}

#endif /* CONF_TIMER_H_ */