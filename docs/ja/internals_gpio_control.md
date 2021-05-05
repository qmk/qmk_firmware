# GPIO 制御 :id=gpio-control

<!---
  original document: 0.9.34:docs/internals_gpio_control.md
  git diff 0.9.34 HEAD -- docs/internals_gpio_control.md | cat
-->

QMK には、マイクロコントローラに依存しない GPIO 制御抽象レイヤーがあります。これは異なるプラットフォーム間でピン制御に簡単にアクセスできるようにするためのものです。

## 関数 :id=functions

以下の関数は GPIO の基本的な制御を提供し、`quantum/quantum.h` にあります。

| 関数 | 説明 | 古い AVR の例 | 古い ChibiOS/ARM の例 |
|------------------------|--------------------------------------------------|-------------------------------------------------|-------------------------------------------------|
| `setPinInput(pin)` | ピンを高インピーダンス(High-Z)の入力として設定 | `DDRB &= ~(1<<2)` | `palSetLineMode(pin, PAL_MODE_INPUT)` |
| `setPinInputHigh(pin)` | ピンを組み込みのプルアップ抵抗付きの入力として設定 | `DDRB &= ~(1<<2); PORTB \|= (1<<2)` | `palSetLineMode(pin, PAL_MODE_INPUT_PULLUP)` |
| `setPinInputLow(pin)` | ピンを組み込みのプルダウン抵抗付きの入力として設定 | N/A (AVR ではサポートされません) | `palSetLineMode(pin, PAL_MODE_INPUT_PULLDOWN)` |
| `setPinOutput(pin)` | ピンを出力として設定 | `DDRB \|= (1<<2)` | `palSetLineMode(pin, PAL_MODE_OUTPUT_PUSHPULL)` |
| `writePinHigh(pin)` | ピンレベルを high に設定 (ピンを出力として設定してあると仮定) | `PORTB \|= (1<<2)` | `palSetLine(pin)` |
| `writePinLow(pin)` | ピンレベルを low に設定 (ピンを出力として設定してあると仮定) | `PORTB &= ~(1<<2)` | `palClearLine(pin)` |
| `writePin(pin, level)` | ピンレベルを設定 (ピンを出力として設定してあると仮定) | `(level) ? PORTB \|= (1<<2) : PORTB &= ~(1<<2)` | `(level) ? palSetLine(pin) : palClearLine(pin)` |
| `readPin(pin)` | ピンのレベルを返す | `_SFR_IO8(pin >> 4) & _BV(pin & 0xF)` | `palReadLine(pin)` |
| `togglePin(pin)` | ピンレベルを反転 (ピンを出力として設定してあると仮定) | `PORTB ^= (1<<2)` | `palToggleLine(pin)` |

## 高度な設定 :id=advanced-settings

各マイクロコントローラは GPIO に関して複数の高度な設定を持つことができます。この抽象レイヤーは、アーキテクチャー固有の機能の使用法を制限しません。上級ユーザは、目的のデバイスのデータシートを参照し、必要なライブラリを含めてください。AVR については、標準 avr/io.h ライブラリが使われます; STM32 については ChibiOS [PAL ライブラリ](https://chibios.sourceforge.net/docs3/hal/group___p_a_l.html)が使われます。
