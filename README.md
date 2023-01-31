# AVR_hd44780

## Library written in C for AVR to handle hd44780 2x16 display.
(Tested on ATmega4809)

# Functions
    void lcd_init();
Init lcd
---
    void lcd_puts(char *str);
    void lcd_puts_P(const char *str);
Puts string on cursor position. Cursor position can be changed by lcd_set()
---
    void lcd_putc(char chr);
Puts single char to lcd
---
    void lcd_def_char(uint8_t index, uint8_t *data);
    void lcd_def_char_P(uint8_t index, const uint8_t *data);
Define custom character. HD44780 accept 8 user defined symbols.
---
	void lcd_set(uint8_t x, uint8_t y);
Set cursor position. (where to print next char)
---
	void lcd_clear();
Clears entire screen