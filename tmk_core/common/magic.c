#include <stdint.h>
#include <stdbool.h>
#if defined(__AVR__)
#include <util/delay.h>
#endif
#include "matrix.h"
#include "bootloader.h"
#include "debug.h"
#include "keymap.h"
#include "host.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "magic.h"

keymap_config_t keymap_config;

void magic(void)
{
    /* check signature */
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }

    /* debug enable */
    debug_config.raw = eeconfig_read_debug();

    /* keymap config */
    keymap_config.raw = eeconfig_read_keymap();

    uint8_t default_layer = 0;
    default_layer = eeconfig_read_default_layer();
    default_layer_set((uint32_t)default_layer);

}
