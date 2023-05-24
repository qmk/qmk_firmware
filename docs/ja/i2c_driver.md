# I2C マスタドライバ :id=i2c-master-driver

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.10.33:docs/i2c_driver.md
  git diff 0.10.33 HEAD -- docs/i2c_driver.md | cat
-->

QMK で使われる I2C マスタドライバには、MCU 間のポータビリティを提供するための一連の関数が用意されています。

## I2C アドレスについての重要なメモ :id=note-on-i2c-addresses

このドライバが期待する全てのアドレスは、アドレスバイトの上位7ビットにプッシュする必要があります。最下位ビットの設定(読み込み/書き込みを示す)は、それぞれの関数によって行われます。データシートやインターネットで列挙されているほとんど全ての I2C アドレスは、下位7ビットを占める7ビットとして表され、1ビット左(より上位)にシフトする必要があります。これは、ビット単位のシフト演算子 `<< 1` を使用して簡単に実行できます。

これは、呼び出しごとに以下の関数を実行するか、アドレスの定義で1度だけ実行するかどちらかで行うことができます。例えば、デバイスのアドレスが `0x18` の場合:

`#define MY_I2C_ADDRESS (0x18 << 1)`

I2C アドレスと他の技術詳細について、さらなる情報を得るためには https://www.robot-electronics.co.uk/i2c-tutorial を見てください。

## 使用できる関数 :id=available-functions

| 関数                                                                                                        | 説明                                                                                                                                                                                |
|-------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `void i2c_init(void);`                                                                                      | I2C ドライバを初期化します。他のあらゆるトランザクションを開始する前に、この関数を一度だけ呼ぶ必要があります。                                                                      |
| `i2c_status_t i2c_start(uint8_t address, uint16_t timeout);`                                                     | I2C トランザクションを開始します。アドレスは方向ビットのない7ビットスレーブアドレスです。                                                                                           |
| `i2c_status_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);`                  | I2C 経由でデータを送信します。アドレスは方向ビットのない7ビットスレーブアドレスです。トランザクションのステータスを返します。                                                       |
| `i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);`                   | I2C 経由でデータを受信します。アドレスは方向ビットのない7ビットスレーブアドレスです。 `length` で指定した長さのバイト列を `data` に保存し、トランザクションのステータスを返します。 |
| `i2c_status_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);` | `i2c_transmit` と同様ですが、 `regaddr` でスレーブのデータ書き込み先のレジスタを指定します。                                                                                    |
| `i2c_status_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);`  | `i2c_receive` と同様ですが、 `regaddr` でスレーブのデータ読み込み先のレジスタを指定します。                                                                                     |
| `i2c_status_t i2c_stop(void);`                                                                                   | I2C トランザクションを終了します。                                                                                                                                                  |

### 関数の戻り値 :id=function-return

`void i2c_init(void)` を除く上にあるすべての関数は、次の真理値表にある値を返します。

|戻り値の定数        |値 |説明                        |
|--------------------|---|----------------------------|
|`I2C_STATUS_SUCCESS`|0  |処理が正常に実行されました。|
|`I2C_STATUS_ERROR`  |-1 |処理に失敗しました。        |
|`I2C_STATUS_TIMEOUT`|-2 |処理がタイムアウトしました。|

## AVR :id=avr

### 設定 :id=avr-configuration

I2Cマスタドライバを設定するために、次の定義が使えます。

| 変数    | 説明                | 既定値 |
|---------|---------------------|--------|
| `F_SCL` | クロック周波数 (Hz) | 400KHz |


AVR は通常 I2C ピンとして使う GPIO が設定されているので、これ以上の設定は必要ありません。

## ARM :id=arm

ARM の場合は、内部に ChibiOS I2C HAL ドライバがあります。この節では STM32 MCU を使用していると仮定します。

### 設定 :id=arm-configuration

ARM MCU 用の設定はしばしば非常に複雑です。これは、多くの場合複数の I2C ドライバをさまざまなポートに対して割り当てられるためです。

最初に、必要なハードウェアドライバを有効にするために `mcuconf.h` ファイルをセットアップします。

| 変数                          | 説明                                                                                           | 既定値 |
|-------------------------------|------------------------------------------------------------------------------------------------|--------|
| `#STM32_I2C_USE_XXX`          | ハードウェアドライバ XXX の有効化/無効化（すべてのドライバを明示的にリストアップする必要あり） | FALSE  |
| `#STM32_I2C_BUSY_TIMEOUT`     | レスポンスの受信がない場合に I2C コマンドを中断するまでの時間 (ms)                             | 50     |
| `#STM32_I2C_XXX_IRQ_PRIORITY` | ハードウェアドライバ XXX の割り込み優先度（上級者向けの設定）                                  | 10     |
| `#STM32_I2C_USE_DMA`          | MCU がデータ送信を DMA ユニットにオフロードする機能の有効化/無効化                             | TRUE   |
| `#STM32_I2C_XXX_DMA_PRIORITY` | ハードウェアドライバ XXX に使用する DMA ユニットの優先度（上級者向けの設定）                   | 1      |

次に `halconf.h` ファイル内で `#define HAL_USE_I2C` を `TRUE` にします。これにより ChibiOS が I2C ドライバを読み込みます。

最後に、使用したい I2C ハードウェアドライバに応じて正しい GPIO ピンを割り当てます。

標準では I2C1 ハードウェアドライバが使われます。もし他のハードウェアドライバを使う場合、 `config.h` ファイルに `#define I2C_DRIVER I2CDX` を追加します（ X は使用するハードウェアドライバの番号です）。例えば I2C3 を有効化する場合、`config.h` ファイルに `#define I2C_DRIVER I2CD3` と定義します。これにより QMK I2C ドライバと ChibiOS I2C driver が同期されます。

STM32 MCU では、使用するハードウェアドライバにより、さまざまなピンを I2C ピンとして設定できます。標準では `B6`, `B7` ピンが I2C 用のピンです。 I2C 用のピンを設定するために次の定義が使えます：

| 変数                  | 説明                                                                                      | 既定値  |
|-----------------------|-------------------------------------------------------------------------------------------|---------|
| `I2C1_SCL_PIN`        | SCL のピン番号                                                                            | `B6`    |
| `I2C1_SDA_PIN`        | SDA のピン番号                                                                            | `B7`    |

ChibiOS I2C ドライバの設定項目は STM32 MCU の種類に依存します。

    STM32F1xx, STM32F2xx, STM32F4xx, STM32L0xx, STM32L1xx では I2Cv1 が使われます。
    STM32F0xx, STM32F3xx, STM32F7xx, STM32L4xx では I2Cv2 が使われます。

#### I2Cv1 :id=i2cv1

STM32 MCU の I2Cv1 では、クロック周波数とデューティ比を次の変数で変更できます。詳しくは <https://www.playembedded.org/blog/stm32-i2c-chibios/#I2Cv1_configuration_structure> を参照してください。

| 変数               | 既定値           |
|--------------------|------------------|
| `I2C1_OPMODE`      | `OPMODE_I2C`     |
| `I2C1_CLOCK_SPEED` | `100000`         |
| `I2C1_DUTY_CYCLE`  | `STD_DUTY_CYCLE` |

#### I2Cv2 :id=i2cv2

STM32 MCU の I2Cv2 では、信号のタイミングパラメータを次の変数で変更できます。詳しくは <https://www.st.com/en/embedded-software/stsw-stm32126.html> を参照してください。

| 変数                  | 既定値 |
|-----------------------|--------|
| `I2C1_TIMINGR_PRESC`  | `15U`  |
| `I2C1_TIMINGR_SCLDEL` | `4U`   |
| `I2C1_TIMINGR_SDADEL` | `2U`   |
| `I2C1_TIMINGR_SCLH`   | `15U`  |
| `I2C1_TIMINGR_SCLL`   | `21U`  |

STM32 MCU では GPIO ピンを設定するとき、別の「代替機能」モードを使うことができます。これは I2Cv2 モードで使われるピンを変更するために必要です。適切な設定値は、使用している MCU のデータシートを参照してください。

| 変数                | 既定値 |
|---------------------|--------|
| `I2C1_SCL_PAL_MODE` | `4`    |
| `I2C1_SDA_PAL_MODE` | `4`    |

#### その他 :id=other

`void i2c_init(void)` 関数は `weak` 属性が付いており、オーバーロードすることができます。この場合、上記で設定した変数は使用されません。可能な GPIO の設定については、 MCU のデータシートを参照してください。次に示すのは初期化関数の例です：

```c
void i2c_init(void)
{
  setPinInput(B6); // Try releasing special pins for a short time
  setPinInput(B7);
  wait_ms(10); // Wait for the release to happen

  palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B6 to I2C function
  palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B7 to I2C function
}
```
