# キーボードを Proton C を使うように変更 Converting a board to use the Proton C

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.9.46:docs/proton_c_conversion.md
  git diff 0.9.46 HEAD -- docs/proton_c_conversion.md | cat
-->

Since the Proton C is a drop-in replacement for a Pro Micro we've made it easy to use. This page documents a handy automated process for converting keyboards, as well as documenting the manual process if you'd like to make use of Proton C features that aren't available on Pro Micros.
Proton C は Pro Micro の差し替え可能品であるため、簡単に使用することができます。
このページでは、キーボードを変換するための便利な自動化されたプロセスと、Pro Micro では利用できない Proton C の機能を利用したい場合の手動プロセスについて説明しています。

## 自動で変換 Automatic Conversion

If a board currently supported in QMK uses a Pro Micro (or compatible board) and you want to use the Proton C, you can generate the firmware by appending `CONVERT_TO_PROTON_C=yes` (or `CTPC=yes`) to your make argument, like this:
QMK で現在サポートされているボードが Pro Micro（または互換ボード）を使用しており、Proton C を使用したい場合は、以下のように make 引数に `CONVERT_TO_PROTON_C=yes` (または `CTPC=yes`) を追加することでファームウェアを生成することができます。

    make 40percentclub/mf68:default CTPC=yes

You can add the same argument to your keymap's `rules.mk`, which will accomplish the same thing.
同じ引数をキーマップの `rules.mk` に追加しても同じことができます。

This exposes the `CONVERT_TO_PROTON_C` flag that you can use in your code with `#ifdef`s, like this:
これは、次のように、`＃ifdef` を使用してコード内で使用できる `CONVERT_TO_PROTON_C` フラグを公開します。

```c
#ifdef CONVERT_TO_PROTON_C
    // Proton C code
#else
    // Pro Micro code
#endif
```

If you get errors about `PORTB/DDRB`, etc not being defined, so you'll need to convert the keyboard's code to use the [GPIO Controls](internals_gpio_control.md) that will work for both ARM and AVR. This shouldn't affect the AVR builds at all.
`PORTB/DDRB` などが定義されていないというエラーが発生した場合は、ARM と AVR の両方で機能する [GPIO Controls]（internals_gpio_control.md）を使用するようにキーボードのコードを変換する必要があります。これは AVR ビルドにまったく影響を与えません。

The Proton C only has one on-board LED (C13), and by default, the TXLED (D5) is mapped to it. If you want the RXLED (B0) mapped to it instead, add this like to your `config.h`:
Proton C には1つのオンボードLED(C13)しかなく、デフォルトでは TXLED(D5) がそれにマップされています。代わりに RXLED(B0) をそれにマッピングしたい場合は、`config.h` に次のように追加してください。

    #define CONVERT_TO_PROTON_C_RXLED

## 機能の変換 Feature Conversion

These are defaults based on what has been implemented for ARM boards.
下記は ARM ボードに実装されているものに基づいたデフォルトです。

| 機能                                  | 説明                                                                               |
|--------------------------------------|------------------------------------------------------------------------------------|
| [オーディオ](ja/feature_audio.md)      | 有効                                                                      |
| [RGB ライト](ja/feature_rgblight.md)  | 無効                                                                       |
| [バックライト](feature_backlight.md)   | ARMが自動コンフィギュレーションを提供できるようになるまで、[タスク駆動 PWM](ja/(feature_backlight.md#software-pwm-driver))が強制されます |
| USB Host (e.g. USB-USB converter)   | 未サポート (USB ホストコードは AVR 固有のもので、現在 ARM ではサポートされていません。 |
| [分割キーボード](ja/feature_split_keyboard.md) | 部分的 - 有効にする機能に大きく依存する                                 |

## 手動で変換 Manual Conversion

To use the Proton C natively, without having to specify `CTPC=yes`, you need to change the `MCU` line in `rules.mk`:
`CTPC = yes` を指定せずに Proton C をネイティブで使用するには、`rules.mk` の `MCU`行を変更する必要があります：

```
MCU = STM32F303
```

Remove these variables if they exist:
次の変数が存在する場合は削除します。

* `BOOTLOADER`
* `EXTRA_FLAGS`

Finally convert all pin assignments in `config.h` to the stm32 equivalents.
最後に、`config.h`のすべてのピン割り当てを同等の stm32 に変換します。

| Pro Micro 左側| Proton C 左側 | | Proton C 右側 | Pro Micro 右側 |
|-----------|----------|-|----------|-----------|
| `D3` | `A9` | | 5v | RAW (5v) |
| `D2` | `A10` | | GND | GND |
| GND | GND | | FLASH | RESET |
| GND | GND | | 3.3v | VCC <sup>1</sup> |
| `D1` | `B7` | | `A2` | `F4` |
| `D0` | `B6` | | `A1` | `F5` |
| `D4` | `B5` | | `A0` | `F6` |
| `C6` | `B4` | | `B8` | `F7` |
| `D7` | `B3` | | `B13` | `B1` |
| `E6` | `B2` | | `B14` | `B3` |
| `B4` | `B1` | | `B15` | `B2` |
| `B5` | `B0` | | `B9` | `B6` |
| `B0` (RX LED) | `C13` <sup>2</sup> | | `C13` <sup>2</sup> | `D5` (TX LED) |

You can also make use of several new pins on the extended portion of the Proton C:
また、Proton C の拡張部分にあるいくつかの新しいピンを利用することもできます。


| 左側 | | 右側 |
|------|-|-------|
| `A4`<sup>3</sup> | | `B10` |
| `A5`<sup>4</sup> | | `B11` |
| `A6` | | `B12` |
| `A7` | | `A14`<sup>5</sup> (SWCLK) |
| `A8` | | `A13`<sup>5</sup> (SWDIO) |
| `A15` | | RESET<sup>6</sup> |

ノート:

1. On a Pro Micro VCC can be 3.3v or 5v.
1. Pro Micro の Vcc は 3.3V または 5V にすることができます。
2. A Proton C only has one onboard LED, not two like a Pro Micro. The Pro Micro has an RX LED on `D5` and a TX LED on `B0`.
2. Proton C のオンボード LED は、Pro Micro のように 2 つはありません、1つだけです。Pro Micro には、RX LED(`D5`) と TX LED(`B0`)があります。
3. `A4` is shared with the speaker.
3. `A4` ピンは、スピーカーと共有されています。
4. `A5` is shared with the speaker.
4. `A5` ピンは、スピーカーと共有されています。
5. `A13` and `A14` are used for hardware debugging (SWD). You can also use them for GPIO, but should use them last.
5. `A13` と `A14` ピンはハードウェアデバッグ (SWD) に使用されます。GPIO にも使えますが、最後に使ってください。
6. Short RESET to 3.3v (pull high) to reboot the MCU. This does not enter bootloader mode like a Pro Micro, it only resets the MCU.
6. RESET を 3.3V とショート(プルアップ)して MCU をリブートします。これは Pro Micro のようにブートローダモードにはならず、MCU をリセットするだけです。

