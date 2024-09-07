// Copyright 2022 @geigeigeist
// SPDX-License-Identifier: GPL-2.0+

#pragma once

#define WINXP_SOUND W__NOTE(_DS6), Q__NOTE(_DS5), H__NOTE(_AS5), H__NOTE(_GS5), H__NOTE(_DS5), H__NOTE(_DS6), H__NOTE(_AS5)
#define MAC_SOUND S__NOTE(_CS5), B__NOTE(_C5)
#define CAPSON_SOUND Q__NOTE(_DS1)
#define CAPSOFF_SOUND Q__NOTE(_DS5)

float winxp_song[][2] = SONG(WINXP_SOUND);
float mac_song[][2] = SONG(MAC_SOUND);
float capson_song[][2] = SONG(CAPSON_SOUND);
float capsoff_song[][2] = SONG(CAPSOFF_SOUND);

