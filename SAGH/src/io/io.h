/*
 * io.h
 *
 * Created: 25/2/2018 6:01:33 PM
 *  Author: Moath
 */ 


#define LED_pin IOPORT_CREATE_PIN(PORTC,5)

#ifndef IO_H_
#define IO_H_



void LED (bool stats);
void LED_init(void);

void LED_init() {
	ioport_set_pin_dir(LED_pin, IOPORT_DIR_OUTPUT);
}



void LED(bool stats) {
	
	if (stats) ioport_set_pin_level(LED_pin,IOPORT_PIN_LEVEL_HIGH);
	else  ioport_set_pin_level(LED_pin,IOPORT_PIN_LEVEL_LOW);
}


#endif /* IO_H_ */