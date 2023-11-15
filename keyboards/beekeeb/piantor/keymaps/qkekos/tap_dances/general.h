
#pragma once
#include "../__init__.h"
#include "multiaction_core.h"

extern tap_dance_action_t tap_dance_actions[];

#define SEQ_TD(func) ACTION_TAP_DANCE_FN_ADVANCED(func, NULL, NULL)

void lock_td(enum td_actions action);
void num_td(enum td_actions action);
void lang_td(enum td_actions action);

void invert_lock(void);
void invert_num(void);
