/*
 * SAGH.c
 *
 * Created: 15/2/2018 10:16:05 PM
 *  Author: Moath
 *		v0.2.0
 */ 

#include <main.h>

bool FirstTime = true;
bool flipFlag = true;

uint16_t TimeStamp1;
uint16_t TimeStamp2;
uint16_t TimeDelta;
uint8_t ReceivedNumber;
uint8_t SignalBuffer[256];
uint8_t SignalBufferBytes[15];
uint8_t SignalBufferLocation;

#define ENABLE_TIMER0 true	
#define ENABLE_TIMER1 true
#define CHECK_Bit(var,pos) ((var) & (1<<(pos)))

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

// 	 nokia_lcd_init();
// 	 nokia_lcd_clear();
// 	 //itoa(AC_ON[0],buffer,10);
// 	 nokia_lcd_write_string("SAGH",1);
// 	 nokia_lcd_set_cursor(0, 10);
// 	 //nokia_lcd_write_string(buffer, 3);
// 	 nokia_lcd_render();
// 	 
	#if ENABLE_TIMER0
		Timer0_Conf();
		TIMER0_FREQ = TIMER0_38KHz;
		TCCR0A &=~ _BV(COM0A0); /* Disconnect The Timer from the Pin */
	#endif
	
	#if ENABLE_TIMER1
		Timer1_Conf();
	#endif
	
	/* Enable Global Interrupt. */
	cpu_irq_enable();
	
	while (1) {
		nop();
	/*
	  mark (3400);
	  space(1536);

	  sendbyte(0x23);
	  sendbyte(0xcb);
	  sendbyte(0x26);
	  sendbyte(0x01);
	  sendbyte(0x00);
	  sendbyte(0x24);
	  sendbyte(0x03);
	  sendbyte(0x07);
	  sendbyte(0x0a);
	  sendbyte(0x00);
	  sendbyte(0x00);
	  sendbyte(0x00);
	  sendbyte(0x00);
	  sendbyte(0x4d);
	  
	  // stop
 	  mark (260);
 	  space(0);
// 	  
// 	  mark (500);
  
	  TCCR0A &=~ _BV(COM0A0);
	 _delay_s(3);
  */
	}
}

/* Timer1 overflow interrupt handler */
ISR(TIMER1_OVF_vect) {
	nop(); /* no operation */
}

/* dummy handler */
ISR(BADISR_vect) {
	nokia_lcd_clear();
	nokia_lcd_write_string("ERR BAD ISR",1);
	nokia_lcd_render();
}

/* Timer0 compare interrupt handler */
EMPTY_INTERRUPT(TIMER0_COMPA_vect);

/* Timer1 input capture interrupt handler */
ISR(TIMER1_CAPT_vect) {
	
	cpu_irq_disable();
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
			
			if ((ReceivedNumber == 0) || (ReceivedNumber == 1)) {
				/*Do Nothing.*/
			}
			else if ((ReceivedNumber % 2) && (TimeDelta > 1000)) {
				SignalBuffer[SignalBufferLocation] = 1;
				SignalBufferLocation++;
			}
			else if (ReceivedNumber % 2) {
				SignalBuffer[SignalBufferLocation] = 0;
				SignalBufferLocation++;
			}
			
			TimeStamp1 = 0;
			flipFlag ? (TIMER1_RISING) : (TIMER1_FALLING);
			flipFlag = !flipFlag;
			ReceivedNumber++;
			
			CLEAR_TIMER1
		}
		if (ReceivedNumber == 227) {
			Array_to_Byte (SignalBufferBytes,SignalBuffer,SignalBufferLocation);
		}
		cpu_irq_enable();
}

void Array_to_Byte (uint8_t __out_bytes_arr[], uint8_t __arr[], uint16_t size) {
	
	int __bytes_num,__count;
	
	__bytes_num = ceil(size/8); 
	for (int j=0;j<__bytes_num;j++) {
		for (int i=0;i<8;i++) {
			__arr[__count] <<= i;
			__out_bytes_arr[j] += __arr[__count];
			__count++;
		}	
	}
}

void sendbyte(uint8_t Byte) {
	int i;
	for (i = 0; i < 8; i++) {
		if ((Byte >> i) & 1){
			// one
			mark (380); //530
			space(1250); //1320
			} else {
			// zero
			mark (380);
			space(260);
		}
	}
}


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

