#pragma once

/* Selected Unicode input method relies on WinCompose
 * https://docs.qmk.fm/#/feature_unicode?id=input-modes
 * Linux users are better served by xkb configuration
 * https://gitlab.com/lykt/geotype/-/blob/master/xkb/dsae
 */
#define UNICODE_SELECTED_MODES UC_WINC
