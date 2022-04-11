#pragma once

#include "../base.h"
#include "../hardware/left_space.h"
#include "dynamic.h"
#include "static.h"

// Prepend key records with macros
bool process_record_user(uint16_t keycode, keyrecord_t* record);
