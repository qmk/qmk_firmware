# Sample for ble_micro_pro with B.T.O trackball module

BLE Micro Proでビット・トレード・ワンのトラックボールモジュールを使うサンプルコードです

## ハードウェア
[トラックボールモジュール用変換基板](https://github.com/sekigon-gonnoc/LevelConverterForTrackballModule)を使用して確認しています

## 通信方式
基本はSPIです。paw3204.cのspi_paw3204に指定する関数で2種類の配線から選択します

- 回路による半二重方式
    - SPIのMOSIとMISOを抵抗で接続して半二重方式で通信します
    - 通信に使うピンはconfig.hに`CONFIG_(MOSI|MISO|SCK)_PIN`でそれぞれ指定してください。デフォルトはPro Microと同じ位置です

    ```
    ____________             _________
           MOSI |---+        |
                |  10k       |
    BMP    MISO |---+--------| SDIO
                |            |
           SCLK |------------| SCLK
                |            |
           GND  |------------| GND
    ____________|            |________
    ```

- ソフトによる半二重方式
    - SPIのMOSIとMISOを適宜切り替えて通信します
    - 通信に使うピンはconfig.hに`PAW3204_(SCLK|DATA)`でそれぞれ指定してください

    ```
    ____________             _________
                |            |
    BMP    DATA |------------| SDIO
                |            |
           SCLK |------------| SCLK
                |            |
            GND |------------| GND
    ____________|            |________
    ```

