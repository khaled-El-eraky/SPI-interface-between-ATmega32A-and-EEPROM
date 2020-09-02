/*
 * SPI.c
 *
 * Created: 9/1/2020 3:30:06 PM
 *  Author: Khaled
 */ 


#include "Microcontroller_config.h"
#include "SPI.h"
#include "DIO.h"

#define NULL_Ptr	 ((void*)0x00)


ISR(SPI_STC_vector)
{
	if (SPI0.SPI_InterruptCall != NULL_Ptr)
	{
		SPI0.SPI_InterruptCall();
	}
}

SPI_ConfigStruct SPI0 = {.SPI_InterruptCall = NULL_Ptr};

void SPI_Init(void)
{
	/* Clear the two registers SPCR AND SPSR */
	SPCR->allRegister = LOW;
	SPSR->allRegister = LOW;
	
	switch(SPI0.Control)
	{
		case SPI_Disable:
		/* DO NOTHING */
		break;
		case SPI_Enable:
				switch(SPI0.Mode)
				{
					case SPI_MASTER:
					/* Select Master by setting the MSTR bit */
					SPCR->bits.b4 = HIGH;
					/* Config MOSI, SCK, SS as OUTPUT */
					DIO_pinConfigure(DIOB,PIN5,OUTPUT);
					DIO_pinConfigure(DIOB,PIN7,OUTPUT);
					DIO_pinConfigure(DIOB,PIN4,OUTPUT);
					//PORTB |= (1<<PB4) | (1<<5);
					break;
					case SPI_SLAVE:
					/* Config MISO as OUTPUT */
					DIO_pinConfigure(DIOB,PIN6,OUTPUT);
					break;
					default:
					break;
				}
				switch(SPI0.DataOrder)
				{
					case SPI_LSB:
					SPCR->bits.b5 = HIGH;
					break;
					case SPI_MSB:
					break;
					default:
					break;
				}
				switch(SPI0.InterruptState)
				{
					case SPI_InterruptDisable:
					break;
					case SPI_InterruptEnable:
					SPCR->bits.b7 = HIGH;
					break;
					default:
					break;
				}
				switch(SPI0.ClockMode)
				{
					case SPI_CLKMode0:
					break;
					case SPI_CLKMode1:
					SPCR->bits.b2 = HIGH;
					break;
					case SPI_CLKMode2:
					SPCR->bits.b3 = HIGH;
					/* when using SPI Mode 3 or Mode 2 (CLK IDLE STATE must = HIGH)	*/
					DIO_pinWrite(DIOB , PIN7 , HIGH);
					break;
					case SPI_CLKMode3:
					SPCR->bits.b2 = HIGH;
					SPCR->bits.b3 = HIGH;
					DIO_pinWrite(DIOB , PIN7 , HIGH);
					break;
					default:
					break;
				}
				switch(SPI0.Freq)
				{
					case SPI_FCPU_BY_2:
					SPSR->bits.b0 = HIGH;
					break;
					case SPI_FCPU_BY_4:
					break;
					case SPI_FCPU_BY_8:
					SPSR->bits.b0 = HIGH;
					SPCR->bits.b0 = HIGH;
					break;
					case SPI_FCPU_BY_16:
					SPCR->bits.b0 = HIGH;
					break;
					case SPI_FCPU_BY_32:
					SPSR->bits.b0 = HIGH;
					SPCR->bits.b1 = HIGH;
					break;
					case SPI_FCPU_BY_64:
					SPCR->bits.b1 = HIGH;
					break;
					case SPI_FCPU_BY_128:
					SPCR->bits.b0 = HIGH;
					SPCR->bits.b1 = HIGH;
					break;
					default:
					break;
				}
		/* Enable SPI Communication */
		SPCR->bits.b6 = HIGH;
		break;
		default:
		break;
	}
}
	
	
	uint8_t SPI_ReadWrite_Blocking(uint8_t Data)
	{
		/* Transmit Data Using SPI Bus */
		SPDR = Data;
		
		/* Check if a Write Collision Error Occurred */
		if ( (SPSR->bits.b6) != 0)
		{
			SPI0.Error = SPI_WriteCollison;
		}
		
		/* Block till The End of Transmision */
		while ( (SPSR->bits.b7) == 0 ) {}
		
		/* return Rx Data From SPI */
		return SPDR;
	}
	
	
	uint8_t SPI_ReadWrite_NonBlocking(uint8_t Data)
	{
				/* Transmit Data Using SPI Bus */
				SPDR = Data;
				/* Check if a Write Collision Error Occurred */
				if ( (SPSR->bits.b6)  != 0)
				{
					SPI0.Error = SPI_WriteCollison;
				}
				/* return Rx Data From SPI */
				return SPDR;	
	}