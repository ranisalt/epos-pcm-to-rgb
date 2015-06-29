#include <nic.h>
#include "rgb_led_controller.h"
#include "tools.h"

__USING_SYS

int sender() {
	NIC nic;
	RGBLEDController led_ctrl;

	while (true) {
		RGB color = getColor();
		led_ctrl.writeColor(color);
	}

	return 0;
}

int main() {
	return sender();
}
