// Copyright 2021 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    k00, e01, e02, \
    e01a, e01b, e02a, e02b \
) { \
    { k00, e01, e02, KC_NO }, \
    { e01a, e01b, e02a, e02b }  \
}
