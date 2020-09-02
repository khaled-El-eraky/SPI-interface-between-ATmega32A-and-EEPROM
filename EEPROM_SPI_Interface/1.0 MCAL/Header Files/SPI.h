/*
 * SPI.h
 * This file is for handling the communication of ATmega32A through SPI communication protocol
 * by 3 functions 
 *
 * SPI_Init >> this function is for intializing the SPI by setting all SPI configuartions 
 *          >> return void 
 *          >> parameters void
 *
 *
 * 
 *
 * Created: 9/1/2020 3:29:32 PM
 *  Author: Khaled
 */ 


#include "Microcontroller_config.h"
#include "Macros.h"
#include "StdTypes.h"


#ifndef SPI_H_
#define SPI_H_


	typedef enum
	{
		SPI_Disable,
		SPI_Enable,
	}SPI_Control;

	typedef enum
	{
		SPI_InterruptDisable,
		SPI_InterruptEnable,
	}SPI_InterruptState;
	
	typedef enum
	{
		SPI_MSB,
		SPI_LSB,
	}SPI_DataOrder;
	
	typedef enum
	{
		SPI_SLAVE,
		SPI_MASTER,
	}SPI_Mode;
	
	
	typedef enum
	{
		SPI_CLKMode0,
		SPI_CLKMode1,
		SPI_CLKMode2,
		SPI_CLKMode3,
	}SPI_ClockModes;
	
	typedef enum
	{
		SPI_FCPU_BY_2,
		SPI_FCPU_BY_4,
		SPI_FCPU_BY_8,
		SPI_FCPU_BY_16,
		SPI_FCPU_BY_32,
		SPI_FCPU_BY_64,
		SPI_FCPU_BY_128,
	}SPI_Freq;

	typedef enum
	{
		SPI_NoError,
		SPI_WriteCollison,
	}SPI_ErrorState;
	
	typedef struct
	{
		SPI_Control			Control;
		SPI_Mode			Mode;
		SPI_ClockModes		ClockMode;
		SPI_DataOrder		DataOrder;
		SPI_InterruptState	InterruptState;
		void (*SPI_InterruptCall) (void);
		
		/* For Slave Mode -- Freq Should not be Selected */
		SPI_Freq			Freq;
		
		/* This Bit dose not clear it Self, Check it and erase The Error By assigning it to SPI_NoError */
		SPI_ErrorState			Error;
	}SPI_ConfigStruct;
	
	
	extern SPI_ConfigStruct SPI0;
	
	void SPI_Init(void);
	uint8_t SPI_ReadWrite_Blocking(uint8_t Data);
	uint8_t SPI_ReadWrite_NonBlocking(uint8_t Data);


#endif /* SPI_H_ */