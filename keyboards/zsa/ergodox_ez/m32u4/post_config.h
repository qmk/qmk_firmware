// Copyright 2012 Jun Wako <wakojun@gmail.com>
// Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
// Copyright 2015 ZSA Technology Labs Inc (@zsa)
// Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#    undef PRODUCT
#    undef PRODUCT_ID
#endif

#if defined(RGB_MATRIX_ENABLE)
#    define PRODUCT "ErgoDox EZ Glow"
#    define PRODUCT_ID 0x4976
#elif defined(RGBLIGHT_ENABLE)
#    define PRODUCT "ErgoDox EZ Shine"
#    define PRODUCT_ID 0x4975
#endif
