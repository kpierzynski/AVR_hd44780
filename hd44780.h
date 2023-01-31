#ifndef __HD44780_H_
#define __HD44780_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "hd44780_mem.h"

#define LCD_PORT PORTA

// Register (Instruction or Data) Select
// High -> Data, Low -> Instruction
#define LCD_RS PIN6_bm
// Read (1) / Write (0)
#define LCD_RW PIN5_bm
#define LCD_E PIN4_bm

#define LCD_D4 PIN3_bm
#define LCD_D5 PIN2_bm
#define LCD_D6 PIN1_bm
#define LCD_D7 PIN0_bm

#define LCD_RS_LOW LCD_PORT.OUT &= ~LCD_RS
#define LCD_RS_HIGH LCD_PORT.OUT |= LCD_RS

#define LCD_RW_LOW LCD_PORT.OUT &= ~LCD_RW
#define LCD_RW_HIGH LCD_PORT.OUT |= LCD_RW

#define LCD_E_LOW LCD_PORT.OUT &= ~LCD_E
#define LCD_E_HIGH LCD_PORT.OUT |= LCD_E

void lcd_init();

void lcd_puts(char *str);
void lcd_puts_P(const char *str);
void lcd_putc(char chr);

void lcd_def_char(uint8_t index, uint8_t *data);
void lcd_def_char_P(uint8_t index, const uint8_t *data);

void lcd_set(uint8_t x, uint8_t y);
void lcd_clear();

#endif