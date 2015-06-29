#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "tools.h"

class LEDController {
public:
	virtual void writeColor(RGB) = 0;
	virtual void setColor(const RGB&) = 0;
	virtual RGB color() const = 0;

protected:
	RGB currentColor;
};

#endif /* LED_CONTROLLER_H */
