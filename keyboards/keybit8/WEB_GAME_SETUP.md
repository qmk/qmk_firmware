# Keybit8 Web Game セットアップガイド

## 概要

Keybit8キーボード用のWebゲームを作成しました。LEDとスピーカーを使用したインタラクティブなゲームを楽しめます。

## バックアップ

現在のファームウェアは以下の場所にバックアップされています：
- `keymaps/default_backup/` - 元のキーマップ
- `config.h.backup` - 元の設定ファイル
- `rules.mk.backup` - 元のルールファイル
- `keymaps/default/keymap.c.backup` - 元のキーマップファイル

## 実装状況

### ✅ 完了した機能

1. **LED制御機能**
   - 8個の赤LED（ピン1, 8, 16, 15, 0, 9, 14, 18）
   - 1個の緑LED（ピン19）
   - ピンの初期化と制御関数

2. **スピーカー制御機能**
   - スピーカーピン（ピン10）の初期化
   - トーン生成機能（基本的な実装）

3. **QMKファームウェアの設定**
   - `CONSOLE_ENABLE = yes` - シリアル通信を有効化
   - `AUDIO_ENABLE = yes` - オーディオ出力を有効化
   - LEDとスピーカーのピン定義

4. **Webゲームファイル**
   - `game/index.html` - ゲームのメインHTML
   - `game/style.css` - スタイルシート
   - `game/game.js` - ゲームロジックとキーボード通信
   - `game/README.md` - 使い方の説明

### ⚠️ 未実装の機能

1. **シリアル通信の読み取り**
   - Webゲームからのコマンドを受け取る機能はまだ実装されていません
   - QMKでシリアル通信の読み取りを実装するには、Raw HIDを使用するか、カスタム実装が必要です

## 次のステップ

### オプション1: Raw HIDを使用する（推奨）

Raw HIDを使用してWebゲームと通信する方法：
1. QMKファームウェア側でRaw HIDを有効化
2. Webゲーム側でWebHID APIを使用
3. コマンドをHIDレポートとして送受信

### オプション2: シリアル通信を実装する

QMKでシリアル通信の読み取りを実装する方法：
1. `uart.h`を使用してシリアル通信を実装
2. Web Serial APIと通信
3. コマンドを文字列として送受信

### オプション3: キー入力で制御する

シンプルな方法として、キーボードのキー入力を使ってLEDとスピーカーを制御：
1. 特定のキーコンビネーションでLEDを制御
2. ゲームモードの切り替え
3. より簡単な実装

## 現在のファームウェアの機能

### LED制御

レイヤーに応じて緑LEDが点灯します：
- レイヤー1またはレイヤー2がアクティブな場合、緑LEDが点灯

### スピーカー制御

現在は基本的なトーン生成機能が実装されていますが、シリアル通信からのコマンドを受け取る機能は未実装です。

## ビルドと書き込み

```bash
cd /Users/inenoyuki/qmk_firmware
qmk compile -kb keybit8 -km default
qmk flash -kb keybit8 -km default
```

## トラブルシューティング

### ビルドエラー

- バックアップファイルから元の状態に戻すことができます
- `config.h.backup`、`rules.mk.backup`、`keymap.c.backup`を元のファイルにコピー

### LEDが点灯しない

- ピン番号が正しいか確認
- ハードウェアの接続を確認

### 音が鳴らない

- スピーカーの接続を確認
- ピン番号が正しいか確認

## 参考資料

- [QMK Documentation](https://docs.qmk.fm/)
- [Web Serial API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Serial_API)
- [WebHID API](https://developer.mozilla.org/en-US/docs/Web/API/WebHID_API)

