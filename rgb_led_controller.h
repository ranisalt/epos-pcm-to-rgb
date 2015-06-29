#ifndef RGB_LED_CONTROLLER_H
#define RGB_LED_CONTROLLER_H

#include <gpio_pin.h>
#include "led_controller.h"
#include "pcm_thread.h"
#include "tools.h"

__USING_SYS

class RGBLEDController : public LEDController {
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
		PIN_BLUE = 11,
	};

	RGBLEDController() : _pins() {
		_pins[COLOR_RED] = new GPIO_Pin(PIN_RED);
		_pins[COLOR_GREEN] = new GPIO_Pin(PIN_GREEN);
		_pins[COLOR_BLUE] = new GPIO_Pin(PIN_BLUE);

		_threads[COLOR_RED] = new Thread(&pcm_thread, _pins[COLOR_RED], &(currentColor.red));
		_threads[COLOR_RED] = new Thread(&pcm_thread, _pins[COLOR_GREEN], &(currentColor.green));
		_threads[COLOR_RED] = new Thread(&pcm_thread, _pins[COLOR_BLUE], &(currentColor.blue));
		setColor(RGB(0xFF, 0xFF, 0xFF));
	}

	~RGBLEDController() {
		for (char i = 0; i < COLOR_LAST; ++i) {
			_threads[i].join();
			delete _threads[i];
			delete _pins[i];
		}
		/*delete[] _threads;
		delete[] _pins;*/
	}

	void writeColor(RGB color) {
		_pins[COLOR_RED]->put((color.red == 0xFF) ? 1 : 0);
		_pins[COLOR_GREEN]->put((color.green == 0xFF) ? 1 : 0);
		_pins[COLOR_BLUE]->put((color.blue == 0xFF) ? 1 : 0);

		this->currentColor = color;
	}

	void setColor(const RGB& color) {
		this->currentColor = color;
	}

	RGB color() const {
		return this->currentColor;
	}

private:
	GPIO_Pin* _pins[COLOR_LAST];
	Thread* _threads[COLOR_LAST];
};

#endif /* RGB_LED_CONTROLLER_H */
