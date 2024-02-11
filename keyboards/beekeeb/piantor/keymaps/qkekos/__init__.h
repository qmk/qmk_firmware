
#pragma once

#include <stdlib.h>
#include "math.h"

#include QMK_KEYBOARD_H
#include "transactions.h"

#include "protected.h"
#include "general/__init__.h"
#include "combos/__init__.h"
#include "localization/__init__.h"
#include "magic_sturdy/__init__.h"
#include "overrides/__init__.h"
#include "tap_dances/__init__.h"
#include "tap_holds/__init__.h"
#include "typing_modes/__init__.h"

#define highest_layer get_highest_layer(layer_state)
extern int combo_actions_keys[][2];

#define PR_IGNORE -1
#define PR_FALSE   0
#define PR_TRUE    1
