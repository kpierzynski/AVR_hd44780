#ifndef __HD44780_MEM_H_
#define __HD44780_MEM_H_

#define LCD_CMD_SET_FUNCTION 0b00100000
#define LCD_DL 4
#define LCD_DL_8BIT 1
#define LCD_DL_4BIT 0

#define LCD_N 3
#define LCD_N_2LINE 1
#define LCD_N_1LINE 0

#define LCD_F 2
#define LCD_F_5x10DOTS 1
#define LCD_F_5x8DOTS 0

#define LCD_CMD_DISPLAY_CONTROL 0b00001000
#define LCD_D 2
#define LCD_D_ON 1
#define LCD_D_OFF 0

#define LCD_C 1
#define LCD_C_ON 1
#define LCD_C_OFF 0

#define LCD_B 0
#define LCD_B_ON 1
#define LCD_B_OFF 0

#define LCD_CMD_ENTRY_MODE 0b00000100
#define LCD_ID 1
#define LCD_ID_INC 1
#define LCD_ID_DEC 0

#define LCD_S 0
#define LCD_S_SHIFT_ON 1
#define LCD_S_SHIFT_OFF 0

#define LCD_CMD_CLEAR 0b00000001

#define LCD_CMD_SET_DD_ADDRESS 0b10000000

#define LCD_SET_CGRAM 0b01000000

#endif