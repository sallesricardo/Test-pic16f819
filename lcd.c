/*
 * File:   lcd.c
 * Author: ricardo
 *
 * Created on 23 de Outubro de 2022, 11:34
 */

#define _XTAL_FREQ 8000000

#define TRUE 1
#define FALSE 0
#define OUTPUT 0
#define INPUT 1

#include <xc.h>
#include "74HC595.h"
#include "lcd.h"

void send_e(uint8_t state){
    EN = state;
    send_byte(data.data);
}

void send_rs(uint8_t state){
    RS = state;
    send_byte(data.data);
}

void send_data(){
    send_byte(data.data);
}

void lcd_cmd(char value) {
    LCD_DATA = (value >> 4) & 0x0F;
    send_data();
    send_e(TRUE);
    __delaywdt_us(1);
    send_e(FALSE);
    __delaywdt_us(5);
    
    LCD_DATA = value & 0x0F;
    send_data();
    send_e(TRUE);
    __delaywdt_us(1);
    send_e(FALSE);
    __delaywdt_us(5);
}

//void lcd_send_char(char value){
//    send_rs(TRUE);
//    lcd_cmd(value);
//    send_rs(FALSE);
//    send_data();
//}

void lcd_send_string(char *str, uint8_t len, uint8_t line){
    lcd_cmd(1 == line ? 0x80 : 0xC0);
    send_rs(TRUE);
    for(uint8_t i = 0; i < len; i++){
        lcd_cmd(str[i]);
    }
    send_rs(FALSE);
}

//void lcd_load_custom_chars(){
//    lcd_cmd(0x40);
//    send_rs(TRUE);
//    for(uint8_t i = 0; i < 8; i++){
//        for(uint8_t b = 0; b < 8; b++){
//            lcd_cmd(custom_char[i][b]);
//        }
//    }
//    send_rs(FALSE);
//}

void _lcd_init_cmd(uint8_t cmd){
    LCD_DATA = cmd;
    send_data();
    send_e(TRUE);
    __delaywdt_us(1);
    send_e(FALSE);
    __delaywdt_ms(1);
}

void _init_lcd_contrast_pwm(void){
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 0;
    T2CONbits.TOUTPS = 0;
    T2CONbits.T2CKPS = 0;
    PR2 = 0x7a;     // 0x5a -> 20kHz / 0x7a -> ~17kHz PWM duty (0->511)
    CCP1CONbits.CCP1X = 0;
    CCP1CONbits.CCP1Y = 0;
    CCPR1L = 0;
    TRISBbits.TRISB2 = 0;
    T2CONbits.TMR2ON = 1;
    CCP1CONbits.CCP1M = 0xF;
}

void init_LCD(void){
    _init_lcd_contrast_pwm();
    init_595();
    data.data = 0;
    __delaywdt_ms(50);
    
    _lcd_init_cmd(0x03);
    __delaywdt_ms(4);

    _lcd_init_cmd(0x03);
    __delaywdt_ms(10);

    _lcd_init_cmd(0x03);
    
    _lcd_init_cmd(0x02);
    __delaywdt_ms(4);

    lcd_cmd(0x28);
    __delaywdt_us(40);
    lcd_cmd(0x08);
    __delaywdt_us(40);
    lcd_cmd(0x0C);
    __delaywdt_us(2);
    lcd_cmd(0x06);
    __delaywdt_us(40);
    //lcd_load_custom_chars();
}

void toggle_led(void){
    LED = !LED;
    send_data();
}

void set_back_light(uint8_t value){
    BACK_LIGHT = value;
    send_data();
}

void set_lcd_contrast(uint16_t value){
    CCP1CONbits.CCP1X = value & 0x01;
    CCP1CONbits.CCP1Y = value & 0x02;
    CCPR1L = (value >> 2) & 0xFF;
}