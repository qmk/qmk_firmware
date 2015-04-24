#include "mbed.h"
#include "test_env.h"

#define SIZE (10)
#define ADDR (0x90)

#if defined(TARGET_KL25Z)
I2C i2c(PTE0, PTE1);
#elif defined(TARGET_nRF51822)
I2C i2c(p22,p20);
#elif defined(TARGET_FF_ARDUINO) || defined(TARGET_MAXWSNENV)
I2C i2c(I2C_SDA, I2C_SCL);
#else
I2C i2c(p28, p27);
#endif

int main() {
    bool success = true;
    char buf[] = {3, 2, 1, 4, 5, 6, 7, 8, 9, 10};
    char res[SIZE];

    i2c.write(ADDR, buf, SIZE);
    i2c.read(ADDR, res, SIZE);

    // here should be buf[all]++
    i2c.write(ADDR, res, SIZE);
    i2c.read(ADDR, res, SIZE);

    // here should be buf[all]+=2
    i2c.write(ADDR, res, SIZE);
    i2c.write(ADDR, res, SIZE);

    // here should be buf[all]+=3
    i2c.read(ADDR, res, SIZE);
    i2c.read(ADDR, res, SIZE);

    for(int i = 0; i < SIZE; i++) {
        if (res[i] != (buf[i] + 3)) {
            success = false;
            break;
        }
    }

    notify_completion(success);
}
