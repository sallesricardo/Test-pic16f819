/*
 * File:   eeprom.c
 * Author: ricardo
 *
 * Created on 3 de Março de 2024, 22:23
 */


#include <xc.h>

uint8_t read_eeprom(uint8_t address){
    CLRWDT();
    EEADR = address;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 0;
    return EEDATA;
}

uint8_t write_eeprom(uint8_t address, uint8_t data){
    CLRWDT();
    EEADR = address;
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.WREN = 1;
    CLRWDT();
    uint8_t _interrupt = INTCONbits.GIE;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = _interrupt;
    EECON1bits.WREN = 0;
    CLRWDT();
}