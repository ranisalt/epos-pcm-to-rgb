#ifndef PCM_THREAD_H
#define PCM_THREAD_H

#include <alarm.h>
#include <gpio_pin.h>
#include <thread.h>

__USING_SYS

int pcm_thread(GPIO_Pin* pin, unsigned char* intensity) {
    //double duty_cycle;
    /*while (true) {
        /*duty_cycle = *intensity / 255.0;
        pin->put(1);
        Alarm::delay((int)(1000 * duty_cycle));
        pin->put(0);
        Alarm::delay((int)(9000 * (1 - duty_cycle)));
    }*/
    for (unsigned char i = 0;; ++i) {
        if (i < *intensity) {
            pin->put(1);
        } else {
            pin->put(0);
        }
    }

    Thread::exit();
    return 0;
}

#endif /* PCM_THREAD_H */
