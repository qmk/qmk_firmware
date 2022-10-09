// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "cpp_map.h"

//build -> _<sym>,
#define _BUILD_LAYER_ENUM_NUMBER(sym, str) _ ## sym,
#define BUILD_LAYER_ENUM_NUMBER(ent) _BUILD_LAYER_ENUM_NUMBER ent

//build -> static const char <sym>_name[]  PROGMEM = str;
#define _BUILD_LAYER_NAME_STR(sym, str) static const char sym ## _name[]  PROGMEM = str;
#define BUILD_LAYER_NAME_STR(ent) _BUILD_LAYER_NAME_STR ent

//build -> [_<sym>] = <sym>_name,
#define _BUILD_LAYER_NAME_TABLE(sym, str) [_##sym] = sym ## _name,
#define BUILD_LAYER_NAME_TABLE(ent) _BUILD_LAYER_NAME_TABLE ent
