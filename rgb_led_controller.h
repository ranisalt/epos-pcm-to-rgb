#ifndef RGB_LED_CONTROLLER_H
#define RGB_LED_CONTROLLER_H

#include <gpio_pin.h>
#include "led_controller.h"

__USING_SYS

class RGBLEDController : public LEDController {
	union byte_int {
		int i;
		char b[4];
	};

public:
	enum COLORS {
		COLOR_RED,
		COLOR_GREEN,
		COLOR_BLUE,

		COLOR_LAST // for loop
	};

	enum PINS {
		PIN_RED = 10,
		PIN_GREEN = 9,
		PIN_BLUE = 11
	};

	RGBLEDController() : _pins(new GPIO_Pin[COLOR_LAST]) {
		_pins[COLOR_RED] = GPIO_Pin(PIN_RED);
		_pins[COLOR_GREEN] = GPIO_Pin(PIN_GREEN);
		_pins[COLOR_BLUE] = GPIO_Pin(PIN_BLUE);

		writeColor(0xFF000000);
	}

	void writeColor(int color) {
		byte_int bi;
		bi.i = color;

		for (int i = 0; i < COLOR_LAST; ++i) {
			_pins[i].put(bi.b[i] > 0);
		}

		this->currentColor = color & 0xFFFFFF00;
	}

private:
	GPIO_Pin* _pins;
};

#endif /* RGB_LED_CONTROLLER_H */
