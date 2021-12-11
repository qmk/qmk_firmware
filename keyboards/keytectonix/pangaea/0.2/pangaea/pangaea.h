#pragma once

#include "quantum.h"

/*                       _     _     _      _     _     _    _
 *                      |__\  |_\   | \ |  | \   |_\   |_   |_\
 *                      |     |  \  |  \|  |__7  |  \  |__  |  \
 * .............  .........................    .........................  .............
 * :     :     :  :     :     :     :     :    :     :     :     :     :  :     :     :
 * ,-----------.  ,-----------------------.    ,-----------------------.  ,-----------.
 * |     |     |  |     |     |     |     |    |     |     |     |     |  |     |     |
 * |-----------|  |-----------------------|    |-----------------------|  |-----------|
 * |     |     |  |     |     |     |     |    |     |     |     |     |  |     |     |
 * |-----------|  |-----------------------|    |-----------------------|  |-----------|
 * |     |     |  |     |     |     |     |    |     |     |     |     |  |     |     |
 * |-----------|  |-----------------------|    |-----------------------|  |-----------|
 * |     |     |  |     |     |     |     |    |     |     |     |     |  |     |     |
 * '-----------'  '-----------------------'    '-----------------------'  '-----------'
 *          ,------------------------------.    ,-----------------------------.
 *          |     |     |     |     |     |    |     |     |     |     |     |
 *          '-----------------------------'    '-----------------------------'
 *          :     :     :     :     :     :    :     :     :     :     :     :
 *          ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
 */

#define LAYOUT( \
	L_D4_to_B4,	L_B4_to_D4,	L_C6_to_B4,	L_B4_to_C6,	L_D7_to_B4,	L_B4_to_D7,		R_B4_to_D7,	R_D7_to_B4,	R_B4_to_C6,	R_C6_to_B4,	R_B4_to_D4,	R_D4_to_B4,	\
	L_D4_to_B5,	L_B5_to_D4,	L_C6_to_B5,	L_B5_to_C6,	L_D7_to_B5,	L_B5_to_D7,		R_B5_to_D7,	R_D7_to_B5,	R_B5_to_C6,	R_C6_to_B5,	R_B5_to_D4,	R_D4_to_B5,	\
	L_D4_to_F4,	L_F4_to_D4,	L_C6_to_F4,	L_F4_to_C6,	L_D7_to_F4,	L_F4_to_D7,		R_F4_to_D7,	R_D7_to_F4,	R_F4_to_C6,	R_C6_to_F4,	R_F4_to_D4,	R_D4_to_F4,	\
	L_D4_to_F5,	L_F5_to_D4,	L_C6_to_F5,	L_F5_to_C6,	L_D7_to_F5,	L_F5_to_D7,		R_F5_to_D7,	R_D7_to_F5,	R_F5_to_C6,	R_C6_to_F5,	R_F5_to_D4,	R_D4_to_F5,	\
	L_D4_to_F6,	L_F6_to_D4,	L_C6_to_F6,	L_F6_to_C6,	L_D7_to_F6,	L_F6_to_D7,		R_F6_to_D7,	R_D7_to_F6,	R_F6_to_C6,	R_C6_to_F6,	R_F6_to_D4,	R_D4_to_F6,	\
		L_E6_to_B4,	L_E6_to_B5,	L_E6_to_F4,	L_E6_to_F5,	L_E6_to_F6,		R_E6_to_F6,	R_E6_to_F5,	R_E6_to_F4,	R_E6_to_B5,	R_E6_to_B4,		\
		L_B4_to_E6,	L_B5_to_E6,	L_F4_to_E6,	L_F5_to_E6,	L_F6_to_E6,		R_F6_to_E6,	R_F5_to_E6,	R_F4_to_E6,	R_B5_to_E6,	R_B4_to_E6	\
) { \
	{	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	L_D4_to_B4,	L_C6_to_B4,	L_D7_to_B4,	L_E6_to_B4	}, \
	{	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	L_D4_to_B5,	L_C6_to_B5,	L_D7_to_B5,	L_E6_to_B5	}, \
	{	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	L_D4_to_F4,	L_C6_to_F4,	L_D7_to_F4,	L_E6_to_F4	}, \
	{	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	L_D4_to_F5,	L_C6_to_F5,	L_D7_to_F5,	L_E6_to_F5	}, \
	{	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	L_D4_to_F6,	L_C6_to_F6,	L_D7_to_F6,	L_E6_to_F6	}, \
	{	L_B4_to_D4,	L_B5_to_D4,	L_F4_to_D4,	L_F5_to_D4,	L_F6_to_D4,	KC_NO,	KC_NO,	KC_NO,	KC_NO	}, \
	{	L_B4_to_C6,	L_B5_to_C6,	L_F4_to_C6,	L_F5_to_C6,	L_F6_to_C6,	KC_NO,	KC_NO,	KC_NO,	KC_NO	}, \
	{	L_B4_to_D7,	L_B5_to_D7,	L_F4_to_D7,	L_F5_to_D7,	L_F6_to_D7,	KC_NO,	KC_NO,	KC_NO,	KC_NO	}, \
	{	L_B4_to_E6,	L_B5_to_E6,	L_F4_to_E6,	L_F5_to_E6,	L_F6_to_E6,	KC_NO,	KC_NO,	KC_NO,	KC_NO	}, \
	{	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	R_D4_to_B4,	R_C6_to_B4,	R_D7_to_B4,	R_E6_to_B4	}, \
	{	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	R_D4_to_B5,	R_C6_to_B5,	R_D7_to_B5,	R_E6_to_B5	}, \
	{	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	R_D4_to_F4,	R_C6_to_F4,	R_D7_to_F4,	R_E6_to_F4	}, \
	{	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	R_D4_to_F5,	R_C6_to_F5,	R_D7_to_F5,	R_E6_to_F5	}, \
	{	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	R_D4_to_F6,	R_C6_to_F6,	R_D7_to_F6,	R_E6_to_F6	}, \
	{	R_B4_to_D4,	R_B5_to_D4,	R_F4_to_D4,	R_F5_to_D4,	R_F6_to_D4,	KC_NO,	KC_NO,	KC_NO,	KC_NO	}, \
	{	R_B4_to_C6,	R_B5_to_C6,	R_F4_to_C6,	R_F5_to_C6,	R_F6_to_C6,	KC_NO,	KC_NO,	KC_NO,	KC_NO	}, \
	{	R_B4_to_D7,	R_B5_to_D7,	R_F4_to_D7,	R_F5_to_D7,	R_F6_to_D7,	KC_NO,	KC_NO,	KC_NO,	KC_NO	}, \
	{	R_B4_to_E6,	R_B5_to_E6,	R_F4_to_E6,	R_F5_to_E6,	R_F6_to_E6,	KC_NO,	KC_NO,	KC_NO,	KC_NO	} \
}

