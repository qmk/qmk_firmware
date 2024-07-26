// Copyright 2025 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// No driver, once more drivers are available, device
// specific config goes in here.
#ifndef DIGITIZER_WIDTH_MM
#    define DIGITIZER_WIDTH_MM 100
#endif
#ifndef DIGITIZER_HEIGHT_MM
#    define DIGITIZER_HEIGHT_MM 100
#endif

#ifndef DIGITIZER_RESOLUTION_X
#    define DIGITIZER_RESOLUTION_X 1920
#endif
#ifndef DIGITIZER_RESOLUTION_Y
#    define DIGITIZER_RESOLUTION_Y 1080
#endif

#ifndef DIGITIZER_HAS_STYLUS
#    define DIGITIZER_HAS_STYLUS true
#endif

#ifndef DIGITIZER_FINGER_COUNT
#    define DIGITIZER_FINGER_COUNT 0
#endif

#ifndef DIGITIZER_CONTACT_COUNT
#    define DIGITIZER_CONTACT_COUNT MAX(1, DIGITIZER_FINGER_COUNT)
#endif

#if DIGITIZER_FINGER_COUNT > 5
#    error "DIGITIZER_FINGER_COUNT must be <= 5"
#endif

#if DIGITIZER_FINGER_COUNT > DIGITIZER_CONTACT_COUNT
#    error "DIGITIZER_FINGER_COUNT must be <= DIGITIZER_CONTACT_COUNT"
#endif
