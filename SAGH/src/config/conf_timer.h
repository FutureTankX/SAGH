/*
 * conf_timer.h
 *
 * Created: 15/2/2018 11:38:26 PM
 *  Author: Moath
 */ 

#define _BV(bit) \
(1 << (bit))

#define PWM_OUT IOPORT_CREATE_PIN(PORTD,6)
#define PWM_DUTYCYCLE OCR0A

#define ENABLE_CLOCK_TIMER0 1
#define ENABLE_FASTPWM_TIMER0 1


void Timer_Conf(void);


#ifndef CONF_TIMER_H_
#define CONF_TIMER_H_

void Timer_Conf() {
	
	#if ENABLE_CLOCK_TIMER0
	PRR = (0 << PRTIM0);
	#endif

	#if ENABLE_FASTPWM_TIMER0
	

	ioport_set_pin_dir(PWM_OUT, IOPORT_DIR_OUTPUT);
	/*DDRD |= _BV(PD6);*/
	TCCR0A = _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
	TCCR0B =_BV(CS00);
	//PWM_DutyCycle = 255/2;
	#endif
	
}

#endif /* CONF_TIMER_H_ */