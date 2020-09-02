/*
 * Microcontroller_config.h
 * <This File Contains ALL ATmega32A Register Address, Memory Map Information and >
 
 * Created: 2/5/2020 2:22:29 PM
 *  Author: Khaled Osama Eraky
 */ 



#ifndef MICROCONTROLLER_CONFIG_H_
#define MICROCONTROLLER_CONFIG_H_

#include "Macros.h"
#include "StdTypes.h"


/******************************* CPU Related Defines *******************************************************/
#define F_CPU       (16000000UL) 
#define BuadRate    (9600)

/******************************* CPU Internal Registers <SFRs & GPRs> **************************************/
#define IO_OFFSET	(0x20)

#define ATMEGA32_SREG		((reg8*)(0x3F+IO_OFFSET))
#define ATMEGA32A_MCUCR		((reg8*)(0x35+IO_OFFSET))
#define ATMEGA32_MCUCSR		((reg8*)(0x34+IO_OFFSET))
#define ATMEGA32_GICR		((reg8*)(0x3B+IO_OFFSET))
#define GIFR				((reg8*)(0x3A+IO_OFFSET))


/******************************UART Registers****************************************************************/ 
/*UCSRA*/
#define UCSRA (*(vuint8_t*)0x2b)     /*data in registers not addresses*/
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

/*UCSRB*/
#define UCSRB (*(vuint8_t*)0x2a)
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

/* UCSRC */
#define UCSRC (*(vuint8_t*)0x40)
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0

/*Data register*/
#define UDR	  (*(vuint8_t*)0x2c)

/*Baud rate registers*/
#define UBRRH (*(vuint8_t*)0x40)
#define UBRRL (*(vuint8_t*)0x29)

/********************************************** SPI Registers *******************************************************/
/* SPI Data Register */
#define SPDR    (*(vuint8_t*)0x0F)

/* SPSR */
#define SPSR    ((reg8*)0x0E)
#define SPIF    7
#define WCOL    6
/* bits 5-1 is reserved */
#define SPI2X   0

/* SPCR */
#define SPCR    ((reg8*)0x0D)
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0

/*****************************************  Attribute Defines FOR AVR Interrupt Handling ************************************************/
#define _VECTOR(N) 		__vector_ ## N
#define ISR(V,...)	void V (void) __attribute__ ((signal)) __VA_ARGS__;\
void V (void)
/******************************************* Global Interrupt Related Macros **************************************/

/*{} not () as those () will higher the piriority..and () as I will call it as a func*/
#define GLOBAL_INTERRUPT_ENABLE()	{ATMEGA32_SREG->bits.b7=1;}
#define GLOBAL_INTERRUPT_DISABLE()	{ATMEGA32_SREG->bits.b7=0;}
	
/****************************** Interrupt addresses form Vector table in flash memory***********************/

#define SPI_STC_vector			_VECTOR(12)

/******************************************* User Types For AVR MCU **************************************/

typedef union
{
	vuint8_t allRegister;
	struct
	{
		vuint8_t b0:1;
		vuint8_t b1:1;
		vuint8_t b2:1;
		vuint8_t b3:1;
		vuint8_t b4:1;
		vuint8_t b5:1;
		vuint8_t b6:1;
		vuint8_t b7:1;
	}bits;
}reg8;

typedef struct
{
	reg8 pin;
	reg8 ddr;
	reg8 port;
}DIO_Struct;


#endif /* MICROCONTROLLER CONFIG_H_ */