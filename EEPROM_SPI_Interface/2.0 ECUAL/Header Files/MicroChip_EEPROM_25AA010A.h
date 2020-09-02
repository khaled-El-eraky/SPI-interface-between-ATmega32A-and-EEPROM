/*
 * MicroChip_EEPROM_25AA010A.h
 *
 * Created: 9/2/2020 2:37:39 AM
 *  Author: Khaled
 */ 


#ifndef MICROCHIP_EEPROM_25AA010A_H_
#define MICROCHIP_EEPROM_25AA010A_H_


void EEPROM_Init(void);
void EEPROM_WriteByte(uint8_t Data , unsigned short address);
uint8_t EEPROM_ReadByte(unsigned short address);



#endif /* MICROCHIP_EEPROM_25AA010A_H_ */