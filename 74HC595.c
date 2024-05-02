/*
 * File:   74HC595.c
 * Author: ricardo
 *
 * Created on 2 de Março de 2024, 20:17
 */


#include <xc.h>

#include "74HC595.h"

void init_595(){
    OE = 1;
    RCLK = 0;
    SRCLR = 0;
    SRCLK = 0;
    SER = 0;
    TRIS_OE = 0; // OE
    TRIS_RCLK = 0; // RCLK
    TRIS_SRCLR = 0; // SRCLR
    TRIS_SRCLK = 0; // SRCLK
    TRIS_SER = 0; // SER
    RCLK = 1;
    RCLK = 0;
    SRCLR = 1;
    OE = 0;
}

void _send_bit (uint8_t value) {
    SER = value & 0x01;
    SRCLK = 1;
    SRCLK = 0;
}

void send_byte (uint8_t value){
    for(int i = 0; i < 8; i++){
        _send_bit(value >> i);
    }
    RCLK = 1;
    RCLK = 0;
}