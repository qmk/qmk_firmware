// Copyright 2023 Michal S. (@not-my-segfault)
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

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