#include "gtest/gtest.h"

extern "C" {
#include "stdio.h"
#include "debug.h"

int8_t sendchar(uint8_t c) {
    fprintf(stdout, "%c", c);
    return 0;
}

__attribute__((weak)) debug_config_t debug_config = {0};

void init_logging(void) {
    print_set_sendchar(sendchar);

    // Customise these values to desired behaviour
    // debug_enable   = true;
    // debug_matrix   = true;
    // debug_keyboard = true;
    // debug_mouse    = true;
    debug_config.raw = 0xFF;
}
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    init_logging();

    return RUN_ALL_TESTS();
}