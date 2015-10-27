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

// Test configuration block
namespace {
const int ntests = 1000;
const int i2c_freq_hz = 400000;
const int i2c_delay_us = 0;
// const int EEPROM_24LC256_SIZE = (256 * 1024 / 8);   // 256 kbit memory
}

// End of test configuration block

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

#define PATTERN_MASK 0x66, ~0x66, 0x00, 0xFF, 0xA5, 0x5A, 0xF0, 0x0F

int main() {
    MBED_HOSTTEST_TIMEOUT(15);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(I2C EEPROM line read write test);
    MBED_HOSTTEST_START("MBED_A25");

    const int EEPROM_MEM_ADDR = 0xA0;
    bool result = true;

    i2c.frequency(i2c_freq_hz);
    printf("I2C: I2C Frequency: %d Hz\r\n", i2c_freq_hz);

    printf("I2C: Lines pattern write test ... ");
    int write_errors = 0;
    for (int i = 0; i < ntests; i++) {
        char data[] = { 0 /*MSB*/, 0 /*LSB*/, PATTERN_MASK };
        const int addr = i * 8;   // 8 bytes of data in data array
        data[0] = ((0xFF00 & addr) >> 8) & 0x00FF;
        data[1] = (addr & 0x00FF);

        if (i2c.write(EEPROM_MEM_ADDR, data, sizeof(data)) != 0) {
            write_errors++;
        }

        while (i2c.write(EEPROM_MEM_ADDR, NULL, 0)) ; // wait to complete

        // us delay if specified
        if (i2c_delay_us != 0) {
            wait_us(i2c_delay_us);
        }
    }

    printf("[%s]\r\n", write_errors ? "FAIL" : "OK");
    printf("I2C: Write errors: %d ... [%s]\r\n", write_errors, write_errors ? "FAIL" : "OK");

    printf("I2C: Lines pattern read test ... ");
    int read_errors = 0;
    int pattern_errors = 0;
    for (int i = 0; i < ntests; i++) {
        char data[8] = { 0 };   // General puspose buffer
        const int addr = i * 8; // 8 bytes of data in data array
        data[0] = ((0xFF00 & addr) >> 8) & 0x00FF;
        data[1] = (addr & 0x00FF);

        // Set address for read
        if (i2c.write(EEPROM_MEM_ADDR, data, 2, true) != 0) {
        }

        if (i2c.read(EEPROM_MEM_ADDR, data, 8) != 0) {
            read_errors++;
        }

        static char pattern[] = { PATTERN_MASK };
        if (memcmp(pattern, data, sizeof(data))) {
            pattern_errors++;
        }
    }

    printf("[%s]\r\n", read_errors ? "FAIL" : "OK");
    printf("I2C: Read errors: %d/%d ... [%s]\r\n", read_errors, ntests, read_errors ? "FAIL" : "OK");
    printf("EEPROM: Pattern match errors: %d/%d ... [%s]\r\n", pattern_errors, ntests, pattern_errors ? "FAIL" : "OK");

    result = write_errors == 0 && read_errors == 0;
    MBED_HOSTTEST_RESULT(result);
}
