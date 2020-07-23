# エンコーダ

<!---
  original document: 0.8.123:docs/feature_encoders.md
  git diff 0.8.123 HEAD -- docs/feature_encoders.md | cat
-->

以下を `rules.mk` に追加することで基本的なエンコーダがサポートされます:

```make
ENCODER_ENABLE = yes
```

さらに、以下を `config.h` に追加します:

```c
#define ENCODERS_PAD_A { B12 }
#define ENCODERS_PAD_B { B13 }
```

各 PAD_A/B 変数は配列を定義するため、複数のエンコーダを定義することができます。例えば:

```c
#define ENCODERS_PAD_A { encoder1a, encoder2a }
#define ENCODERS_PAD_B { encoder1b, encoder2b }
```

エンコーダの時計回りの方向が間違っている場合は、A と B のパッド定義を交換することができます。define を使って逆にすることもできます:

```c
#define ENCODER_DIRECTION_FLIP
```

さらに、解像度を同じファイルで指定することができます (デフォルトかつお勧めは4):

```c
#define ENCODER_RESOLUTION 4
```

## 分割キーボード

分割キーボードのそれぞれの側のエンコーダに異なるピン配列を使っている場合、右側のピン配列を以下のように定義することができます:

```c
#define ENCODERS_PAD_A_RIGHT { encoder1a, encoder2a }
#define ENCODERS_PAD_B_RIGHT { encoder1b, encoder2b }
```

## コールバック

コールバック関数を `<keyboard>.c` に記述することができます:

```c
void encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_update_user(index, clockwise);
}
```

あるいは `keymap.c` に記述することもできます:

```c
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
}
```

## ハードウェア

エンコーダの A と B の線は MCU に直接配線し、C/common 線はグランドに配線する必要があります。
