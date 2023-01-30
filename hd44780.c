#include "hd44780.h"

uint8_t lcd_busy();

void lcd_cmd_entry_mode(uint8_t id, uint8_t s);
void lcd_cmd_display_control(uint8_t d, uint8_t c, uint8_t b);
void lcd_cmd_function_set(uint8_t dl, uint8_t n, uint8_t f);

void lcd_send_data(uint8_t data);
void lcd_send_cmd(uint8_t cmd);
uint8_t lcd_read();

void lcd_data_dir_out();
void lcd_data_dir_in();

uint8_t lcd_read_part();
void lcd_send_part(uint8_t u4);

void lcd_send_part(uint8_t u4)
{
	if (u4 & 0b1)
		LCD_PORT.OUT |= LCD_D4;
	else
		LCD_PORT.OUT &= ~LCD_D4;

	if (u4 & 0b10)
		LCD_PORT.OUT |= LCD_D5;
	else
		LCD_PORT.OUT &= ~LCD_D5;

	if (u4 & 0b100)
		LCD_PORT.OUT |= LCD_D6;
	else
		LCD_PORT.OUT &= ~LCD_D6;

	if (u4 & 0b1000)
		LCD_PORT.OUT |= LCD_D7;
	else
		LCD_PORT.OUT &= ~LCD_D7;
}

uint8_t lcd_read_part()
{
	uint8_t data = LCD_PORT.IN;
	uint8_t result = 0;
	if (data & LCD_D4)
		result |= 0b1;

	if (data & LCD_D5)
		result |= 0b10;

	if (data & LCD_D6)
		result |= 0b100;

	if (data & LCD_D7)
		result |= 0b1000;

	return result;
}

void lcd_data_dir_in()
{
	LCD_PORT.DIR &= ~(LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7);
}

void lcd_data_dir_out()
{
	LCD_PORT.DIR |= LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
}

uint8_t lcd_read()
{
	lcd_data_dir_in();

	LCD_RS_LOW;
	LCD_RW_HIGH;
	LCD_E_HIGH;
	uint8_t data = lcd_read_part() << 4;
	LCD_E_LOW;
	LCD_E_HIGH;
	data = data | lcd_read_part();
	LCD_E_LOW;

	return data;
}

uint8_t lcd_busy()
{
	return lcd_read() & 0x80;
}

void lcd_send_cmd(uint8_t cmd)
{
	lcd_data_dir_out();
	LCD_E_HIGH;

	LCD_RS_LOW;
	LCD_RW_LOW;

	lcd_send_part(cmd >> 4);
	LCD_E_LOW;
	LCD_E_HIGH;
	lcd_send_part(cmd);

	LCD_E_LOW;

	while (lcd_busy())
		;
}

void lcd_send_data(uint8_t data)
{
	lcd_data_dir_out();
	LCD_E_HIGH;

	LCD_RS_HIGH;
	LCD_RW_LOW;

	lcd_send_part(data >> 4);
	LCD_E_LOW;
	LCD_E_HIGH;
	lcd_send_part(data);

	LCD_E_LOW;

	while (lcd_busy())
		;
}

void lcd_putc(char chr)
{
	lcd_send_data((uint8_t)chr);
}

void lcd_puts(char *str)
{
	char c;

	while ((c = *(str++)))
		lcd_putc(c);
}

void lcd_cmd_function_set(uint8_t dl, uint8_t n, uint8_t f)
{
	lcd_send_cmd(LCD_CMD_SET_FUNCTION | (dl << LCD_DL) | (n << LCD_N) | (f << LCD_F));
}

void lcd_cmd_display_control(uint8_t d, uint8_t c, uint8_t b)
{
	lcd_send_cmd(LCD_CMD_DISPLAY_CONTROL | (d << LCD_D) | (c << LCD_C) | (b << LCD_B));
}

void lcd_cmd_entry_mode(uint8_t id, uint8_t s)
{
	lcd_send_cmd(LCD_CMD_ENTRY_MODE | (id << LCD_ID) | (s << LCD_S));
}

void lcd_clear()
{
	lcd_send_cmd(LCD_CMD_CLEAR);
}

void lcd_set(uint8_t x, uint8_t y)
{
	y = y * 0x40;
	lcd_send_cmd(LCD_CMD_SET_DD_ADDRESS + x + y);
}

void lcd_init()
{
	LCD_PORT.DIR |= LCD_RS | LCD_RW | LCD_E;
	lcd_data_dir_out();

	LCD_PORT.OUT |= LCD_E;
	LCD_PORT.OUT &= ~LCD_RS;
	LCD_PORT.OUT &= ~LCD_RW;
	lcd_send_part(0b0010);
	LCD_PORT.OUT &= ~LCD_E;

	_delay_ms(5);

	lcd_cmd_function_set(LCD_DL_4BIT, LCD_N_2LINE, LCD_F_5x8DOTS);
	lcd_cmd_display_control(LCD_D_ON, LCD_C_OFF, LCD_B_OFF);
	lcd_cmd_entry_mode(LCD_ID_INC, LCD_S_SHIFT_OFF);
}