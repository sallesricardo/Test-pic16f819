/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef EEPROM_H
#define	EEPROM_H

#include <xc.h> // include processor files - each processor file is guarded.  

uint8_t read_eeprom(uint8_t address);
uint8_t write_eeprom(uint8_t address, uint8_t data);

#endif	/* EEPROM_H */

