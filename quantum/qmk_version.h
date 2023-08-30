// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define QMK_MAJOR 0
#define QMK_MINOR 22
#define QMK_PATCH 1

// number that can be used to order all versions, 0x prefix because otherwise leading zeros would get this number interpreted as an octal literal
// reserved 2/3/3 digits for each part of the version, so that it fits on 4 bytes
// example: "#if __QMK__ == 0x00020005" (for 0.20.5), note how it is '20' and not '14' (values in base 10)
#define __QMK__ 0x00022001
