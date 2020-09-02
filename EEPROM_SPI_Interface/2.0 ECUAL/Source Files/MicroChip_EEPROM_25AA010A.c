/*
 * MicroChip_EEPROM_25AA010A.c
 *
 * Created: 9/2/2020 2:37:49 AM
 *  Author: Khaled
 */ 




#include "SPI.h"
#include "MicroChip_EEPROM_25AA010A.h"
#include "Microcontroller_config.h"
#include <util/delay.h>
#include "DIO.h"


#define WREN_OPCODE		(0x06)
#define WRTIE_OPCODE	(0x02)
#define READ_OPCODE		(0x03)

#define DUMMY_DATA		(0x00)

static void SPI_CS_Control(uint8_t State)
{
	switch(State)
	{
		case LOW:
		/*  SET the CS by clearing the SS pin on ATmege32A >> PB0  */
		DIO_pinWrite(DIOB , PIN0 , LOW);

		break;
		case HIGH:
		/*  Clear the CS by Setting the SS pin on ATmege32A >> PB0  */
		DIO_pinWrite(DIOB , PIN0 , HIGH);
		break;
		default:
		break;
	}	
}

void EEPROM_Init(void)
{
	SPI0.Control = SPI_Enable;
	SPI0.Mode = SPI_MASTER;
	SPI0.ClockMode = SPI_CLKMode3;
	SPI0.DataOrder = SPI_MSB;
	SPI0.Freq = SPI_FCPU_BY_8;
	SPI0.InterruptState = SPI_InterruptDisable;
	/* Config CS Pin  as OUTPUT */
	DIO_pinConfigure(DIOB , PIN0 , OUTPUT);
	//DIO_pinWrite(DIOB , PIN0 , HIGH);
	SPI_Init();
}

void EEPROM_WriteByte(uint8_t Data , unsigned short address)
{
	/* Select EEPROM By Applying 0 to CS */
	SPI_CS_Control(LOW);
	/* Write Latch Enable */
	SPI_ReadWrite_Blocking(WREN_OPCODE);
	/* Apply High to CS to Make Write Latch Enable Instruction Executed*/
	SPI_CS_Control(HIGH);
	_delay_ms(50);
	/* Select EEPROM By Applying 0 to CS */
	SPI_CS_Control(LOW);
	SPI_ReadWrite_Blocking(WRTIE_OPCODE);
	SPI_ReadWrite_Blocking(address);
	SPI_ReadWrite_Blocking(Data);
	SPI_CS_Control(HIGH);
}

uint8_t EEPROM_ReadByte(unsigned short address)
{
	
	uint8_t ReadData = 0;
	SPI_CS_Control(LOW);
	SPI_ReadWrite_Blocking(READ_OPCODE);
	SPI_ReadWrite_Blocking(address);
	ReadData = SPI_ReadWrite_Blocking(DUMMY_DATA);
	SPI_CS_Control(HIGH);
	return ReadData;
}