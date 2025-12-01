# QMKファームウェア ビルド・書き込み手順

## 前提条件

1. **QMK Toolbox** または **qmk CLI** がインストールされていること
2. **Arduino Pro Micro** が接続されていること

## 方法1: QMK CLIを使用する場合（推奨）

### ステップ1: QMK環境のセットアップ

1. **QMK CLIをインストール**（まだの場合）
   ```bash
   # macOSの場合
   brew install qmk/qmk/qmk
   
   # または、pipを使用
   pip3 install qmk
   ```

2. **QMKリポジトリをクローン**
   ```bash
   qmk setup
   ```
   初回実行時は、QMKリポジトリの場所を聞かれます。デフォルトの `~/qmk_firmware` で問題ありません。

### ステップ2: キーボードファイルの配置

1. **qmk_keybit8ディレクトリをQMKのキーボードディレクトリにコピー**
   ```bash
   # 現在のディレクトリから実行
   cp -r qmk_keybit8 ~/qmk_firmware/keyboards/
   ```

2. **確認**
   ```bash
   ls ~/qmk_firmware/keyboards/keybit8
   ```
   以下のファイルが存在することを確認：
   - `config.h`
   - `rules.mk`
   - `keymap.c` または `keymaps/default/keymap.c`

### ステップ3: ファームウェアのビルド

```bash
cd ~/qmk_firmware
qmk compile -kb keybit8 -km default
```

**成功時の出力例：**
```
Compiling: keyboards/keybit8/keymap.c                                    [OK]
Creating keybit8_default.hex                                              [OK]
```

ビルドされたファイルは `~/qmk_firmware/.build/keybit8_default.hex` に生成されます。

### ステップ4: ファームウェアの書き込み

1. **Arduino Pro Microを接続**

2. **ブートローダーモードに入る**
   - Arduino Pro Microの **RESETボタンを2回素早く押す**
   - または、**GNDとRSTを短絡**してから離す
   - 成功すると、PC上で新しいUSBデバイス（通常は "Arduino Leonardo" または "ATm32U4DFU"）として認識されます

3. **ファームウェアを書き込み**
   ```bash
   qmk flash -kb keybit8 -km default
   ```

   **注意**: 書き込み中はキーボードを抜かないでください。

4. **完了**
   - 書き込みが完了すると、キーボードが自動的に再起動します
   - 数秒後にキーボードとして認識されます

## 方法2: QMK Toolboxを使用する場合

### ステップ1: QMK Toolboxのダウンロード

1. [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) から最新版をダウンロード
2. アプリケーションを起動

### ステップ2: ファームウェアのビルド（CLIを使用）

```bash
cd ~/qmk_firmware
qmk compile -kb keybit8 -km default
```

### ステップ3: QMK Toolboxで書き込み

1. **QMK Toolboxを開く**

2. **「Open」ボタンをクリック**
   - `~/qmk_firmware/.build/keybit8_default.hex` を選択

3. **「Auto-Flash」にチェックを入れる**（オプション）
   - ブートローダーモードに入ると自動的に書き込みが開始されます

4. **Arduino Pro Microをブートローダーモードに入る**
   - RESETボタンを2回素早く押す
   - または、GNDとRSTを短絡

5. **「Flash」ボタンをクリック**
   - 書き込みが開始されます

6. **完了を確認**
   - ターミナルに "Device disconnected" と表示されれば成功

## トラブルシューティング

### ビルドエラーが発生する場合

1. **QMKが最新か確認**
   ```bash
   qmk doctor
   ```

2. **依存関係をインストール**
   ```bash
   qmk setup
   ```

3. **エラーメッセージを確認**
   - 通常、不足しているツールやライブラリが表示されます

### 書き込みが失敗する場合

1. **ブートローダーモードに入れているか確認**
   - RESETボタンのタイミングが重要です
   - 2回素早く押す必要があります

2. **正しいポートを選択しているか確認**
   - QMK Toolboxの場合、右上のドロップダウンでポートを選択

3. **ドライバーがインストールされているか確認**
   - macOS: 通常は不要
   - Windows: [Zadig](https://zadig.akeo.ie/) でドライバーをインストール

4. **別のUSBケーブルを試す**
   - データ転送対応のケーブルが必要です

### キーボードが認識されない場合

1. **USBケーブルを抜き差し**
2. **PCを再起動**
3. **別のUSBポートを試す**

## 確認方法

書き込み後、以下の方法で動作を確認できます：

1. **キーを押して動作確認**
   - W, A, S, D などが正しく入力されるか確認
   - レイヤー切り替え（長押し）が動作するか確認
   - 緑LEDの状態でレイヤーを確認
     - レイヤー0: LED OFF
     - レイヤー1: LED ON
     - レイヤー2: LED 点滅
     - レイヤー3: LED ON

2. **Remapで認識されるか確認**
   - [Remap](https://remap-keys.app/) にアクセス
   - 「+ KEYBOARD」をクリック
   - Keybit8が表示されれば成功

## 次のステップ

書き込みが完了したら、[Remap](https://remap-keys.app/) でキーマッピングをカスタマイズできます。

**Layer Tapの設定方法**:
1. キーを選択
2. 「Layer Tap」を選択
3. レイヤー番号を選択（例: Layer 3）
4. タップ時のキーを選択（例: D）

これで、タップでキー入力、長押しでレイヤー切り替えが可能になります。

