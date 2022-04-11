#pragma once

#include "../base.h"
#include "../hardware/left_space.h"
#include "macros/dynamic.h"
#include "macros/static.h"

// Prepend key records with macros
bool process_record_user(uint16_t keycode, keyrecord_t* record);
