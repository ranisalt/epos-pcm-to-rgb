#include <periodic_thread.h>
#include <uart.h>
#include "fft.h"
#include "rgb_led_controller.h"

const int points = 2048;
static RGBLEDController led_ctrl = RGBLEDController();
static UART* uart = new UART();

short readInt16LE(UART* uart)
{
	short a = uart->get(), b = uart->get();
	return b << 8 | a;
}

int apply_fft()
{
	while (true) {
		double data[points * 2 + 1];
		for (int i = 0; i < points * 2;) {
			data[++i] = static_cast<double>(readInt16LE(uart));
			data[++i] = 0;
		}

		fft::four1(data, points, 1);

		int color;
		// map complex to color
		led_ctrl.writeColor(color);

		Periodic_Thread::wait_next();
	}

	return 0;
}

int main()
{
	UART uart;
	RGBLEDController led_ctrl;

	Periodic_Thread pt(apply_fft, 44100 / points);
	pt.join();

	return 0;
}
