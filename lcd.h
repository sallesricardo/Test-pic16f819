/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

#include <xc.h> // include processor files - each processor file is guarded.  

typedef union {
    struct {
        uint8_t lcd_data :4;
        uint8_t rs :1;      // D
        uint8_t en :1;      // C
        uint8_t led2 :1;    // B
        uint8_t led1 :1;    // A
    };
    struct {
        uint8_t d:4;
    };
    struct {
        uint8_t d7 :1;
        uint8_t d6 :1;
        uint8_t d5 :1;
        uint8_t d4 :1;
    };
    uint8_t data;
} data_t;

data_t data;

//const uint8_t custom_char[8][8] = {
//    { // 
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00011111
//    },
//    { // 
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00011111,
//        0b00011111
//    },
//    { // 
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00011111,
//        0b00011111,
//        0b00011111
//    },
//    { // 
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111
//    },
//    { // 
//        0b00000000,
//        0b00000000,
//        0b00000000,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111
//    },
//    { // 
//        0b00000000,
//        0b00000000,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111
//    },
//    { // 
//        0b00000000,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111
//    },
//    { // 
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111,
//        0b00011111
//    }
//};

#define RS data.rs
#define EN data.en
#define D4 data.d4
#define D5 data.d5
#define D6 data.d6
#define D7 data.d7
#define LCD_DATA data.lcd_data
#define LED data.led1
#define BACK_LIGHT data.led2


void init_LCD(void);
void int8tostr(int8_t value, char *str);
void lcd_cmd(char);
void lcd_send_char(char);
void toggle_led(void);
void lcd_send_string(char *str, uint8_t len, uint8_t line);
void set_back_light(uint8_t value);
void set_lcd_contrast(uint16_t value);

#endif	/* LCD_H */
