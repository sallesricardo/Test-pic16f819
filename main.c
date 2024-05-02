/*
 * File:   main.c
 * Author: ricardo
 *
 * Created on 28 de Fevereiro de 2024, 14:04
 */


#include <xc.h>
#include <stdint.h>
#include "main.h"
#include "lcd.h"

#define _XTAL_FREQ 8000000
uint16_t count = 0;
char text[16] = "Display    ";
uint8_t bcd[6] = { 0, 0, 0, 0, 0, 0 };

void init_cpu(void){
    CLRWDT();
    OSCCONbits.IRCF = 7;
    while (!OSCCONbits.IOFS) NOP();
    CLRWDT();
}

void init_timer0(void){
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 2;
    OPTION_REGbits.T0CS = 0;
    TMR0 = TIMER0_RELOAD;
    INTCONbits.TMR0IE = 1;
}

void inc_bcd_counter(void){
    #define Array(a, i)  ((unsigned)(((a) >> (60 - 4 * (i))) & 0xf))
    for (int8_t i = 5; i >= 0; i--){
        bcd[i]++;
        if (bcd[i] >= 10){
            bcd[i] = 0;
        } else {
            break;
        }
    }
}

void __interrupt() ISR(void){
    static uint16_t scount = 0;
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        TMR0 = TIMER0_RELOAD;
        ticks++;
        count++;
        scount++;
        if(scount >= 1000){
            inc_bcd_counter();
            seconds++;
            scount = 0;
        }
    }
}

void main(void) {
    init_cpu();
    init_timer0();
    PORTBbits.RB1 = 0;
    TRISBbits.TRISB1 = 0;
    ADCON1bits.PCFG = 0xE;
    init_LCD();
    uint16_t count2 = 0;
    uint8_t dir = 0;
    INTCONbits.GIE = 1;
    set_back_light(1);
    set_lcd_contrast(40);
    CLRWDT();
    lcd_send_string("Teste Teste     ",16,1);
    CLRWDT();
    while (1) {
        CLRWDT();
        PORTBbits.RB1 = !PORTBbits.RB1;
        if (count >= 500){
            CLRWDT();
            toggle_led();
            count = 0;
            for (uint8_t i = 0; i < 6; i++){
                text[10 + i] = bcd[i] + '0';
            }
            lcd_send_string(text,16,2);
        }
        if ((ticks & 0x00ff) == 0x1a){
            if (dir){
                count2--;
                if (count2 == 0){
                    dir = 0;
                }
            } else {
                count2++;
                if (count2 >= 511){
                    dir = 1;
                }
            }
        }
        // set_lcd_contrast(count2);
    }
    return;
}
