// Copyright 2022 Michal S. (@ihatethefrench)
// SPDX-License-Identifier: GPL-2.0-only

#pragma once

// Enables features such as octave changer, suspend, etc.
#define MIDI_ADVANCED

// This autoshift delay feels most natural for me I think
#define AUTO_SHIFT_TIMEOUT 165

// I don't use too many layers, so this is more than enough
#define LAYER_STATE_8BIT

// Saving space
#define NO_ACTION_ONESHOT
#define NO_ACTION_TAPPING
#define NO_MUSIC_MODE

// If I recall correctly, these aren't necessary for the sofle
// so i disable them to save more space.
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE