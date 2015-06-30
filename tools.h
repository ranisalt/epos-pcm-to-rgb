#ifndef TOOLS_H
#define TOOLS_H

#include <uart.h>

__USING_SYS

struct RGB {
	unsigned char red, green, blue;

	RGB() : red(0), green(0), blue(0) {}
	RGB(unsigned char red, unsigned char green, unsigned char blue)
		: red(red), green(green), blue(blue) {}
};

RGB getColor() {
	UART uart;
	RGB ret(
		uart.get(),
		uart.get(),
		uart.get()
	);

	return ret;
}

#endif /* TOOLS_H */
