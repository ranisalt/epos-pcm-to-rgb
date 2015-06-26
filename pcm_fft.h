#ifndef PCM_FFT_H
#define PCM_FFT_H

#include <alarm.h>
#include <uart.h>
#include "led_controller.h"

class PCM_FFT {
	union byte_short {
		char b[2];
		short s;
	};

public:
	// points = samples per calculation
	// header = 44 byte info
	// bytes 22 and 23 = channels
	// bytes 24-27 = sample rate
	// bytes 40-43 = data length (total samples)
	PCM_FFT(int points, int* header) :
		points(points),
		channels(header[5] & 0xFF),
		sample_rate(header[6]),
		length(header[10]),
		values(new short[points])
	{ }

	unsigned int period() const
	{
		// period in microseconds
		double period = (1.0 / static_cast<double>(sample_rate)) * 1000000.0;
		return static_cast<unsigned int>(period * static_cast<double>(points));
	}

	int times() const
	{
		// this ignores the last bytes that are past the last points multiple
		// no problem since this will be less than 1/10 of a second
		return static_cast<int>(length / points);
	}

	template<typename UART, typename LEDController>
	static int run(PCM_FFT fft, UART uart, LEDController ctrl)
	{
		for (unsigned int i = 0; i < fft.points; ++i) {
			byte_short bs;
			bs.b[0] = uart.get();
			bs.b[1] = uart.get();

			fft.values[i] = bs.s;
		}

		// TODO: FFT

		ctrl.writeColor(0);

		return 0;
	}

private:
	const unsigned int points;
	unsigned short channels;
	unsigned int sample_rate;
	unsigned int length;
	short* values;
};

#endif /* PCM_FFT_H */
