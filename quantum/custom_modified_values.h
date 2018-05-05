#ifndef _CUSTOM_MODIFIED_VALUES_H_
#define _CUSTOM_MODIFIED_VALUES_H_

#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "action_util.h"
#ifdef CMV_COMPLETE_VERSION
# include "keyboard.h"
#endif

#ifndef CMV_NUMBER_OF_HELD_KEYS
#define CMV_NUMBER_OF_HELD_KEYS 8
#endif

#define CMV(kc_default, kc_shifted, kc_altgred, kc_sftralt) set_cmv_buffer(kc_default, kc_shifted, kc_altgred, kc_sftralt)
bool set_cmv_buffer(uint16_t kc_default, uint16_t kc_shifted, uint16_t kc_altgred, uint16_t kc_sftralt);

#ifdef CMV_COMPLETE_VERSION
# define get_dakp() get_dynamic_active_key_processing()
# define toggle_dynamic_active_key_processing() set_dynamic_active_key_processing(!get_dynamic_active_key_processing())
# define toggle_dakp() toggle_dynamic_active_key_processing()
  bool get_dynamic_active_key_processing(void);
  bool set_dynamic_active_key_processing(bool new_state);

# ifndef CMV_NO_DELAY_AFTER_MODIFIER_RELEASE
#   ifndef CMV_TIME_AFTER_MODIFIER_RELEASE
#     define CMV_TIME_AFTER_MODIFIER_RELEASE 200
#   endif

#   define get_damr() get_delay_after_modifier_release()
#   define toggle_delay_after_modifier_release() set_delay_after_modifier_release(!get_delay_after_modifier_release())
#   define toggle_damr() toggle_delay_after_modifier_release()
    bool get_delay_after_modifier_release(void);
    bool set_delay_after_modifier_release(bool new_state);
# endif
#endif

#endif
