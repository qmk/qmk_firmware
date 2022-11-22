/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT_all( \
	k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0J, k0K, k0L, k0M, k0O, k1A, k1C, k1D, k1E, k1F, k1G, k1H, k1I, k1J, k1K, k1L, k1M, k1N, k2O, k2A, k2C, k2D, k2E, k2F, k2G, k2H, k2I, k2J, k2K, k2L, k2M, k2N, k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, k3J, k3K, k3L, k3M, k3O, k3P, k3Q, k4A, k4B, k4D, k4E, k4G, k4I, k4K, k4L, k4M, k4N, k4O, k4P, k4Q \
) { \
	{k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0J, k0K, k0L, k0M, XXX, k0O, XXX, XXX}, \
	{k1A, XXX, k1C, k1D, k1E, k1F, k1G, k1H, k1I, k1J, k1K, k1L, k1M, k1N, XXX, XXX, XXX}, \
	{k2A, XXX, k2C, k2D, k2E, k2F, k2G, k2H, k2I, k2J, k2K, k2L, k2M, k2N, k2O, XXX, XXX}, \
	{k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, k3J, k3K, k3L, k3M, XXX, k3O, k3P, k3Q}, \
	{k4A, k4B, XXX, k4D, k4E, XXX, k4G, XXX, k4I, XXX, k4K, k4L, k4M, k4N, k4O, k4P, k4Q} \
}
