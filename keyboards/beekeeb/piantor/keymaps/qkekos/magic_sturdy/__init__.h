
#pragma once
#include "../__init__.h"

#include "general.h"
#include "magic_key.h"
#include "rep_key.h"

#define magic_case(trigger, supplement) \
    case trigger: \
        record_send_string(supplement); \
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
            record_send_string(supplement); \
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
            record_send_string(supplement); \
            return; \
        } \
        break

#define quadruple_magic_case(trigger, ppp_key, pp_key, p_key, supplement) \
    case trigger: \
        if (queue(-3) == ppp_key && queue(-2) == pp_key && queue(-1) == p_key) { \
            record_send_string(supplement); \
            return; \
        } \
        break
