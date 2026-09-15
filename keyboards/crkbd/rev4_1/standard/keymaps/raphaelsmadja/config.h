/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

// Layer 0 utilise l'effet "typing heatmap" (typing_heatmap est déjà activé
// par info.json ; forcé au boot dans keymap.c car RGB_MATRIX_DEFAULT_MODE
// ne s'applique qu'à une EEPROM vierge)
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP

// Synchroniser le layer actif vers la moitié droite (pour les couleurs par
// layer dans rgb_matrix_indicators_user()) reste non résolu : 5 tentatives
// différentes ont toutes cassé le scan clavier côté droit, jusqu'à isoler
// que le simple appel à transaction_register_rpc() suffit (même sans jamais
// envoyer de donnée). Voir la PR pour le détail des essais. Les couleurs par
// layer ne s'appliquent donc qu'à la moitié gauche pour l'instant.
