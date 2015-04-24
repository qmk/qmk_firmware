#include "test_env.h"

/******************************************************************************
*  This will test an I2C EEPROM connected to mbed by writing a predefined byte at
*  address 0 and then reading it back and comparing it with the known byte value a
*  number of times. This test was written specifically for reproducing the bug
*  reported here:
*
*  https://mbed.org/forum/bugs-suggestions/topic/4128/
*
*  Test configuration:
*
* set 'ntests' to the number of iterations
* set 'i2c_speed_hz' to the desired speed of the I2C interface
* set 'i2c_delay_us' to the delay that will be inserted between 'write' and
*  'read' I2C operations (https://mbed.org/users/mbed_official/code/mbed/issues/1
*  for more details). '0' disables the delay.
* define I2C_EEPROM_VERBOSE to get verbose output
*
*  The test ran with a 24LC256 external EEPROM memory, but any I2C EEPROM memory
*  that uses two byte addresses should work.
******************************************************************************/

#if defined(TARGET_KL25Z)
I2C i2c(PTC9, PTC8);

#elif defined(TARGET_KL46Z)
I2C i2c(PTC9, PTC8);

#elif defined(TARGET_K64F)
I2C i2c(PTE25, PTE24);

#elif defined(TARGET_K22F)
I2C i2c(PTE0, PTE1);

#elif defined(TARGET_K20D50M)
I2C i2c(PTB3, PTB2);

#elif defined(TARGET_LPC812)
I2C i2c(P0_10, P0_11);

#elif defined(TARGET_LPC1549)
I2C i2c(P0_23, P0_22);

#elif defined(TARGET_LPC11U68)
I2C i2c(SDA, SCL);

#elif defined(TARGET_DELTA_DFCM_NNN40)
I2C i2c(I2C_SDA0, I2C_SCL0);

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
      defined(TARGET_FF_ARDUINO)
I2C i2c(I2C_SDA, I2C_SCL);

#else
I2C i2c(p28, p27);
#endif

namespace {
const int ntests = 10000;
const int i2c_freq_hz = 400000;
const int i2c_delay_us = 0;
}

int main() {
    MBED_HOSTTEST_TIMEOUT(15);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(I2C EEPROM read write test);
    MBED_HOSTTEST_START("MBED_A19");

    const int EEPROM_MEM_ADDR = 0xA0;
    const char MARK = 0x66;
    int fw = 0;
    int fr = 0;
    int fc = 0;
    int i2c_stat = 0;
    bool result = true;

    i2c.frequency(i2c_freq_hz);
    printf("I2C: I2C Frequency: %d Hz\r\n", i2c_freq_hz);

    printf("I2C: Write 0x%2X at address 0x0000 test ... \r\n", MARK);
    // Data write
    {
        char data[] = { 0, 0, MARK };
        if ((i2c_stat = i2c.write(EEPROM_MEM_ADDR, data, sizeof(data))) != 0) {
            printf("Unable to write data to EEPROM (i2c_stat = 0x%02X), aborting\r\n", i2c_stat);
            notify_completion(false);
            return 1;
        }

        // ACK polling (assumes write will be successful eventually)
        while (i2c.write(EEPROM_MEM_ADDR, data, 0) != 0)
            ;
    }

    printf("I2C: Read data from address 0x0000 test ... \r\n");
    // Data read (actual test)
    for (int i = 0; i < ntests; i++) {
        // Write data to EEPROM memory
        {
            char data[] = { 0, 0 };
            if ((i2c_stat = i2c.write(EEPROM_MEM_ADDR, data, 2, true)) != 0) {
                printf("Test %d failed at write, i2c_stat is 0x%02X\r\n", i, i2c_stat);
                fw++;
                continue;
            }
        }

        // us delay if specified
        if (i2c_delay_us != 0)
            wait_us(i2c_delay_us);

        // Read data
        {
            char data[1] = { 0 };
            if ((i2c_stat = i2c.read(EEPROM_MEM_ADDR, data, 1)) != 0) {
                printf("Test %d failed at read, i2c_stat is 0x%02X\r\n", i, i2c_stat);
                fr++;
                continue;
            }

            if (data[0] != MARK) {
                printf("Test %d failed at data match\r\n", i);
                fc++;
            }
        }
    }

    result = (fw + fr + fc == 0);
    printf("EEPROM: Test result ... [%s]\r\n", result ? "OK" : "FAIL");

    if (!result) {
        printf("Test Statistics:\r\n");
        printf("\tTotal tests:     %d\r\n", ntests);
        printf("\tFailed at write: %d\r\n", fw);
        printf("\tFailed at read:  %d\r\n", fr);
        printf("\tData mismatch:   %d\r\n", fc);
        printf("\tTotal failures:  %d\r\n", fw + fr + fc);
    }

    MBED_HOSTTEST_RESULT(result);
}
