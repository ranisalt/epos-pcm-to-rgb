#ifndef PCM_THREAD_H
#define PCM_THREAD_H

#include <gpio_pin.h>
#include <thread.h>
#include "tools.h"

__USING_SYS

int pwm_thread(RGB* color) {
	GPIO_Pin red_led(10), green_led(9), blue_led(11);

    for (unsigned char i = 0;; ++i) {
		red_led.put(i < color->red);
		green_led.put(i < color->green);
		blue_led.put(i < color->blue);
    }

    Thread::exit();
    return 0;
}

#endif /* PCM_THREAD_H */
