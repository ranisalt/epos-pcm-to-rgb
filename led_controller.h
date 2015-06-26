#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

class LEDController {
public:
	virtual void writeColor(int) = 0;

protected:
	int currentColor;
};

#endif /* LED_CONTROLLER_H */
