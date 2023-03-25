// Copyright 2023 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#ifdef UNICODEMAP_ENABLE
#    define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX, UNICODE_MODE_MACOS, UNICODE_MODE_WINDOWS, UNICODE_MODE_WINCOMPOSE
#endif

#ifdef WPM_ENABLE
#    define WPM_SAMPLE_SECONDS 10
#    define WPM_SAMPLE_PERIODS 100
#    define WPM_ALLOW_COUNT_REGRESSION
#endif
