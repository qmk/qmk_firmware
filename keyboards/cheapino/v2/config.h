// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Shorter settle time than the default 30 us, to make up for the time
// spent on ghost handling.
#define MATRIX_IO_DELAY 25
