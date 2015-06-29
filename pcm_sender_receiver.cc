#include <nic.h>
#include <thread.h>
#include "pcm_thread.h"
#include "rgb_led_controller.h"
#include "tools.h"

__USING_SYS

const NIC::Address src(0x01);
const unsigned char PROTOCOL_ID = 56;

int sender() {
	NIC nic;
	RGBLEDController led_ctrl;

	GPIO_Pin red_led(23);
	red_led.put(0);

        Thread* t = new Thread(&pcm_thread);

	/*while (true) {
		RGB color = getColor();
    		led_ctrl.writeColor(color);
                nic.send(src, PROTOCOL_ID, &color, sizeof(color));
        }*/

        t->join();

	return 0;
}

int receiver() {
    
    NIC::Address src;
    NIC::Protocol prot;
    NIC nic;
    RGBLEDController led_ctrl;
    RGB color;
    GPIO_Pin red_led(23);
    red_led.put(0);

    while(true) {
        nic.receive(&src, &prot, (unsigned char*)&color, sizeof(color));
        led_ctrl.writeColor(color);
        nic.send(src, PROTOCOL_ID, &color, sizeof(color));
    }

    return 0;
}

int main() {
#ifdef SENDER
    return sender();
#else
    return receiver();
#endif
}
