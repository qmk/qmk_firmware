// Copyright 2026 Ryan McLean
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Board identifier — WCH CH579M macropad (KEY12-V02).
 */

#define CH579M

#if !defined(_FROM_ASM_)
#    ifdef __cplusplus
extern "C" {
#    endif
void boardInit(void);
#    ifdef __cplusplus
}
#    endif
#endif /* _FROM_ASM_ */
