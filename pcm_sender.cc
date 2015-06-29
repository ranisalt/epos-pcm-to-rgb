#include <nic.h>
#include <utility/ostream.h>
#include "rgb_led_controller.h"
#include "tools.h"

__USING_SYS

int sender() {
	NIC nic;
	OStream cout;
	RGBLEDController led_ctrl;

	while (true) {
		RGB color = getColor();
		led_ctrl.setColor(color);
		cout << "Color " << color.red
			<< ' ' << color.green
			<< ' ' << color.blue << '\n';
	}

	return 0;
}

int main() {
	return sender();
}
