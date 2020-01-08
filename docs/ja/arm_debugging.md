# Eclipse を使った ARM デバッグ

<!---
  original document: eae21eed7:docs/arm_debugging.md
  git diff eae21eed7 HEAD -- docs/arm_debugging.md | cat
-->

このページでは、SWD アダプタとオープンソース/フリーツールを使って ARM MCU をデバッグするためのセットアップ方法について説明します。このガイドでは、GNU MCU Eclipse IDE for C/C++ Developers および OpenOCD を必要な依存関係と一緒にインストールします。

このガイドは上級者向けであり、あなたのマシンで、MAKE フローを使って、ARM 互換キーボードをコンパイルできることを前提にしています。

## ソフトウェアのインストール

ここでの主な目的は MCU Eclipse IDE を正しくマシンにインストールすることです。必要な手順は[この](https://gnu-mcu-eclipse.github.io/install/)インストールガイドから派生しています。

### xPack マネージャ

このツールはソフトウェアパッケージマネージャであり、必要な依存関係を取得するために使われます。

XPM は Node.js を使って実行されるため、[ここ](https://nodejs.org/en/)から取得してください。インストール後に、ターミナルを開き `npm -v` と入力します。バージョン番号が返ってくるとインストールは成功です。

XPM のインストール手順は[ここ](https://www.npmjs.com/package/xpm)で見つけることができ、OS 固有のものです。ターミナルに `xpm --version` と入力すると、ソフトウェアのバージョンが返ってくるはずです。

### ARM ツールチェーン

XPM を使うと、ARM ツールチェーンをとても簡単にインストールできます。`xpm install --global @xpack-dev-tools/arm-none-eabi-gcc` とコマンドを入力します。

### Windows ビルドツール

Windows を使っている場合は、これをインストールする必要があります！

`xpm install --global @gnu-mcu-eclipse/windows-build-tools`

### プログラマ/デバッガドライバ

プログラマのドライバをインストールします。このチュートリアルはほとんどどこでも入手できる ST-Link v2 を使って作成されました。
ST-Link を持っている場合は、ドライバは[ここ](https://www.st.com/en/development-tools/stsw-link009.html)で見つけることができます。そうでない場合はツールの製造元にお問い合わせください。

### OpenOCD

この依存関係により、SWD は GDB からアクセスでき、デバッグに不可欠です。`xpm install --global @xpack-dev-tools/openocd` を実行します。

### Java

Java は Eclipse で必要とされるため、[ここ](https://www.oracle.com/technetwork/java/javase/downloads/index.html)からダウンロードしてください。

### GNU MCU Eclipse IDE

最後に IDE をインストールする番です。[ここ](https://github.com/gnu-mcu-eclipse/org.eclipse.epp.packages/releases/)のリリースページから最新バージョンを取得します。

## Eclipse の設定

ダウンロードした Eclipse IDE を開きます。QMK ディレクトリをインポートするために、File -> Import -> C/C++ -> Existing Code as Makefile Project を選択します。Next を選択し、Browse を使用して QMK フォルダを選択します。tool-chain リストから ARM Cross GCC を選択し、Finish を選択します。

これで、左側に QMK フォルダが表示されます。右クリックして、Properties を選択します。左側で MCU を展開し、ARM Toolchains Paths を選択します。xPack を押して OK を押します。OpenOCD Path で同じことを繰り返し、Windows の場合は、Build Tools Path でも同じことを繰り返します。Apply and Close を選択します。

ここで、必要な MCU パッケージをインストールします。Window -> Perspective -> Open Perspective -> Other... -> Packs を選択して、Packs perspective に移動します。Packs タブの横にある黄色のリフレッシュ記号を選択します。これは様々な場所から MCU の定義を要求するため、時間が掛かります。一部のリンクが失敗した場合は、おそらく Ignore を選択できます。

これが終了すると、ビルドやデバッグする MCU を見つけることができるはずです。この例では、STM32F3 シリーズの MCU を使います。左側で、STMicroelectronics -> STM32F3 Series を選択します。中央のウィンドウに、pack が表示されます。右クリックし、Install を選択します。それが終了したら、Window -> Perspective -> Open Perspective -> Other... -> C/C++ を選択してデフォルトのパースペクティブに戻ることができます。

Eclipse に QMK をビルドしようとするデバイスを教える必要があります。QMK フォルダを右クリック -> Properties -> C/C++ Build -> Settings を選択します。Devices タブを選択し、Devices の下から MCU の適切な種類を選択します。私の例では、STM32F303CC です。

この間に、Build コマンドもセットアップしましょう。C/C++ Build を選択し、Behavior タブを選択します。build コマンドのところで、`all` を必要な make コマンドに置き換えます。例えば、rev6 Planck の default キーマップの場合、これは `planck/rev6:default` になります。Apply and Close を選択します。

## ビルド

全て正しくセットアップできていれば、ハンマーボタンを押すとファームウェアがビルドされ、.binファイルが出力されるはずです。

## デバッグ

### デバッガの接続

ARM MCU は、クロック信号(SWCLK) とデータ信号(SWDIO) で構成される Single Wire Debug (SWD) プロトコルを使います。MCUを 完全に操作するには、この2本のワイヤとグラウンドを接続するだけで十分です。ここでは、キーボードは USB を介して電力が供給されると想定しています。手動でリセットボタンを使えるため、RESET 信号は必要ありません。より高度なセットアップのために printf と scanf をホストに非同期にパイプする SWO 信号を使用できますが、私たちのセットアップでは無視します。

注意: SWCLK と SWDIO ピンがキーボードのマトリックスで使われていないことを確認してください。もし使われている場合は、一時的に他のピンに切り替えることができます。

### デバッガの設定

QMK フォルダを右クリックし、Debug As -> Debug Configurations... を選択します。ここで、GDB OpenOCD Debugging をダブルクリックします。Debugger タブを選択し、MCU に必要な設定を入力します。これを見つけるにはいじったりググったりする必要があるかもしれません。STM32F3 用のデフォルトスクリプトは stm32f3discovery.cfg と呼ばれます。OpenOCD に伝えるには、Config options で `-f board/stm32f3discovery.cfg` と入力します。

注意: 私の場合、この設定スクリプトはリセット操作を無効にするために編集が必要です。スクリプトの場所は、通常はパス `openocd/version/.content/scripts/board` の下の実際の実行可能フィールドの中で見つかります。ここで、私は `reset_config srst_only` を `reset_config none` に編集しました。

Apply and Close を選択します。

### デバッガの実行

キーボードをリセットしてください。

虫アイコンをクリックし、もし全てうまく行けば Debug パースペクティブに移動します。ここでは、main 関数の最初でプログラムカウンタが停止するので、Play ボタンを押します。全てのデバッガのほとんどの機能は ARM MCU で動作しますが、正確な詳細については google があなたのお友達です！


ハッピーデバッギング！
