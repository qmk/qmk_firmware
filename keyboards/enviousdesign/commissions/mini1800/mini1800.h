/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
	k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0J, k0K, k0L, k0M, k0N, k0O, k0P, k0Q, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I, k1J, k1K, k1L, k1M, k1O, k1P, k1Q, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I, k2J, k2K, k2L, k2O, k2P, k2Q, k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, k3J, k3L, k3O, k3P, k3Q, k3M, k4A, k4B, k4C, k4E, k4G, k4I, k4K, k4P, k4Q, k4L, k4M, k4N \
) { \
	{k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0J, k0K, k0L, k0M, k0N, k0O, k0P, k0Q}, \
	{k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I, k1J, k1K, k1L, k1M, XXX, k1O, k1P, k1Q}, \
	{k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I, k2J, k2K, k2L, XXX, XXX, k2O, k2P, k2Q}, \
	{k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, k3J, XXX, k3L, k3M, XXX, k3O, k3P, k3Q}, \
	{k4A, k4B, k4C, XXX, k4E, XXX, k4G, XXX, k4I, XXX, k4K, k4L, k4M, k4N, XXX, k4P, k4Q} \
}
