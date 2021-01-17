# 'シリアル' ドライバ

<!---
  original document: 0.9.51:docs/serial_drive.md
  git diff 0.9.51 HEAD -- docs/serial_drive.md | cat
-->

このドライバは[分割キーボード](ja/feature_split_keyboard.md) 機能に使います。

?> この文章でのシリアルは、UART/USART/RS485/RS232 規格の実装ではなく、**一度に1ビットの情報を送信するもの**として読まれるべきです。

このカテゴリの全てのドライバには以下の特徴があります:
* 1本の線上でデータと信号を提供
* シングルマスタ、シングルスレーブに限定

## サポートされるドライバの種類

|                   | AVR                | ARM                |
|-------------------|--------------------|--------------------|
| bit bang          | :heavy_check_mark: | :heavy_check_mark: |
| USART Half-duplex |                    | :heavy_check_mark: |

## ドライバ設定

### Bitbang
デフォルトのドライバ。設定がない場合はこのドライバが想定されます。設定するには、以下を rules.mk に追加します:

```make
SERIAL_DRIVER = bitbang
```

config.h を介してドライバを設定します:
```c
#define SOFT_SERIAL_PIN D0  // または D1, D2, D3, E6
#define SELECT_SOFT_SERIAL_SPEED 1 // または 0, 2, 3, 4, 5
                                   //  0: 約 189kbps (実験目的のみ)
                                   //  1: 約 137kbps (デフォルト)
                                   //  2: 約 75kbps
                                   //  3: 約 39kbps
                                   //  4: 約 26kbps
                                   //  5: 約 20kbps
```

#### ARM

!> bitbang ドライバは bitbang WS2812 ドライバと接続の問題があります

上記の一般的なオプションに加えて、halconf.h で `PAL_USE_CALLBACKS` 機能もオンにする必要があります。

### USART Half-duplex
通信が USART ハードウェアデバイスに送信される STM32 ボードが対象です。これにより高速で正確なタイミングを提供できることが利点です。このドライバの `SOFT_SERIAL_PIN` は、設定された USART TX ピンです。**TX ピンに適切なプルアップ抵抗が必要です**。設定するには、以下を rules.mk に追加します:

```make
SERIAL_DRIVER = usart
```

config.h を介してハードウェアを設定します:
```c
#define SOFT_SERIAL_PIN B6  // USART TX ピン
#define SELECT_SOFT_SERIAL_SPEED 1 // または 0, 2, 3, 4, 5
                                   //  0: 約 460800 ボー
                                   //  1: 約 230400 ボー (デフォルト)
                                   //  2: 約 115200 ボー
                                   //  3: 約 57600 ボー
                                   //  4: 約 38400 ボー
                                   //  5: 約 19200 ボー
#define SERIAL_USART_DRIVER SD1 // TX ピンの USART ドライバ。デフォルトは SD1
#define SERIAL_USART_TX_PAL_MODE 7 // 「代替機能」 ピン。MCU の適切な値については、それぞれのデータシートを見てください。デフォルトは 7
```

また、ChibiOS `SERIAL` 機能を有効にする必要があります:
* キーボードの halconf.h: `#define HAL_USE_SERIAL TRUE`
* キーボードの mcuconf.h: `#define STM32_SERIAL_USE_USARTn TRUE` (ここで、'n' は MCU で選択した USART のペリフェラル番号と一致)

必要な構成は、`UART` 周辺機器ではなく、`SERIAL` 周辺機器であることに注意してください。
