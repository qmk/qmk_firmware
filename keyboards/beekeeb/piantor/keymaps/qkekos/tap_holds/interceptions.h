
#pragma once
#include "../__init__.h"

#define intercept_tap(body) \
    if (record->tap.count && record->event.pressed) { \
        body; \
        return false; \
    } \
    return PR_IGNORE;

#define intercept_hold(body) \
    if (!record->tap.count && record->event.pressed) { \
        body; \
        return false; \
    } \
    return PR_IGNORE;
