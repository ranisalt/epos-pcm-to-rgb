#include <periodic_thread.h>
#include <uart.h>
#include "pcm_fft.h"
#include "rgb_led_controller.h"

const int points = 4096;

union byte_int {
	char b[4];
	int i;
};

int readInt(UART& uart)
{
	byte_int bi;
	for (int i = 0; i < 4; ++i) {
		bi.b[i] = uart.get();
	}
	return bi.i;
}

int main()
{
	UART uart;

	int header[11];
	for (int i = 0; i < 11; ++i) {
		header[i] = readInt(uart);
	}

	PCM_FFT fft(points, header);
	RGBLEDController led_ctrl;

	Periodic_Thread pt(PCM_FFT::run, fft, uart, led_ctrl, fft.period(), fft.times());
	pt.join();

	return 0;
}
