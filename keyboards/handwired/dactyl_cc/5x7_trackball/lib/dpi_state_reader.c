#include <stdio.h>
#include <inttypes.h>
#include "pointing_device.h"

char dpi_state_str[12];
#define PRIu16 "hu"
#define PRId16 "hd"
#define PRIx16 "hx"

const char *read_cpi_str(void) {

    snprintf(dpi_state_str, sizeof(dpi_state_str), "DPI: %" PRIu16,
    (pointing_device_set_cpi));
  return dpi_state_str;
}
