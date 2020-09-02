/*
 * UART.c
 *
 * Created: 8/25/2020 6:08:04 PM
 *  Author: Khaled
 */ 

#include "UART.h"



void	UART_init(void)
{
	UBRRL = (uint8_t)(UBRR);             /*set the Baudrate in the UBRRL and UBRRH registers */
	UBRRH = (uint8_t)((UBRR)>>8);
	SETBIT(UCSRB,RXEN);					 /*Rx Enable*/    
	SETBIT(UCSRB,TXEN);					 /*Tx Enable*/
	SETBIT(UCSRC,URSEL);                 /*select UCSRC register*/
	SETBIT(UCSRC,UCSZ0);                 /*set the date bit size with 8 bit*/
	SETBIT(UCSRC,UCSZ1);           
}

void UART_sendByte(uint8_t Data)
{
	while((UCSRA & (1<<UDRE)) == 0)     
	{
		
	}
	UDR =(uint8_t) Data;
}

uint8_t UART_ReadByte(void)
{
	while((UCSRA & (1<<RXC)) == 0)
	{
	}
	return UDR;
}
void UART_Send_string(char string[])
{
	int i=0;
	while ( string[i] > 0)
	UART_sendByte(string[i++]);
}

//char UART_ReadString(uint8_t*RecivedPack)
//{
	//uint8_t i =0;
	//while(i<36)
	//{
		//RecivedPacket[i]= UART_ReadByte();
		//
		//i++;
	//}
	
 //uint8_t *UART_ReadString(uint8_t *string, uint8_t len) 
 //{
	//uint8_t *ptr = string;								  /* copy the buffer pointer*/
	//do 
	//{
		//*string = UART_ReadByte();						 /* get a new character*/
		//if (( *string == '\r') || (*string == '\n'))     /* end of text*/
		//{
			//break; 
		//}
		//string++;
		//len--;
	//} 
	//while (len>1); 
//
	//*string = '\0'; // null terminate the string
	//return ptr; // return buffer pointer
//}