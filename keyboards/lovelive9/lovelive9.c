#include "lovelive9.h"
#include "rgblight.h"

#include <avr/pgmspace.h>

#include "action_layer.h"
#include "quantum.h"
#include "rgblight.h"
extern rgblight_config_t rgblight_config;

void matrix_init_kb(void) {
	matrix_init_user();
}
