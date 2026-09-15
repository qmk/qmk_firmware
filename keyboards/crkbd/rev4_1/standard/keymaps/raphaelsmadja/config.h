/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

// Layer 0 utilise l'effet "typing heatmap" (typing_heatmap est déjà activé
// par info.json ; forcé au boot dans keymap.c car RGB_MATRIX_DEFAULT_MODE
// ne s'applique qu'à une EEPROM vierge)
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP

// Synchronise le layer actif vers la moitié droite (esclave) pour que
// rgb_matrix_indicators_user() y applique aussi les couleurs par layer
#define SPLIT_LAYER_STATE_ENABLE
