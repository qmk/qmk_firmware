# Keyball: Special Keycodes

* [English/英語](#english)
* [日本語/Japanese](#japanese)

<a id="english"></a>
## Special Keycodes

| Keycode    | Value on Remap  | Hex      | Description                                                       |
|:-----------|:----------------|:---------|:------------------------------------------------------------------|
| `KBC_RST`  | `Kb 0`          | `0x7e00` | Reset Keyball configuration[^1]                                   |
| `KBC_SAVE` | `Kb 1`          | `0x7e01` | Persist Keyball configuration[^1] to EEPROM                       |
| `CPI_I100` | `Kb 2`          | `0x7e02` | Increase 100 CPI (max 12000)                                      |
| `CPI_D100` | `Kb 3`          | `0x7e03` | Decrease 100 CPI (min 100)                                        |
| `CPI_I1K`  | `Kb 4`          | `0x7e04` | Increase 1000 CPI (max 12000)                                     |
| `CPI_D1K`  | `Kb 5`          | `0x7e05` | Decrease 1000 CPI (min 100)                                       |
| `SCRL_TO`  | `Kb 6`          | `0x7e06` | Toggle scroll mode                                                |
| `SCRL_MO`  | `Kb 7`          | `0x7e07` | Enable scroll mode when pressing                                  |
| `SCRL_DVI` | `Kb 8`          | `0x7e08` | Increase scroll divider (max D7 = 1/128) <- Most Scroll slow      |
| `SCRL_DVD` | `Kb 9`          | `0x7e09` | Decrease scroll divider (min 0 = 1/1) <- Most Scroll fast         |
| `AML_TO`   | `Kb 10`         | `0x7e0a` | Toggle automatic mouse layer                                      |
| `AML_I50`  | `Kb 11`         | `0x7e0b` | Increase 50ms automatic mouse layer timeout (max 1000ms)          |
| `AML_D50`  | `Kb 12`         | `0x7e0c` | Decrease 50ms automatic mouse layer timeout (min 100ms)           |
| `SSNP_VRT` | `Kb 13`         | `0x7e0d` | Set scroll snap mode as vertical                                  |
| `SSNP_HOR` | `Kb 14`         | `0x7e0e` | Set scroll snap mode as horizontal                                |
| `SSNP_FRE` | `Kb 15`         | `0x7e0f` | Set scroll snap mode as disable (free scroll)                     |

[^1]: CPI, scroll divider, automatic mouse layer's enable/disable, and automatic mouse layer's timeout.

<a id="japanese"></a>
## 特殊キーコード

| キーコード | Remap上での表記 | 値       | 説明                                                              |
|:-----------|:----------------|:---------|:------------------------------------------------------------------|
| `KBC_RST`  | `Kb 0`          | `0x7e00` | Keyball設定[^2]のリセット                                         |
| `KBC_SAVE` | `Kb 1`          | `0x7e01` | 現在のKeyball設定[^2]をEEPROMに保存します                         |
| `CPI_I100` | `Kb 2`          | `0x7e02` | CPIを100増加させます(最大:12000)                                  |
| `CPI_D100` | `Kb 3`          | `0x7e03` | CPIを100減少させます(最小:100)                                    |
| `CPI_I1K`  | `Kb 4`          | `0x7e04` | CPIを1000増加させます(最大:12000)                                 |
| `CPI_D1K`  | `Kb 5`          | `0x7e05` | CPIを1000減少させます(最小:100)                                   |
| `SCRL_TO`  | `Kb 6`          | `0x7e06` | タップごとにスクロールモードのON/OFFを切り替えます                |
| `SCRL_MO`  | `Kb 7`          | `0x7e07` | キーを押している間、スクロールモードになります                    |
| `SCRL_DVI` | `Kb 8`          | `0x7e08` | スクロール除数を１つ上げます(max D7 = 1/128)←最もスクロール遅い   |
| `SCRL_DVD` | `Kb 9`          | `0x7e09` | スクロール除数を１つ下げます(min D0 = 1/1)←最もスクロール速い     |
| `AML_TO`   | `Kb 10`         | `0x7e0a` | 自動マウスレイヤーをトグルします。                                |
| `AML_I50`  | `Kb 11`         | `0x7e0b` | 自動マウスレイヤーのタイムアウトを50msec増やします (max 1000ms)   |
| `AML_D50`  | `Kb 12`         | `0x7e0c` | 自動マウスレイヤーのタイムアウトを50msec減らします (min 100ms)    |
| `SSNP_VRT` | `Kb 13`         | `0x7e0d` | スクロールスナップモードを垂直にする                              |
| `SSNP_HOR` | `Kb 14`         | `0x7e0e` | スクロールスナップモードを水平にする                              |
| `SSNP_FRE` | `Kb 15`         | `0x7e0f` | スクロールスナップモードを無効にする(自由スクロール)              |

[^2]: CPI、スクロール除数、自動マウスレイヤーのON/OFF状態、及び自動マウスレイヤのタイムアウト
