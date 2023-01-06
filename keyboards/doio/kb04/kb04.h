#pragma once

#include "quantum.h"
#include "print.h"

/*                    06 ◯ 05
 * ┌───┬───┬───┬───┐   ┌───┐
 * │00 │01 │02 │03 │   │04 │
 * └───┴───┴───┴───┘   └───┘
 */

#define LAYOUT(K00, K01, K02, K03, K04) {{ K00, K01, K02, K03, K04 }}