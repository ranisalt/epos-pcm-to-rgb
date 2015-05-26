#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

class LEDController {
public:
	virtual int readColor() const = 0;
	virtual void writeColor(int) = 0;

protected:
	int currentColor;
};

#endif /* LED_CONTROLLER_H */
