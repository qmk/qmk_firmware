#include "mbed.h"
#include "test_env.h"

AnalogIn pot1(A0);
AnalogIn pot2(A1);

#define TEST_ITERATIONS     20
#define MEASURE_MIN         0.01

int main(void) {
    MBED_HOSTTEST_TIMEOUT(10);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(AnalogIn potentiometer test);
    MBED_HOSTTEST_START("analog_pot");

    bool result = false;
    float val1, val2;
    
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        val1 = pot1.read();
        val2 = pot2.read();
        
        const char *succes_str = val1 > MEASURE_MIN || val2 > MEASURE_MIN ? "[OK]" : "[FAIL]";
        result = result || (val1 > MEASURE_MIN || val2 > MEASURE_MIN);
        printf("Pot values %f, %f\r\n", val1, val2);
        wait(0.001);
    }
    MBED_HOSTTEST_RESULT(result);
}
