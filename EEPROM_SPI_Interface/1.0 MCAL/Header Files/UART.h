/*
 * UART.h
 * this file for abstracting the details of UART communication protocol in AVR in some functions 
 * Created: 8/25/2020 6:07:43 PM
 *  Author: Khaled Osama Eraky
 */ 


#ifndef UART_H_
#define UART_H_

#include "Microcontroller_config.h"
#include "Macros.h"
#include "StdTypes.h"
#include <util/delay.h>

#define UBRR   F_CPU/16/BuadRate-1

void	UART_init(void);
void	UART_sendByte(uint8_t Data);
uint8_t UART_ReadByte(void);
void    UART_Send_string(char string[]);
//uint8_t *UART_ReadString(uint8_t *string, uint8_t len); 



#endif /* UART_H_ */