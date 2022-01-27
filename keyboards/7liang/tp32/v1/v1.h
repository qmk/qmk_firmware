/*
 * @Description    : 
 * @version        : 
 * @Author         : JunLee
 * @Date           : 2022-01-27 09:50:47
 * @LastEditTime   : 2022-01-27 11:36:25
 * @FilePath       : \qmk_firmware\keyboards\7liang\tp32\v1\v1.h
 */

#pragma once

#include "tp32.h"

#include "quantum.h"

#define ___     KC_NO

#define LAYOUT_ortho_3x12(  \
    K00, K01, K02, K03, K04,           K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14,           K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B  \
    ) { \
        { K00, K01, K02, K03, K04, ___, ___, K07, K08, K09, K0A, K0B }, \
        { K10, K11, K12, K13, K14, ___, ___, K17, K18, K19, K1A, K1B }, \
        { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B }  \
    }
