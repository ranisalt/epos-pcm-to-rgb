#include <nic.h>
#include <thread.h>
#include "pwm_thread.h"
#include "tools.h"

__USING_SYS

const unsigned char PROTOCOL_ID = 56;

int worker_thread(RGB* color) {
	NIC nic;

#if defined(SENDER)
	NIC::Address src(0x01);
	NIC::Protocol prot(56);

	for (unsigned char i = 0;; ++i) {
		(*color) = getColor();
		nic.send(src, prot, color, sizeof(RGB));
	}
#elif defined(RECEIVER)
    NIC::Address src;
    NIC::Protocol prot;

	for (unsigned char i = 0;; ++i) {
        nic.receive(&src, &prot, color, sizeof(RGB));
		nic.send(src, PROTOCOL_ID, color, sizeof(RGB));
	}
#endif

	Thread::exit();
	return 0;
}

int main() {
	{
		GPIO_Pin red_led(23);
		red_led.put(0);
	}

	RGB color;
	Thread pwm(&pwm_thread, &color);
	Thread worker(&worker_thread, &color);
	pwm.join();
	worker.join();

	return 0;
}

