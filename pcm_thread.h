#ifndef PCM_THREAD_H
#define PCM_THREAD_H

#include <alarm.h>
#include <gpio_pin.h>

__USING_SYS

int pcm_thread(GPIO_Pin* pin, unsigned char* mem) {
	while (true) {
		pin->put(1);
		Alarm::delay((*mem) * 16);
		pin->put(0);
		Alarm::delay((0xFF - *mem) * 16);
	}
	return 0;
}

#endif /* PCM_THREAD_H */
