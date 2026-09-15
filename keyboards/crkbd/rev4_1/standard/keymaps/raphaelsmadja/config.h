/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

// Layer 0 utilise l'effet "typing heatmap" (typing_heatmap est déjà activé
// par info.json ; forcé au boot dans keymap.c car RGB_MATRIX_DEFAULT_MODE
// ne s'applique qu'à une EEPROM vierge)
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP

// SPLIT_LAYER_STATE_ENABLE (pour synchroniser le layer actif vers la moitié
// droite) a rendu ce côté complètement inutilisable au flash — retiré en
// attendant d'en comprendre la cause. En attendant, les couleurs par layer
// dans rgb_matrix_indicators_user() ne s'appliquent qu'à la moitié gauche.
