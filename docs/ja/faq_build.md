# よくあるビルドの質問

<!---
  original document: 0.12.43:docs/faq_build.md
  git diff 0.12.43 HEAD -- docs/faq_build.md | cat
-->

このページは QMK のビルドに関する質問を説明します。まだビルドをしていない場合は、[ビルド環境のセットアップ](ja/getting_started_build_tools.md) および [Make 手順](ja/getting_started_make_guide.md)ガイドを読むべきです。

## Linux でプログラムできません
デバイスを操作するには適切な権限が必要です。Linux ユーザの場合は、以下の `udev` ルールに関する指示を見てください。`udev` に問題がある場合は、回避策は `sudo` コマンドを使うことです。このコマンドに慣れていない場合は、`man sudo` コマンドでマニュアルを確認するか、[この web ページを見てください](https://linux.die.net/man/8/sudo)。

コントローラが ATMega32u4 の場合の `sudo` の使い方の例:

    $ sudo dfu-programmer atmega32u4 erase --force
    $ sudo dfu-programmer atmega32u4 flash your.hex
    $ sudo dfu-programmer atmega32u4 reset

あるいは、単純に:

    $ sudo make <keyboard>:<keymap>:flash

`make` を `sudo` で実行することは一般的には良い考えでは***なく***、可能であれば前者の方法のいずれかを使うべきです。

### Linux の `udev` ルール :id=linux-udev-rules

Linux では、ブートローダデバイスと通信するには適切な権限が必要です。ファームウェアを書き込む時に `sudo` を使うか(非推奨)、`/etc/udev/rules.d/` に[このファイル](https://github.com/qmk/qmk_firmware/tree/master/util/udev/50-qmk.rules)を配置することで、通信することができます。

追加が完了したら、以下を実行します:

```
sudo udevadm control --reload-rules
sudo udevadm trigger
```

**注意:** 古い(1.12以前の) ModemManager では、フィルタリングは厳密なモードではない場合にのみ動作し、以下のコマンドはその設定を更新することができます。

```
printf '[Service]\nExecStart=\nExecStart=/usr/sbin/ModemManager --filter-policy=default' | sudo tee /etc/systemd/system/ModemManager.service.d/policy.conf
sudo systemctl daemon-reload
sudo systemctl restart ModemManager
```

### Linux のブートローダモードで Serial デバイスが検知されない
カーネルがデバイスを適切にサポートしていることを確認してください。デバイスが、Pro Micro (Atmega32u4) のように USB ACM を使う場合、`CONFIG_USB_ACM=y` を含めるようにしてください。他のデバイスは `USB_SERIAL` およびそのサブオプションを必要とするかもしれません。

## DFU ブートローダの不明なデバイス

Windows 上でキーボードを書き込む時に発生する問題は、ブートローダ用に間違ったドライバがインストールされているか、全くインストールされていないかによるものがほとんどです。

QMK インストールスクリプト (MSYS2 あるいは WSL 内の `qmk_firmware` ディレクトリから `./util/qmk_install.sh`) を再実行するか、QMK Toolbox の再インストールでこの問題が解決するかもしれません。別のやり方として、手動で [`qmk_driver_installer`](https://github.com/qmk/qmk_driver_installer) パッケージをダウンロードして実行することができます。

それでもうまく行かない場合は、Zadig をダウンロードして実行する必要があります。詳細な情報は [Zadig を使ったブートローダドライバのインストール](ja/driver_installation_zadig.md)を見てください。

## USB VID と PID
`config.h` を編集することで任意の ID を使うことができます。おそらく未使用の ID を使っても、他の製品と衝突するとても低い可能性があることを除いて、実際には問題はありません。

QMK のほとんどのキーボードは、vendor ID として、`0xFEED` を使います。他のキーボードを調べて、ユニークな ID を選択してください。

またこれも見てください。
https://github.com/tmk/tmk_keyboard/issues/150

ここで本当にユニークな VID:PID を買うことができます。個人的な使用にはこれは必要ないと思います。
- https://www.obdev.at/products/vusb/license.html
- https://www.mcselec.com/index.php?page=shop.product_details&flypage=shop.flypage&product_id=92&option=com_phpshop&Itemid=1

### キーボードに書き込んだが何も起こらない、あるいはキーの押下が登録されない - ARM (rev6 planck、clueboard 60、hs60v2 など) でも同じ (Feb 2019)
ARM ベースのチップ上での EEPROM の動作によって、保存された設定が無効になる場合があります。これはデフォルトレイヤに影響し、まだ調査中の特定の環境下でキーボードが使えなくなるかも*しれません*。EEPROM のリセットでこれが修正されます。

[Planck rev6 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/539284620861243409/planck_rev6_default.bin) を使って eeprom のリセットを強制することができます。このイメージを書き込んだ後で、通常のファームウェアを書き込むと、キーボードが _通常_ の動作順序に復元されます。
[Preonic rev3 reset EEPROM](https://cdn.discordapp.com/attachments/473506116718952450/537849497313738762/preonic_rev3_default.bin)

いずれかの形式でブートマジックが有効になっている場合は、これも実行できるはずです (実行方法の詳細については、[ブートマジックドキュメント](ja/feature_bootmagic.md)とキーボード情報を見てください)。
