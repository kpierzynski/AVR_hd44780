#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "hd44780.h"

const uint8_t battery_0[8] PROGMEM = {14, 31, 17, 17, 17, 17, 19, 31};

int main()
{
	_delay_ms(5000);
	lcd_init();

	uint8_t battery_1[8] = {14, 31, 17, 17, 17, 19, 23, 31};
	uint8_t battery_2[8] = {14, 31, 17, 19, 23, 31, 31, 31};
	uint8_t battery_3[8] = {14, 31, 23, 31, 31, 31, 31, 31};

	uint8_t heart_hollow[8] = {32, 10, 21, 17, 10, 4, 32, 32};
	uint8_t heart_full[8] = {32, 10, 31, 31, 14, 4, 32, 32};

	lcd_def_char_P(0, battery_0);
	lcd_def_char(1, battery_1);
	lcd_def_char(2, battery_2);
	lcd_def_char(3, battery_3);
	lcd_def_char(4, heart_hollow);
	lcd_def_char(5, heart_full);
	lcd_clear();

	lcd_set(3, 1);
	lcd_puts("2nd ");
	lcd_puts_P(PSTR("line"));

	uint8_t i = 0;
	uint8_t tick = 0;

	while (1)
	{
		lcd_set(0, 0);
		lcd_putc(i);

		i++;

		if (i > 3)
			i = 0;

		if (tick)
		{
			lcd_set(15, 1);
			lcd_putc(4);
		}
		else
		{
			lcd_set(15, 1);
			lcd_putc(5);
		}

		tick ^= 1;
		_delay_ms(1000);
	}

	return 0;
}
