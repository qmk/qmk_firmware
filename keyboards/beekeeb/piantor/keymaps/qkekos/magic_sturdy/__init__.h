
#pragma once
#include "../__init__.h"

#include "general.h"
#include "magic_key.h"
#include "rep_key.h"

#define magic_case(trigger, supplement) \
    case trigger: \
        SEND_STRING(supplement); \
        return

#define remember_magic_case(trigger, supplement, key_to_remember) \
    case trigger: \
        SEND_STRING(supplement); \
        prev_last_key = keycode; \
        set_last_keycode(key_to_remember); \
        return

#define double_magic_case(trigger, body) \
    case trigger: \
        switch (keycode) { \
            body \
        } \
        break
