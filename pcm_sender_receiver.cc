#include <nic.h>
#include <thread.h>
#include "pcm_thread.h"
#include "rgb_led_controller.h"
#include "tools.h"

__USING_SYS

const NIC::Address src(0x01);
const unsigned char PROTOCOL_ID = 56;

int sender_thread(RGB* color) {
	while (true) {
		(*color) = getColor();
                Thread::yield();
    		//led_ctrl.setColor(color);
                //nic.send(src, PROTOCOL_ID, &color, sizeof(color));
        }
}

int sender() {
	//NIC nic;
	//RGBLEDController led_ctrl;
        RGB color(20, 100, 255);

        //unsigned char a = 20, b = 100, c = 255;
	GPIO_Pin* red_led = new GPIO_Pin(10);
	GPIO_Pin* green_led = new GPIO_Pin(9);
	GPIO_Pin* blue_led = new GPIO_Pin(11);
	//red_led.put(0);

        Thread* t = new Thread(&pcm_thread, red_led, &color.red);
        Thread* u = new Thread(&pcm_thread, green_led, &color.green);
        Thread* v = new Thread(&pcm_thread, blue_led, &color.blue);
        //t->join();
        //u->join();
        //v->join();*/
        //Thread* w = new Thread(&sender_thread, &color);
	/*while (true) {
		//color = getColor();
    		//led_ctrl.setColor(color);
                //nic.send(src, PROTOCOL_ID, &color, sizeof(color));
        }*/

        //t->join();

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
    //Thread* s = new Thread(&sender);
    sender();
    return 0;
#else
    return receiver();
#endif
}
