# エンコーダ

これを`rules.mk`に追加することで基本的なエンコーダがサポートされます:

    ENCODER_ENABLE = yes

以下を`config.h`に追加します:

    #define ENCODERS_PAD_A { B12 }
    #define ENCODERS_PAD_B { B13 }

各 PAD_A/B 変数は配列を定義するため、複数のエンコーダを定義することができます。例えば:

    #define ENCODERS_PAD_A { encoder1a, encoder2a }
    #define ENCODERS_PAD_B { encoder1b, encoder2b }

エンコーダの時計回りの方向が間違っている場合は、A & B パッド定義を交換することができます。

さらに、解像度は同じファイルで指定することができます (デフォルト & お勧めは4):

    #define ENCODER_RESOLUTION 4

## 分割キーボード

分割キーボードの各半分のエンコーダに異なるピン配列を使っている場合、右半分のピン配列を以下のように定義することができます:

```c
#define ENCODERS_PAD_A_RIGHT { encoder1a, encoder2a }
#define ENCODERS_PAD_B_RIGHT { encoder1b, encoder2b }
```

## コールバック

コールバック関数を`<keyboard>.c`に挿入することができます:

    void encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_update_user(index, clockwise);
    }

あるいは `keymap.c`:

    void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
    if (clockwise) {
    tap_code(KC_PGDN);
    } else {
    tap_code(KC_PGUP);
    }
    } else if (index == 1) { /* Second encoder */
    if (clockwise) {
    tap_code(KC_UP);
    } else {
    tap_code(KC_DOWN);
    }
    }
    }

## ハードウェア

エンコーダの A および B のラインはMCUに直接配線し、C/common ラインはグランドに配線する必要があります。
