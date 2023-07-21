/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
	k0A, k0B, k0C, k0D, k1A, k1B, k1C, k1D, k2A, k2B, k2C, k2D, k3B, k3C, k3D, k4A, k4B, k4C, k4D, k5B, k5D \
) { \
	{k0A, k0B, k0C, k0D}, \
	{k1A, k1B, k1C, k1D}, \
	{k2A, k2B, k2C, k2D}, \
	{XXX, k3B, k3C, k3D}, \
	{k4A, k4B, k4C, k4D}, \
	{XXX, k5B, XXX, k5D} \
}
