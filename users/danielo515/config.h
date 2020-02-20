#pragma once

#if defined(COMBO_ENABLE)
  #define COMBO_COUNT 4
  #define COMBO_TERM  40
#endif // !COMBO_ENABLE
// Timeout settings for leader key
#undef  LEADER_TIMEOUT
#define LEADER_TIMEOUT 350
#define LEADER_PER_KEY_TIMING
