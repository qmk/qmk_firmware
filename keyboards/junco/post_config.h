// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef JUNCO_SYNC_ENABLE
// Keyboard-level data sync ids
#    define SPLIT_TRANSACTION_IDS_KB KB_SYNC, KB_SYNC_RESET, KB_SYNC_RGB

// By default will throttle syncs to a maximum of 1 per second
#    ifndef JUNCO_SYNC_THROTTLE
#        define JUNCO_SYNC_THROTTLE 1000
#    endif
// By default, syncs will be tried 10 times before giving up
#    ifndef JUNCO_SYNC_RETRIES
#        define JUNCO_SYNC_RETRIES 10
#    endif

#endif
