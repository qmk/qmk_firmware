# 触覚フィードバック

<!---
  original document: 0.8.123:docs/feature_haptic_feedback.md
  git diff 0.8.123 HEAD -- docs/feature_haptic_feedback.md | cat
-->

## 触覚フィードバック の rules.mk オプション

現在のところ、`rules.mk` で触覚フィードバック用に以下のオプションを利用可能です:

`HAPTIC_ENABLE += DRV2605L`

`HAPTIC_ENABLE += SOLENOID`

## サポートされる既知のハードウェア

| 名前 | 説明 |
|--------------------|-------------------------------------------------|
| [LV061228B-L65-A](https://www.digikey.com/product-detail/en/jinlong-machinery-electronics-inc/LV061228B-L65-A/1670-1050-ND/7732325) | z-axis 2v LRA |
| [ミニモーターディスク](https://www.adafruit.com/product/1201) | small 2-5v ERM |

## 触覚キーコード

以下のキーコードは、選択した触覚メカニズムに依存して動作するかどうか決まります。

| 名前 | 説明 |
|-----------|-------------------------------------------------------|
| `HPT_ON` | 触覚フィードバックをオン |
| `HPT_OFF` | 触覚フィードバックをオフ |
| `HPT_TOG` | 触覚フィードバックのオン/オフを切り替え |
| `HPT_RST` | 触覚フィードバック設定をデフォルトに戻す |
| `HPT_FBK` | キー押下またはリリースまたはその両方でフィードバックを切り替え |
| `HPT_BUZ` | ソレノイドの振動のオン/オフを切り替え |
| `HPT_MODI` | 次の DRV2605L 波形に移動 |
| `HPT_MODD` | 前の DRV2605L 波形に移動 |
| `HPT_CONT` | 継続的触覚モードのオン/オフを切り替え |
| `HPT_CONI` | DRV2605L の連続触覚強度を増加 |
| `HPT_COND` | DRV2605L の連続触覚強度を減少 |
| `HPT_DWLI` | ソレノイドの滞留時間を増加 |
| `HPT_DWLD` | ソレノイドの滞留時間を減少 |

### ソレノイド

最初に、ほとんどの MCU はソレノイドのコイルを駆動するために必要な電流を供給できないため、MOSFET を介してソレノイドを駆動する回路を構築する必要があります。

[Adafruit が提供する配線図](https://playground.arduino.cc/uploads/Learning/solenoid_driver.pdf)


| 設定 | デフォルト | 説明 |
|--------------------------|---------------|-------------------------------------------------------|
| `SOLENOID_PIN` | *定義なし* | ソレノイドが接続されているピンを設定する。 |
| `SOLENOID_DEFAULT_DWELL` | `12` ms | ソレノイドのデフォルトの滞留時間を設定する。 |
| `SOLENOID_MIN_DWELL` | `4` ms | 滞留時間の下限を設定する。 |
| `SOLENOID_MAX_DWELL` | `100` ms | 滞留時間の上限を設定する。 |

?> 滞留時間とは、「プランジャー」が作動したままになる時間です。滞留時間により、ソレノイドの音が変わります。

ブートローダ実行中に一部のピンが給電されているかもしれず (例えば、STM32F303 チップ上の A13)、そうすると書き込みプロセスの間ずっとソレノイドがオン状態になることに注意してください。これはソレノイドを加熱し損傷を与えるかもしれません。ソレノイドが接続されているピンがブートローダ/DFU 実行中にソレノイドをオンにしていることが分かった場合は、他のピンを選択してください。

### DRV2605L

DRV2605Lは i2c プロトコルで制御され、SDA および SCL ピンに接続する必要があります。これらは使用する MCU によって異なります。

#### フィードバックモータのセットアップ

このドライバは2つの異なるフィードバックモータをサポートします。選択したモータに基づいて、`config.h` で以下を設定します。

##### ERM

偏心回転質量振動モータ (ERM) はオフセット重量が取り付けられたモータで、駆動信号が取り付けられるとオフセット重量が回転し、振動に変換される正弦波が発生します。

```
#define FB_ERM_LRA 0
#define FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */

/* 特定のモータに最適な設定については、データシートを参照してください。*/
#define RATED_VOLTAGE 3
#define V_PEAK 5
```
##### LRA

線形共振アクチュエータ (LRA、線形バイブレータとしても知られています)は、ERM と異なります。LRA は重りと磁石をバネで吊るしたものとボイスコイルで構成されています。駆動信号が適用されると、重りは単一の軸で振動します (左右または上下)。重りはバネに取り付けられているため、特定の周波数で共振効果があります。この周波数は LRA が最も効率的に動作する箇所です。この周波数の推奨範囲については、モータのデータシートを参照してください。

```
#define FB_ERM_LRA 1
#define FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */

/* 特定のモータに最適な設定については、データシートを参照してください。*/
#define RATED_VOLTAGE 2
#define V_PEAK 2.8
#define V_RMS 2.0 
#define V_PEAK 2.1
#define F_LRA 205 /* 共振周波数 */
```

#### DRV2605L 波形ライブラリ

DRV2605L には呼び出して再生できる様々な波形シーケンスのプリロードライブラリが同梱されています。マクロを書く場合、これらの波形は `DRV_pulse(*sequence name or number*)` を使って再生することができます

データシートの波形シーケンスのテーマ

| seq# | シーケンス名 | seq# | シーケンス名 | seq# | シーケンス名 |
|-----|---------------------|-----|-----------------------------------|-----|--------------------------------------|
| 1 | strong_click | 43 | lg_dblclick_med_60 | 85 | transition_rampup_med_smooth2 |
| 2 | strong_click_60 | 44 | lg_dblsharp_tick | 86 | transition_rampup_short_smooth1 |
| 3 | strong_click_30 | 45 | lg_dblsharp_tick_80 | 87 | transition_rampup_short_smooth2 |
| 4 | sharp_click | 46 | lg_dblsharp_tick_60 | 88 | transition_rampup_long_sharp1 |
| 5 | sharp_click_60 | 47 | buzz | 89 | transition_rampup_long_sharp2 |
| 6 | sharp_click_30 | 48 | buzz_80 | 90 | transition_rampup_med_sharp1 |
| 7 | soft_bump | 49 | buzz_60 | 91 | transition_rampup_med_sharp2 |
| 8 | soft_bump_60 | 50 | buzz_40 | 92 | transition_rampup_short_sharp1 |
| 9 | soft_bump_30 | 51 | buzz_20 | 93 | transition_rampup_short_sharp2 |
| 10 | dbl_click | 52 | pulsing_strong | 94 | transition_rampdown_long_smooth1_50 |
| 11 | dbl_click_60 | 53 | pulsing_strong_80 | 95 | transition_rampdown_long_smooth2_50 |
| 12 | trp_click | 54 | pulsing_medium | 96 | transition_rampdown_med_smooth1_50 |
| 13 | soft_fuzz | 55 | pulsing_medium_80 | 97 | transition_rampdown_med_smooth2_50 |
| 14 | strong_buzz | 56 | pulsing_sharp | 98 | transition_rampdown_short_smooth1_50 |
| 15 | alert_750ms | 57 | pulsing_sharp_80 | 99 | transition_rampdown_short_smooth2_50 |
| 16 | alert_1000ms | 58 | transition_click | 100 | transition_rampdown_long_sharp1_50 |
| 17 | strong_click1 | 59 | transition_click_80 | 101 | transition_rampdown_long_sharp2_50 |
| 18 | strong_click2_80 | 60 | transition_click_60 | 102 | transition_rampdown_med_sharp1_50 |
| 19 | strong_click3_60 | 61 | transition_click_40 | 103 | transition_rampdown_med_sharp2_50 |
| 20 | strong_click4_30 | 62 | transition_click_20 | 104 | transition_rampdown_short_sharp1_50 |
| 21 | medium_click1 | 63 | transition_click_10 | 105 | transition_rampdown_short_sharp2_50 |
| 22 | medium_click2_80 | 64 | transition_hum | 106 | transition_rampup_long_smooth1_50 |
| 23 | medium_click3_60 | 65 | transition_hum_80 | 107 | transition_rampup_long_smooth2_50 |
| 24 | sharp_tick1 | 66 | transition_hum_60 | 108 | transition_rampup_med_smooth1_50 |
| 25 | sharp_tick2_80 | 67 | transition_hum_40 | 109 | transition_rampup_med_smooth2_50 |
| 26 | sharp_tick3_60 | 68 | transition_hum_20 | 110 | transition_rampup_short_smooth1_50 |
| 27 | sh_dblclick_str | 69 | transition_hum_10 | 111 | transition_rampup_short_smooth2_50 |
| 28 | sh_dblclick_str_80 | 70 | transition_rampdown_long_smooth1 | 112 | transition_rampup_long_sharp1_50 |
| 29 | sh_dblclick_str_60 | 71 | transition_rampdown_long_smooth2 | 113 | transition_rampup_long_sharp2_50 |
| 30 | sh_dblclick_str_30 | 72 | transition_rampdown_med_smooth1 | 114 | transition_rampup_med_sharp1_50 |
| 31 | sh_dblclick_med | 73 | transition_rampdown_med_smooth2 | 115 | transition_rampup_med_sharp2_50 |
| 32 | sh_dblclick_med_80 | 74 | transition_rampdown_short_smooth1 | 116 | transition_rampup_short_sharp1_50 |
| 33 | sh_dblclick_med_60 | 75 | transition_rampdown_short_smooth2 | 117 | transition_rampup_short_sharp2_50 |
| 34 | sh_dblsharp_tick | 76 | transition_rampdown_long_sharp1 | 118 | long_buzz_for_programmatic_stopping |
| 35 | sh_dblsharp_tick_80 | 77 | transition_rampdown_long_sharp2 | 119 | smooth_hum1_50 |
| 36 | sh_dblsharp_tick_60 | 78 | transition_rampdown_med_sharp1 | 120 | smooth_hum2_40 |
| 37 | lg_dblclick_str | 79 | transition_rampdown_med_sharp2 | 121 | smooth_hum3_30 |
| 38 | lg_dblclick_str_80 | 80 | transition_rampdown_short_sharp1 | 122 | smooth_hum4_20 |
| 39 | lg_dblclick_str_60 | 81 | transition_rampdown_short_sharp2 | 123 | smooth_hum5_10 |
| 40 | lg_dblclick_str_30 | 82 | transition_rampup_long_smooth1 |  |  |
| 41 | lg_dblclick_med | 83 | transition_rampup_long_smooth2 |  |  |
| 42 | lg_dblclick_med_80 | 84 | transition_rampup_med_smooth1 |  |  |
### Optional DRV2605L defines

```
#define DRV_GREETING *sequence name or number*
```
触覚フィードバッグは有効な場合、キーボード起動時に特定のシーケンスに合わせて振動します。以下の定義を使って選択することができます:

```
#define DRV_MODE_DEFAULT *sequence name or number*
```
これにより HPT_RST がアクティブモードとして設定するシーケンスを設定します。未定義の場合、HPT_RST が押された時にモードが 1 に設定されます。

### DRV2605L 継続的触覚モード

このモードは強さを増減するオプションを使って継続的な触覚フィードバッグを設定します。
