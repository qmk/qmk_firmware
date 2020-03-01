# I2C マスタドライバ

<!-- The I2C Master drivers used in QMK have a set of common functions to allow portability between MCUs. -->

QMK で使われる I2C マスタドライバには、MCU間のポータビリティを提供するための一連の関数が用意されています。


<!-- ## Available functions -->

## 使用できる関数

|関数                                                                                                          |説明                                                                                                                                                                  |
|------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|`void i2c_init(void);`                                                                                            |<!--Initializes the I2C driver. This function should be called once before any transaction is initiated. -->I2Cドライバを初期化します。〔他の〕あらゆるトランザクションを開始する前に、この関数を一度だけ呼ぶ必要があります。                                                                        |
|`uint8_t i2c_start(uint8_t address, uint16_t timeout);`                                                                             |<!--Starts an I2C transaction. Address is the 7-bit slave address without the direction bit.-->I2Cトランザクションを開始します。アドレスは方向ビットのない7bitスレーブアドレスです。                                                                                    |
|`uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);`                        |<!--Transmit data over I2C. Address is the 7-bit slave address without the direction. Returns status of transaction.-->I2C経由でデータを送信します。アドレスは方向ビットのない7bitスレーブアドレスです。トランザクションのステータスを返します。                                                             |
|`uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);`                         |<!--Receive data over I2C. Address is the 7-bit slave address without the direction. Saves number of bytes specified by `length` in `data` array. Returns status of transaction.-->I2C経由でデータを受信します。アドレスは方向ビットのない7bitスレーブアドレスです。 `length` で指定した長さのバイト列を `data` に保存し、トランザクションのステータスを返します。 |
|`uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);`       |<!--Same as the `i2c_transmit` function but `regaddr` sets where in the slave the data will be written.-->`i2c_transmit` と同様ですが、`regaddr` でスレーブのデータ書き込み先〔のレジスタ〕を指定します。                                                                          |
|`uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);`        |<!--Same as the `i2c_receive` function but `regaddr` sets from where in the slave the data will be read.-->`i2c_receive` と同様ですが、`regaddr` でスレーブのデータ読み込み先〔のレジスタ〕を指定します。                                                                        |
|`uint8_t i2c_stop(void);`                                                                                         |<!--Ends an I2C transaction.-->I2Cトランザクションを終了します。                                                                                                                                                     |


<!--### Function Return-->
### 関数の戻り値

<!--All the above functions, except `void i2c_init(void);` return the following truth table:-->

`void i2c_init(void)` を除く上にあるすべての関数は、次の真理値表にある値を返します。

|戻り値   |説明                                        |
|---------------|---------------------------------------------------|
|0              |<!--Operation executed successfully.-->処理が正常に実行されました。                   |
|-1             |<!--Operation failed.-->処理に失敗しました。                                  |
|-2             |<!--Operation timed out.-->処理がタイムアウトしました。                               |


## AVR

<!--### Configuration-->
### 設定

<!--The following defines can be used to configure the I2C master driver.
-->
I2Cマスタドライバを設定するために、次の定義が使えます。

|変数          |説明                                        |既定値|
|------------------|---------------------------------------------------|-------|
|`F_SCL`           |<!-- Clock frequency in Hz -->クロック周波数 (Hz)                              |400KHz |

<!-- AVRs usually have set GPIO which turn into I2C pins, therefore no further configuration is required. -->
AVR は通常 I2C ピンとして使う GPIO が設定されているので、これ以上の設定は必要ありません。

## ARM

<!-- For ARM the Chibios I2C HAL driver is under the hood.
This section assumes an STM32 MCU. -->

ARM の場合は、裏で ChibiOS I2C HAL ドライバが使われます。この節では STM32 を使用していると仮定します。

### 設定

<!-- The configuration for ARM MCUs can be quite complex as often there are multiple I2C drivers which can be assigned to a variety of ports.

Firstly the `mcuconf.h` file must be setup to enable the necessary hardware drivers. -->

ARM MCU 用の設定はしばしば非常に複雑です。これは、多くの場合複数の I2C ドライバをさまざまなポートに対して割り当てられるためです。

最初に、必要なハードウェアドライバを有効にするために `mcuconf.h` をセットアップします。

|変数                      |説明                                                                        |既定値|
|------------------------------|------------------------------------------------------------------------------------|-------|
|`#STM32_I2C_USE_XXX`          |<!-- Enable/Disable the hardware driver XXX (each driver should be explicitly listed) -->ハードウェアドライバ XXX の有効化/無効化（すべてのドライバを明示的にリストアップする必要あり） |FALSE  |
|`#STM32_I2C_BUSY_TIMEOUT`     |<!-- Time in ms until the I2C command is aborted if no response is received -->レスポンスの受信がない場合に I2C コマンドを強制終了するまでの時間 (ms) |50     |
|`#STM32_I2C_XXX_IRQ_PRIORITY` |<!-- Interrupt priority for hardware driver XXX (THIS IS AN EXPERT SETTING) -->ハードウェアドライバ XXX の割り込み優先度（上級者向け） |10     |
|`#STM32_I2C_USE_DMA`          |<!-- Enable/Disable the ability of the MCU to offload the data transfer to the DMA unit -->MCUがデータ送信をDMAユニットにオフロードする機能の有効化/無効化 |TRUE   |
|`#STM32_I2C_XXX_DMA_PRIORITY` |<!-- Priority of DMA unit for hardware driver XXX (THIS IS AN EXPERT SETTING) -->ハードウェアドライバ XXX に使用する DMA ユニットの優先度（上級者向け）            |1      |

<!-- Secondly。 in the `halconf.h` file, `#define HAL_USE_I2C` must be set to `TRUE`. This allows ChibiOS to load its I2C driver. -->
次に `halconf.h` 内で `#define HAL_USE_I2C` を `TRUE` にします。これにより ChibiOS が I2C ドライバを読み込みます。

<!-- Lastly, we need to assign the correct GPIO pins depending on the I2C hardware driver we want to use. -->
最後に、使用したい I2C ハードウェアドライバに応じて正しい GPIO ピンを割り当てます。

<!-- By default the I2C1 hardware driver is assumed to be used. If another hardware driver is used,  `#define I2C_DRIVER I2CDX` should be added to the `config.h` file with X being the number of hardware driver used. For example is I2C3 is enabled, the `config.h` file should contain `#define I2C_DRIVER I2CD3`. This aligns the QMK I2C driver with the Chibios I2C driver. -->
標準では I2C1 ハードウェアドライバが使われます。もし他のハードウェアドライバを使う場合、 `config.h` に `#define I2C_DRIVER I2CDX` を追加します（ X は使用するハードウェアドライバの番号です）。例えば I2C3 を有効化する場合、`config.h` に `#define I2C_DRIVER I2CD3` と定義します。これにより QMK I2C ドライバと ChibiOS I2C driver が同期されます。

<!-- STM32 MCUs allows a variety of pins to be configured as I2C pins depending on the hardware driver used. By default B6 and B7 are set to I2C. You can use these defines to set your i2c pins: -->
STM32 MCU では、使用するハードウェアドライバにより、さまざまなピンを I2C ピンとして設定できます。標準では `B6`, `B7` ピンが I2C 用のピンです。I2C 用のピンを設定するために次の定義が使えます：

| 変数                 | 説明                                                                                  | 既定値 |
|--------------------------|----------------------------------------------------------------------------------------------|---------|
| `I2C1_SCL_BANK`          |<!-- The bank of pins (`GPIOA`, `GPIOB`, `GPIOC`) to use for SCL --> SCLに使うピンのバンク (`GPIOA`, `GPIOB`, `GPIOC`)                                  | `GPIOB` |
| `I2C1_SDA_BANK`          |<!-- The bank of pins (`GPIOA`, `GPIOB`, `GPIOC`) to use for SDA --> SDAに使うピンのバンク (`GPIOA`, `GPIOB`, `GPIOC`)                                  | `GPIOB` |
| `I2C1_SCL`               |<!-- The pin number for the SCL pin (0-9) --> SCL のピン番号 (0-9)                                                         | `6`     |
| `I2C1_SDA`               |<!-- The pin number for the SDA pin (0-9) --> SDA のピン番号 (0-9)                                                         | `7`     |
| `I2C1_BANK` <!-- (deprecated) -->(非推奨) | <!-- The bank of pins (`GPIOA`, `GPIOB`, `GPIOC`), superceded by `I2C1_SCL_BANK`, `I2C1_SDA_BANK` --> `GPIOA`, `GPIOB`, `GPIOC` で使用するピンのバンク。 `I2C1_SCL_BANK`, `I2C1_SDA_BANK` を推奨。 | `GPIOB` |

<!-- The ChibiOS I2C driver configuration depends on STM32 MCU: -->
<!--     STM32F1xx, STM32F2xx, STM32F4xx, STM32L0xx and STM32L1xx use I2Cv1; -->
<!--     STM32F0xx, STM32F3xx, STM32F7xx and STM32L4xx use I2Cv2; -->

ChibiOS I2C ドライバの設定項目は STM32 MCU の種類に依存します。

    STM32F1xx, STM32F2xx, STM32F4xx, STM32L0xx, STM32L1xx では I2Cv1 が使われます。
    STM32F0xx, STM32F3xx, STM32F7xx, STM32L4xx では I2Cv2 が使われます。

#### I2Cv1

<!-- STM32 MCUs allow for different clock and duty parameters when configuring I2Cv1. These can be modified using the following parameters, using <https://www.playembedded.org/blog/stm32-i2c-chibios/#I2Cv1_configuration_structure> as a reference: -->

STM32 の I2Cv1 では、クロック周波数とデューティ比を次の変数で変更できます。詳しくは <https://www.playembedded.org/blog/stm32-i2c-chibios/#I2Cv1_configuration_structure> を参照してください。

| 変数                | 既定値             |
|--------------------|------------------|
| `I2C1_OPMODE`      | `OPMODE_I2C`     |
| `I2C1_CLOCK_SPEED` | `100000`         |
| `I2C1_DUTY_CYCLE`  | `STD_DUTY_CYCLE` |

#### I2Cv2

<!--STM32 MCUs allow for different timing parameters when configuring I2Cv2. These can be modified using the following parameters, using <https://www.st.com/en/embedded-software/stsw-stm32126.html> as a reference:-->

STM32 の I2Cv2 では、信号のタイミングパラメタを次の変数で変更できます。詳しくは <https://www.st.com/en/embedded-software/stsw-stm32126.html> を参照してください。

| 変数                   | 既定値    |
|-----------------------|---------|
| `I2C1_TIMINGR_PRESC`  | `15U`   |
| `I2C1_TIMINGR_SCLDEL` | `4U`    |
| `I2C1_TIMINGR_SDADEL` | `2U`    |
| `I2C1_TIMINGR_SCLH`   | `15U`   |
| `I2C1_TIMINGR_SCLL`   | `21U`   |

<!-- STM32 MCUs allow for different "alternate function" modes when configuring GPIO pins. These are required to switch the pins used to I2Cv2 mode. See the respective datasheet for the appropriate values for your MCU. -->

STM32 MCU では GPIO ピンを設定するとき、別の「オルタネート機能」モードを使うことができます。これは I2Cv2 モードで使われるピンを変更するために必要です。適切な設定値は、使用している MCU のデータシートを参照してください。

<!-- PAL = Port Abstraction Layer -->

| 変数                 | 既定値    |
|---------------------|---------|
| `I2C1_SCL_PAL_MODE` | `4`     |
| `I2C1_SDA_PAL_MODE` | `4`     |

<!-- Other -->
#### その他

`void i2c_init(void)` 関数は `weak` 属性が付いており、オーバーロードすることができます。この場合、上記で設定した変数は使用されません。可能な GPIO の設定については、MCUのデータシートを参照してください。次に示すのは初期化関数の例です：

```C
void i2c_init(void)
{
  setPinInput(B6); // Try releasing special pins for a short time
  setPinInput(B7);
  wait_ms(10); // Wait for the release to happen

  palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B6 to I2C function
  palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B7 to I2C function
}
```
