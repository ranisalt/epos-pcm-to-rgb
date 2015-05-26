#include "rgb_led_controller.h"

int main() {
	RGBLEDController led_ctrl;

	led_ctrl.writeColor(0xFF00FFFF); // purple, full luminosity

	led_ctrl.writeColor(0x00FF8080); // aqua, half-luminosity

	return 0;
}
