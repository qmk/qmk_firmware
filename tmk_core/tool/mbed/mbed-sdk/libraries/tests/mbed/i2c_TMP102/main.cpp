#include "test_env.h"
#include "TMP102.h"

#if defined(TARGET_KL25Z)
TMP102 temperature(PTC9, PTC8, 0x90);

#elif defined(TARGET_LPC812)
TMP102 temperature(D10, D11, 0x90);

#elif defined(TARGET_LPC4088)
TMP102 temperature(p9, p10, 0x90);

#elif defined(TARGET_LPC2368)
TMP102 temperature(p28, p27, 0x90);

#elif defined(TARGET_NUCLEO_F030R8) || \
      defined(TARGET_NUCLEO_F070RB) || \
      defined(TARGET_NUCLEO_F072RB) || \
      defined(TARGET_NUCLEO_F091RC) || \
      defined(TARGET_NUCLEO_F103RB) || \
      defined(TARGET_NUCLEO_F302R8) || \
      defined(TARGET_NUCLEO_F303RE) || \
      defined(TARGET_NUCLEO_F334R8) || \
      defined(TARGET_NUCLEO_F401RE) || \
      defined(TARGET_NUCLEO_F411RE) || \
      defined(TARGET_NUCLEO_L053R8) || \
      defined(TARGET_NUCLEO_L073RZ) || \
      defined(TARGET_NUCLEO_L152RE) || \
      defined(TARGET_LPC824) || \
      defined(TARGET_FF_ARDUINO) || \
      defined(TARGET_MAXWSNENV)
TMP102 temperature(I2C_SDA, I2C_SCL, 0x90);

#else
TMP102 temperature(p28, p27, 0x90);
#endif

int main() {
    MBED_HOSTTEST_TIMEOUT(10);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(DigitalIn DigitalOut);
    MBED_HOSTTEST_START("MBED_A4");

    float t = temperature.read();

    printf("TMP102: Temperature: %f\n\r", t);
    // In our test environment (ARM office) we should get a temperature within
    // the range ]15, 30[C
    bool result = (t > 15.0) && (t < 30.0);
    MBED_HOSTTEST_RESULT(result);
}
