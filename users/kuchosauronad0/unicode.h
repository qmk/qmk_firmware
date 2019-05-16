#pragma once

#include "quantum.h"

void send_unicode_hex_string(const char* str);

/* use X(n) to call the  */
#ifdef UNICODEMAP_ENABLE
enum unicode_name {
  THINK, // thinking face 🤔
  GRIN, // grinning face 😊
  SMRK, // smirk 😏
  WEARY, // good shit 😩
  UNAMU, // unamused 😒

  SNEK, // snke 🐍
  PENGUIN, // 🐧
  DRAGON, // 🐉
  MONKEY, // 🐒
  CHICK, // 🐥
  BOAR, // 🐗

  OKOK, // 👌
  EFFU, // 🖕
  INUP, // 👆
  THUP, // 👍
  THDN, // 👎

  BBB, // dat B 🅱
  POO, // poop 💩
  HUNDR, // 100 💯
  EGGPL, // EGGPLANT 🍆
  WATER, // wet 💦
  TUMBLER, // 🥃

  LIT, // fire 🔥
  BANG, // ‽
  IRONY, // ⸮
  DEGREE // °
};
#endif
