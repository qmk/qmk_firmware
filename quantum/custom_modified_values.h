#ifndef _CUSTOM_MODIFIED_VALUES_H_
#define _CUSTOM_MODIFIED_VALUES_H_

#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "action_util.h"

#ifndef CMV_NUMBER_OF_HELD_KEYS
#define CMV_NUMBER_OF_HELD_KEYS 8
#endif

#define CMV(kc_default, kc_shifted, kc_altgred, kc_sftralt) set_cmv_buffer(kc_default, kc_shifted, kc_altgred, kc_sftralt)
bool set_cmv_buffer(uint16_t kc_default, uint16_t kc_shifted, uint16_t kc_altgred, uint16_t kc_sftralt);

#endif
