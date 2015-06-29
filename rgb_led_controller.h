#ifndef RGB_LED_CONTROLLER_H
#define RGB_LED_CONTROLLER_H

#include <gpio_pin.h>
#include "led_controller.h"
//#include "pcm_thread.h"
#include "tools.h"

__USING_SYS

class RGBLEDController : public LEDController {
public:
	enum COLORS {
		COLOR_RED,
		COLOR_GREEN,
		COLOR_BLUE,

		COLOR_LAST // for loop
	} PinColor;

	enum PINS {
		PIN_RED = 10,
		PIN_GREEN = 9,
		PIN_BLUE = 11,
	} PinId;

	RGBLEDController() : _pins() {
		_pins[COLOR_RED] = new GPIO_Pin(PIN_RED);
		_pins[COLOR_GREEN] = new GPIO_Pin(PIN_GREEN);
		_pins[COLOR_BLUE] = new GPIO_Pin(PIN_BLUE);

		/*_threads[COLOR_RED] = new Thread(&pcm_thread, PIN_RED);
		_threads[COLOR_GREEN] = new Thread(&pcm_thread, PIN_GREEN);
		_threads[COLOR_BLUE] = new Thread(&pcm_thread, PIN_BLUE);*/
		setColor(RGB(0xFF, 0xFF, 0xFF));
	}

	~RGBLEDController() {
		for (int i = 0; i < COLOR_LAST; ++i) {
			/*_threads[i]->join();
			delete _threads[i];*/
			delete _pins[i];
		}
		/*delete[] _threads;
		delete[] _pins;*/
	}

	void writeColor(RGB color) {
		_pins[COLOR_RED]->put((color.red > 0xC0) ? 1 : 0);
		_pins[COLOR_GREEN]->put((color.green > 0xC0) ? 1 : 0);
		_pins[COLOR_BLUE]->put((color.blue > 0xC0) ? 1 : 0);

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
