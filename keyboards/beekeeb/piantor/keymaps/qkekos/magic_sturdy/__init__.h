
#pragma once
#include "../__init__.h"

#include "general.h"
#include "rep_key.h"
#include "context_magic.h"

#define single_queue_check(p_key) queue(-1) == p_key
#define double_queue_check(pp_key, p_key) queue(-2) == pp_key && single_queue_check(p_key)
#define triple_queue_check(ppp_key, pp_key, p_key) queue(-3) == ppp_key && double_queue_check(pp_key, p_key)
#define quadruple_queue_check(pppp_key, ppp_key, pp_key, p_key) queue(-4) == pppp_key && triple_queue_check(ppp_key, pp_key, p_key)

#define magic_case_core(trigger, condition, supplement) \
    case trigger: \
        if (condition) { \
            record_send_string(supplement); \
            return; \
        } \
        break

#define magic_switch_core(trigger, body, index) \
    case trigger: \
        switch (queue(index)) { \
            body \
        } \
        break

#define magic_case(trigger, supplement) \
    case trigger: \
        record_send_string(supplement); \
        return

#define double_magic_switch(trigger, body) \
    magic_switch_core(trigger, body, -1)

#define triple_magic_switch(trigger, body) \
    magic_switch_core(trigger, body, -2)

#define double_magic_case(trigger, p_key, supplement) \
    magic_case_core(trigger, single_queue_check(p_key), supplement)

#define triple_magic_case(trigger, pp_key, p_key, supplement) \
    magic_case_core(trigger, double_queue_check(pp_key, p_key), supplement)

#define quadruple_magic_case(trigger, ppp_key, pp_key, p_key, supplement) \
    magic_case_core(trigger, triple_queue_check(ppp_key, pp_key, p_key), supplement)

#define quintuple_magic_case(trigger, pppp_key, ppp_key, pp_key, p_key, supplement) \
    magic_case_core(trigger, quadruple_queue_check(pppp_key, ppp_key, pp_key, p_key), supplement)
