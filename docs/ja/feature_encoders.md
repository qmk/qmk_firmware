# エンコーダ

<!---
  original document: 0.14.14:docs/feature_encoders.md
  git diff 0.14.14 HEAD -- docs/feature_encoders.md | cat
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

さらに、エンコーダが各戻り止め(デテント)間に登録するパルス数を定義する解像度は、次のように定義できます:

```c
#define ENCODER_RESOLUTION 4
```

エンコーダごとに定義することも可能で、その場合は以下のように定義します:

```c
#define ENCODER_RESOLUTIONS { 4, 2 }
```

4× エンコーダの場合、エンコーダが方向を変える時にパルスをスキップする場合のデフォルトの位置を割り当てることもできます。例えば、エンコーダがデフォルトで両方のピンでハイレベルを送信する場合は、以下のように定義します:

```c
#define ENCODER_DEFAULT_POS 0x3
```

## 分割キーボード

分割キーボードのそれぞれの側のエンコーダに異なるピン配列を使っている場合、右側のピン配列(およびオプションで解像度)を以下のように定義することができます:

```c
#define ENCODERS_PAD_A_RIGHT { encoder1a, encoder2a }
#define ENCODERS_PAD_B_RIGHT { encoder1b, encoder2b }
#define ENCODER_RESOLUTIONS_RIGHT { 2, 4 }
```

## コールバック

コールバック関数を `<keyboard>.c` に記述することができます:

```c
bool encoder_update_kb(uint8_t index, bool clockwise) {
    return encoder_update_user(index, clockwise);
}
```

あるいは `keymap.c` に記述することもできます:

```c
bool encoder_update_user(uint8_t index, bool clockwise) {
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
    return true;
}
```

!> `true` を返すと、キーボードレベルのコードも実行できるようになります。`false` を返すと、キーボードレベルのコードが上書きされます。キーボードレベルの関数がどのように設定されているかに依ります。

## ハードウェア

エンコーダの A と B の線は MCU に直接配線し、C/common 線はグランドに配線する必要があります。

## 複数のエンコーダ

複数のエンコーダでピンを共有できますが、各エンコーダが異なるピンのペアを持つ必要があります。

例えば、以下のように3つのピンだけを使って2つのエンコーダをサポートできます
```
#define ENCODERS_PAD_A { B1, B1 }
#define ENCODERS_PAD_B { B2, B3 }
```

3つのピンだけを使って3つのエンコーダをサポート(エンコーダごとに1つのピン)することもできますが、この構成ではピンを共有する2つのエンコーダを同時に回転させると、誤った出力が生成されることがよくあります。例えば:
```
#define ENCODERS_PAD_A { B1, B1, B2 }
#define ENCODERS_PAD_B { B2, B3, B3 }
```
この時、エンコーダ 0 の `B1 B2` とエンコーダ 1 の `B1 B3` は、タイミングによっては、エンコーダ 2 の `B2 B3` や `B3 B2` の回転と解釈できます。これでも、ユースケースによっては便利な構成かもしれません。
