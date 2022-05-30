#pragma once

#include "alt34.h"
#include "quantum.h"

#define ____ KC_NO

/*              left hand                     right hand            */
#define LAYOUT_split_3x5_2(\
    K0_0, K0_1, K0_2, K0_3, K0_4,       K0_5, K0_6, K0_7, K0_8, K0_9,\
    K1_0, K1_1, K1_2, K1_3, K1_4,       K1_5, K1_6, K1_7, K1_8, K1_9,\
    K2_0, K2_1, K2_2, K2_3, K2_4,       K2_5, K2_6, K2_7, K2_8, K2_9,\
                      K3_2, K3_3,       K3_4, K3_5 )\
/* matrix positions */\
{\
    {K0_0,  K0_1,  K0_2,  K0_3,  K0_4},\
    {K1_0,  K1_1,  K1_2,  K1_3,  K1_4},\
    {K2_0,  K2_1,  K2_2,  K2_3,  K2_4},\
    {____,  ____,  ____,  K3_2,  K3_3},\
	\
	{K0_9,  K0_8,  K0_7,  K0_6,  K0_5},\
	{K1_9,  K1_8,  K1_7,  K1_6,  K1_5},\
	{K2_9,  K2_8,  K2_7,  K2_6,  K2_5},\
	{____,  ____,  ____,  K3_5,  K3_4} \
}
