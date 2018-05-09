/*
 * SAGH.c
 *
 * Created: 15/2/2018 10:16:05 PM
 *  Author: Moath
 *		v0.3.0
 */ 

#include <main.h>

bool FirstTime = true;
bool flipFlag = true;

uint16_t TimeStamp1;
uint16_t TimeStamp2;
uint16_t TimeDelta;
uint8_t ReceivedNumber;
char buffer[20];
uint8_t SignalBuffer[256];
uint8_t SignalBufferBytes[15];
uint8_t SignalBufferLocation;
int SerialRecived;

#define ENABLE_TIMER0 true	
#define ENABLE_TIMER1 true
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

int main (void)
{
	/* Calibrate Internal RC Oscillator */
	OSCCAL = 0xAB;
	/* Turnoff Watch Dog Timer */
	WDT_off();
	/* System Clock Initialization. */
	sysclk_init();
	/* Initializes the Board */
	board_init();
	/* Initializes the IOPORT service */
	ioport_init();
	/* Initializes the USART */
	USART_Init(UBRR);
	/* Initializes Timer0 in CTC mode */
	Timer0_Conf();
	TIMER0_FREQ = TIMER0_38KHz;
	TCCR0A &=~ _BV(COM0A0); /* Disconnect The Timer from the Pin */
	/* Initializes Timer1 in Normal mode */
	Timer1_Conf();
	/* Enable Global Interrupt. */
	cpu_irq_enable();
	nokia_lcd_init();
 	nokia_lcd_clear();
	
	
	while (1) {

 		nokia_lcd_set_cursor(0, 10);
		nokia_lcd_write_string("1:AC ON 2:IRQ EN 3:IRQ !EN",1);
 		nokia_lcd_render();
		printf("1: RESET ALL\n\r");
		printf("2: IRQ ENABLE\n\r");
		printf("3: IRQ DISABLE\n\r");
		printf("4: Display Received Signal\n\r");
		printf("5: Send Received Signal\n\r");
		printf("6: Encode Signal\n\r");
		
		scanf("%d",&SerialRecived);
		switch (SerialRecived) {
			default:
				break;
			case 1:
				Reset_all();
				break;
			 case 2:
				cpu_irq_enable();
				break;
			 case 3:
				cpu_irq_disable();
				break;
			 case 4:
				nokia_lcd_set_cursor(0,0);
				itoa(ReceivedNumber,buffer,10);
 				nokia_lcd_write_string(buffer,1);
				nokia_lcd_render();
				break;
			 case 5:
				mark (START_HIGH);
				space(START_LOW);
				for (int i=0;i<14;i++) {
					sendbyte(SignalBufferBytes[i]);
				}
				mark(SHORT);
				TCCR0A &=~ _BV(COM0A0);
				break;
			case 6:
				Array_to_Byte (SignalBufferBytes,SignalBuffer,SignalBufferLocation);
				break;
				
		}
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
			TimeStamp2 = ICR1/8;
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
		cpu_irq_enable();
}

void Array_to_Byte (uint8_t __out_bytes_arr[], uint8_t __arr[], uint16_t size) {
	
	int __bytes_num,__count=0;
	
	__bytes_num = ceil(size/8); 
	for (int j=0;j<__bytes_num;j++) {
		for (int i=0;i<8;i++) {
			__arr[__count] <<= i;
			__out_bytes_arr[j] += __arr[__count];
			__count++;
		}	
	}
}
void Reset_all(void) {
	memset(&SignalBuffer,0,sizeof(SignalBuffer));
	memset(&SignalBufferBytes,0,sizeof(SignalBufferBytes));
	memset(&SignalBufferLocation,0,1);
	memset(&ReceivedNumber,0,sizeof(uint8_t));
	memset(&buffer,0,sizeof(buffer));
}
void sendbyte(uint8_t Byte) {
	int i;
	for (i = 0; i < 8; i++) {
		if ((Byte >> i) & 1){
			// one
			mark (SHORT); //530
			space(LONG); //1320
			} else {
			// zero
			mark (SHORT);
			space(SHORT);
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
	__delay_us(time);
}

void space(uint16_t time) {
	TCCR0A &=~ _BV(COM0A0);
	__delay_us(time);
}
