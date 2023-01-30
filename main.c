#include <avr/io.h>
#include <util/delay.h>

#include <avr/interrupt.h>

#include "hd44780.h"

int main()
{
	_delay_ms(5000);
	lcd_init();
	lcd_clear();

	char *m = "PepaToPepito";
	lcd_puts(m);

	while (1)
	{
	}

	return 0;
}
