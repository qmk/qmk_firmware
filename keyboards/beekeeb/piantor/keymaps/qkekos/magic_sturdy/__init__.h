
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
        enqueue(key_to_remember); \
        return

#define double_magic_switch(trigger, body) \
    case trigger: \
        switch (queue(-1)) { \
            body \
        } \
        break

#define double_magic_case(trigger, p_key, supplement) \
    case trigger: \
        if (queue(-1) == p_key) { \
            SEND_STRING(supplement); \
            return; \
        } \
        break

#define triple_magic_switch(trigger, body) \
    case trigger: \
        switch (queue(-2)) { \
            body \
        } \
        break

#define triple_magic_case(trigger, pp_key, p_key, supplement) \
    case trigger: \
        if (queue(-2) == pp_key && queue(-1) == p_key) { \
            SEND_STRING(supplement); \
            return; \
        } \
        break

#define quadruple_magic_case(trigger, ppp_key, pp_key, p_key, supplement) \
    case trigger: \
        if (queue(-3) == ppp_key && queue(-2) == pp_key && queue(-1) == p_key) { \
            SEND_STRING(supplement); \
            return; \
        } \
        break
