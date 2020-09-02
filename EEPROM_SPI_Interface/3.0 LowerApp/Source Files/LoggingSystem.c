/*
 * LoggingSystem.c
 *
 * Created: 9/2/2020 4:31:59 AM
 *  Author: Khaled
 */ 


#include "Microcontroller_config.h"
#include "MicroChip_EEPROM_25AA010A.h"
#include "UART.h"
#include <util/delay.h>

void DATALogger_Init(void)
{
	UART_init();
	EEPROM_Init();
}

void DATALogger_Start(void)
{
	uint8_t Operation = 0;
	uint8_t Address = 0;
	uint8_t Data = 0;
    UART_Send_string("Please Enter W to Write Data to EEPROM or R to Read Data From EEPROM: ");
	UART_sendByte('\r');
	Operation = UART_ReadByte();
	UART_sendByte('\r');
	switch(Operation)
	{
		case 'W':
		case 'w':
		UART_Send_string("Please Provide Address [0 - 127] Followed By Data[0-255] : ");
		
		
		Address = UART_ReadByte();
		UART_sendByte('-');
		Data	= UART_ReadByte();
		UART_sendByte('\r');
		/* Code to Convert rx String to Number */
		Address = Address - '0';
		Data	-= '0';
		EEPROM_WriteByte(Data,Address);
		UART_Send_string("Write Operation Done :: ");
		UART_sendByte('\r');
		break;
		case 'R':
		case 'r':
		UART_Send_string("Please Provide Address [0 - 127]: ");
		Address = UART_ReadByte();
		UART_sendByte('\r');
		Address = Address - '0';
		Data = EEPROM_ReadByte(Address);
		
		/* Code to Convert Number to ASCII Before Printing */
		Data += '0';
		UART_Send_string("Address has Data of :  ");
		UART_sendByte(Data);
		UART_sendByte('\r');
		break;
		default:
		UART_Send_string("Wrong Input Please Try Again ::");
		UART_sendByte('\r');
		break;
	}
}