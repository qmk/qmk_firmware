#include <string.h>
#include "pico/platform.h"
#include "pico/rand.h"

/* Function to feed mbedtls entropy. */
int mbedtls_hardware_poll(void *data __unused, unsigned char *output, size_t len, size_t *olen) {
    *olen = 0;
    while(*olen < len) {
        uint64_t rand_data = get_rand_64();
        size_t to_copy = MIN(len, sizeof(rand_data));
        memcpy(output + *olen, &rand_data, to_copy);
        *olen += to_copy;
    }
    return 0;
}
