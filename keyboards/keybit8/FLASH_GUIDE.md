# Keybit8 ファームウェア書き込みガイド

## 前提条件

✅ QMK CLIがインストール済み（確認済み）
✅ ファームウェアのビルドが完了（`keybit8_default.hex`が生成済み）

## 書き込み手順

### 方法1: QMK CLIを使用（推奨・最も簡単）

#### ステップ1: キーボードを接続

1. **Arduino Pro MicroをUSBケーブルでPCに接続**
   - データ転送対応のUSBケーブルを使用してください
   - 充電専用ケーブルでは書き込みできません

#### ステップ2: ブートローダーモードに入る

Arduino Pro Microをブートローダーモードに入れる方法：

1. **RESETボタンを2回素早く押す**
   - 1回目：リセット
   - 2回目（1秒以内）：ブートローダーモードに入る
   - 成功すると、PC上で新しいUSBデバイスとして認識されます
   - macOSの場合、システム設定で「Arduino Leonardo」や「ATm32U4DFU」として表示されます

2. **または、GNDとRSTを短絡**
   - 導線などでGNDとRSTピンを短絡してから離す
   - ブートローダーモードに入ります

#### ステップ3: ファームウェアを書き込む

```bash
cd /Users/inenoyuki/qmk_firmware
qmk flash -kb keybit8 -km default
```

**実行時の流れ：**
1. QMKが自動的にデバイスを検出します
2. ブートローダーモードに入っていない場合、自動的に入るよう促されます
3. 書き込みが開始されます（数秒かかります）
4. 完了すると自動的に再起動します

**成功時の出力例：**
```
Ψ Flashing keybit8 to keybit8_default
Ψ Bootloader: caterina
Ψ Size: 17302
Ψ Checking for flashable device...
Ψ Device found!
Ψ Flashing...
Ψ Success!
```

#### ステップ4: 動作確認

1. **キーボードが認識されるか確認**
   - 数秒後にキーボードとして認識されます
   - システム設定で「Keybit8」として表示されるはずです

2. **キーを押して動作確認**
   - 各キーが正しく入力されるか確認してください

3. **Remapで認識されるか確認**（VIA対応の場合）
   - [Remap](https://remap-keys.app/) にアクセス
   - 「+ KEYBOARD」をクリック
   - Keybit8が表示されれば成功

---

### 方法2: QMK Toolboxを使用

#### ステップ1: QMK Toolboxのダウンロード

1. [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) から最新版をダウンロード
2. macOSの場合、`.dmg`ファイルをダウンロードしてインストール

#### ステップ2: ファームウェアファイルを開く

1. **QMK Toolboxを起動**
2. **「Open」ボタンをクリック**
   - `/Users/inenoyuki/qmk_firmware/.build/keybit8_default.hex` を選択
   - または `/Users/inenoyuki/qmk_firmware/keybit8_default.hex` を選択

#### ステップ3: 書き込み

1. **「Auto-Flash」にチェックを入れる**（オプション）
   - ブートローダーモードに入ると自動的に書き込みが開始されます

2. **Arduino Pro Microをブートローダーモードに入る**
   - RESETボタンを2回素早く押す
   - または、GNDとRSTを短絡

3. **「Flash」ボタンをクリック**
   - 書き込みが開始されます
   - ターミナルに進行状況が表示されます

4. **完了を確認**
   - 「Device disconnected」と表示されれば成功
   - キーボードが自動的に再起動します

---

### 方法3: avrdudeを直接使用（上級者向け）

```bash
cd /Users/inenoyuki/qmk_firmware
avrdude -p atmega32u4 -c avr109 -P /dev/tty.usbmodem* -U flash:w:.build/keybit8_default.hex:i
```

**注意：**
- `/dev/tty.usbmodem*` の部分は、実際のデバイスパスに置き換えてください
- デバイスパスは `ls /dev/tty.usbmodem*` で確認できます

---

## トラブルシューティング

### 書き込みが失敗する場合

#### 1. ブートローダーモードに入れない

- **RESETボタンのタイミングを調整**
  - 2回目の押下を1秒以内に行う
  - 素早く連続で押す

- **GNDとRSTの短絡を試す**
  - より確実な方法です

#### 2. デバイスが見つからない

```bash
# 接続されているUSBデバイスを確認
ls /dev/tty.usbmodem*
ls /dev/cu.usbmodem*
```

- デバイスが表示されない場合：
  - USBケーブルを抜き差し
  - 別のUSBポートを試す
  - 別のUSBケーブルを試す（データ転送対応のもの）

#### 3. 権限エラーが発生する場合

```bash
# ユーザーをdialoutグループに追加（通常は不要）
sudo dseditgroup -o edit -a $(whoami) -t user _developer
```

#### 4. 「Device not found」エラー

- ブートローダーモードに入っているか再確認
- QMK Toolboxの場合、右上のドロップダウンで正しいポートを選択

### 書き込み後、キーボードが認識されない場合

1. **USBケーブルを抜き差し**
2. **PCを再起動**
3. **別のUSBポートを試す**
4. **ファームウェアを再書き込み**

### キーが正しく動作しない場合

1. **キーマップを確認**
   - `keymaps/default/keymap.c` を確認
   - 必要に応じて修正して再ビルド・再書き込み

2. **マトリックス配線を確認**
   - `config.h` のピン設定が正しいか確認
   - 実際の配線と一致しているか確認

---

## よくある質問

### Q: 書き込み中にエラーが出たが、どうすればいい？

A: エラーメッセージを確認してください。通常は：
- ブートローダーモードに入っていない
- USBケーブルがデータ転送対応でない
- デバイスが正しく接続されていない

### Q: 何度書き込み直しても動作しない

A: 以下を確認してください：
1. ファームウェアのビルドが正常に完了しているか
2. キーマップファイルが正しいか
3. ハードウェアの配線が正しいか

### Q: Remapで認識されない

A: 
1. VIA対応が有効になっているか確認（`rules.mk`で`VIA_ENABLE = yes`）
2. `via.json`ファイルが正しく配置されているか確認
3. ブラウザを再読み込み

---

## 次のステップ

書き込みが完了したら：

1. **キーマップのカスタマイズ**
   - [Remap](https://remap-keys.app/) でキーマップを変更
   - または、`keymaps/default/keymap.c` を編集して再ビルド・再書き込み

2. **レイヤーの設定**
   - 現在3レイヤーが設定されています
   - 必要に応じて追加・変更

3. **動作テスト**
   - すべてのキーが正しく動作するか確認

