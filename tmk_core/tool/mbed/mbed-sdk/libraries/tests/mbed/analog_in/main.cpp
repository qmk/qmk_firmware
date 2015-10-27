/*
 * Version of the Analog test,
 * Intended for use by devices which
 * don't have analog out.
 *
 * Connect 'control' to pin 21 of an mbed LPC1768
 * Connect 'analogInput' to pin 18 of an mbed LPC1768
 * Connect 'TX/RX' to pins 27 and 28 of an mbed LPC1768
 *
 * Upload:
*/
#include "test_env.h"

#define ERROR_TOLERANCE 0.05

#if defined(TARGET_LPC1114)

AnalogIn analogInput(dp4);
DigitalOut control(dp5);
DigitalOut indicator(LED1);

#else

#endif

uint8_t successes = 0;

int main() {
	control = 0;

	for (int i = 0; i < 10; i++) {
		// Read value,
		float expectedValue = i * 0.1;
		float value = analogInput.read();

		if (value > expectedValue + ERROR_TOLERANCE || value < expectedValue - ERROR_TOLERANCE) {
			// Failure.
			printf("ERROR (out:%.4f) - (in:%.4f) = (%.4f)"NL, expectedValue, value, fabs(expectedValue - value));
		}
		else {
			printf("OK    (out:%.4f) - (in:%.4f) = (%.4f)"NL, out_value, in_value, diff);
			successes++;
		}

		control = 1;
		indicator = 1;
		wait(0.1);
		control = 0;
		indicator = 0;
	}

	if (successes > 8) {
		notify_success(true);
	}
	else {
		notify_success(false);
	}
}