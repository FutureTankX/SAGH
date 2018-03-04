/*
 * conf_timer.h
 *
 * Created: 15/2/2018 11:38:26 PM
 *  Author: Moath
 */ 


#ifndef CONF_TIMER_H_
#define CONF_TIMER_H_

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
/*--TIMER1 CONF--*/
#define TIMER1_CAPT IOPORT_CREATE_PIN(PORTB,0)
/*--Debug--*/
#define ENABLE_CLOCK_TIMER0 ture
#define ENABLE_CLOCK_TIMER1 true
#define ENABLE_CTC_TIMER0 true
#define ENABLE_INPUT_CAPTURE_TIMER1 true



void Timer0_Conf(void);
void Timer1_Conf(void);



void Timer0_Conf() {
	
	#if ENABLE_CLOCK_TIMER0
	PRR = (0 << PRTIM0);
	#endif

	#if ENABLE_CTC_TIMER0
	ioport_set_pin_dir(TIMER0_OUT, IOPORT_DIR_OUTPUT);
	TCCR0A = _BV(COM0A0) | _BV(WGM01);
	TIMSK0 = _BV(OCIE0A);
	TCCR0B = _BV(CS00);
	#endif
}

void Timer1_Conf() {
	
	#if ENABLE_CLOCK_TIMER1
	PRR = (0 << PRTIM1);
	#endif
	
	#if ENABLE_INPUT_CAPTURE_TIMER1
	ioport_set_pin_dir(TIMER1_CAPT, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(TIMER1_CAPT, IOPORT_MODE_PULLDOWN);
	TCCR1B = /*_BV(ICNC1) | */_BV(ICES1) | _BV(CS10);
	TIMSK1 = _BV(ICIE1);
	#endif
	
}

#endif /* CONF_TIMER_H_ */

