#include <uart.h>
#include <utility/ostream.h>

__USING_SYS

class WAV {
public:
	WAV(OStream& cout) : uart()
	{
		char riff[5];
		riff[0] = uart.get();
		riff[1] = uart.get();
		riff[2] = uart.get();
		riff[3] = uart.get();
		riff[4] = 0;
		while (true)
			cout << riff;
	}

private:
	UART uart;
};

int main()
{
	OStream cout;
	WAV wav(cout);

	return 0;
}
