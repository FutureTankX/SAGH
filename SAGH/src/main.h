/*
 * main.h
 *
 * Created: 15/2/2018 11:59:05 PM
 *  Author: Moath
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include <asf.h>
#include <conf_timer.h>
#include <conf_uart.h>
//#include "io/io.h"
#include <delay/delay_x.h>
#include <LCD/nokia5110.h>


#define HIGH 1
#define LOW 0

#define START_HIGH 3400
#define START_LOW 1536
#define LONG 1250
#define SHORT 380

void WDT_off(void);
void mark(uint16_t time);
void space(uint16_t time);
void sendbyte(uint8_t Byte);
void Array_to_Byte (uint8_t __out_bytes_arr[], uint8_t __arr[], uint16_t size);
void Reset_all(void);

#endif /* MAIN_H_ */