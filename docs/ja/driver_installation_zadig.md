# Zadigを使ったブートローダ ドライバのインストール

QMKは通常のHIDキーボードとしてホストに提示されるため、特別なドライバは必要ありません。However, in order to flash your keyboard on Windows, the bootloader device that appears when you reset the board often *does*.

2つの注目すべき例外があります: Pro Microで通常見られるCaterina ブートローダと、PJRC Teensyに同梱されているHalfkayブートローダは、それぞれシリアルポートーと汎用HIDデバイスとして表示されるため、ドライバを必要としません。

[Zadig](https://zadig.akeo.ie/) ユーティリティを使うことをお勧めします。Msys2 あるいは WSL を使って開発環境をセットアップした場合、`qmk_install.sh` スクリプトはドライバをインストールするかどうかを尋ねます。

## インストール

`RESET` キーコード (別のレイヤにあるかもしれません)を押すか、通常はボードの下側にあるリセットスイッチを押して、キーボードをブートローダモードにします。キーボードに無い場合は、Escape または Space+`B` を押しながら接続してみてください (詳細は、[Bootmagic](feature_bootmagic.md) ドキュメントを見てください)。一部のボードはBootmagicの代わりに[Command](feature_command.md)を使います; この場合、キーボードが接続されている任意の時点で Left Shift+Right Shift+`B` あるいは Left Shift+Right Shift+Escape を押すと、ブートローダ モードに入ることができます。
一部のキーボードにはブートローダ に入るための特定の指示があります。例えば、[Bootmagic Lite](feature_bootmagic.md#bootmagic-lite) キー (デフォルト: Escape) は別のキーにあるかもしれません。例えば、左 Control; あるいは Command の魔法の組み合わせ (デフォルト: Left Shift+Right Shift) は何か他の物を保持する必要がある場合があります。例えば Left Control+Right Control。不明な場合は、ボードの README ファイルを参照してください。

USBaspLoader を使ってデバイスをブートローダ モードにするには、`BOOT`ボタンを押しながら`RESET` ボタンをタップしてください。
または、USBケーブルを挿入しながら`BOOT`を保持します。

Zadig は自動的にブートローダ デバイスを検知します。**Options → List All Devices** を確認する必要がある場合があります。

- Atmel AVR MCU を搭載したキーボードの場合、ブートローダは`ATm32U4DFU`に似た名前が付けられ、ベンダーIDは`03EB`です。
- USBasp ブートローダは`USBasp`として表示され、VID/PID は`16C0:05DC`です。
- QMK-DFU ブートローダを使ってフラッシュされた AVR キーボードは `<keyboard name> Bootloader` という名前が付けられ、VID `03EB`も持ちます。
- ほとんどの ARM キーボードでは、`STM32 BOOTLOADER`と呼ばれ、VID/PID `0483:DF11` を持ちます。

!> Zadigは`HidUsb`ドライバで1つ以上のデバイスをリストする場合、キーボードはおそらくブートローダ モードではありません。矢印はオレンジ色になり、システムドライバの変更を確認するように求められます。この場合、続行**しないでください**！

矢印が緑色で表示されたら、ドライバを選択し、**Install Driver**をクリックします。`libusb-win32` ドライバは通常 AVR で動作し、`WinUSB`は ARMで動作しますが、まだボードをフラッシュできない場合は、リストから異なるドライバをインストールしてみてください。nsys2を使ってコマンドライン経由でUSBaspLoaderドライバをフラッシュするには、`libusbk`ドライバがお勧めです。そうでなければ、フラッシュのためにQMK Toolboxを使っている場合は`libusb-win32`が動作します。

![Zadig with a bootloader driver correctly installed](https://i.imgur.com/b8VgXzx.png)

最後に、新しいドライバがロードされたことを確認するためにキーボードのプラグを抜いて再接続します。フラッシュにQMKを使う場合は、ドライバの変更を認識しない場合があるため、QMK Toolkitも終了して再起動します。

## 間違ったデバイスのインストールからの回復

キーボードで入力できなくなった場合は、ブートローダではなくキーボード自体にドライバをインストールした可能性があります。これはZadigで簡単に確認することができます - 健全なキーボードには、全てのインタフェースに `HidUsb` ドライバがインストールされています:

![Zadigから見た健全なキーボード](https://i.imgur.com/Hx0E5kC.png)

デバイスマネージャを開き、キーボードと思われるデバイスを探します。

![デバイスマネージャで、間違ったドライバがインストールされたボード](https://i.imgur.com/L3wvX8f.png)

右クリックし、**Uninstall device**をクリックします。最初に**Delete the driver software for this device**をクリックするようにしてください。

!["ドライバの削除"にチェックボックスにチェックが付いた、デバイスのアンインストール ダイアログ](https://i.imgur.com/aEs2RuA.png)

**Action → Scan for hardware changes**をクリックします。この時点で、再び入力できるはずです。Zadigでキーボード デバイスが`HidUsb`ドライバを使っていることを再確認します。そうであれば、完了です。ボードは再び機能するはずです！
