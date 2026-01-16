// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Override the one in quantum/util because it doesn't like working on x64 builds.
#define ARRAY_SIZE(array) (sizeof((array)) / sizeof((array)[0]))
