
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
        remember_last_key(keycode, key_to_remember); \
        return

#define double_magic_switch(trigger, body) \
    case trigger: \
        switch (keycode) { \
            body \
        } \
        break

#define double_magic_case(trigger, prev_key, supplement) \
    case trigger: \
        if (keycode == prev_key) { \
            SEND_STRING(supplement); \
            return; \
        } \
        break

#define triple_magic_switch(trigger, body) \
    case trigger: \
        switch (last_queue_key) { \
            body \
        } \
        break
