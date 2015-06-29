#ifndef PCM_THREAD_H
#define PCM_THREAD_H

#include <alarm.h>
#include <gpio_pin.h>
#include <thread.h>
#include "rgb_led_controller.h"

__USING_SYS

int pcm_thread(RGBLEDController::PinId pinid) {
	GPIO_Pin pin(pinid);
	while (true) {
		pin.put(1);
	}
	/*while (true) {
		pin->put(1);
		Alarm::delay((*mem) * 16);
		pin->put(0);
		Alarm::delay((0xFF - *mem) * 16);
	}*/

	Thread::exit();
	return 0;
}

#endif /* PCM_THREAD_H */
