# QMK環境セットアップガイド（macOS Apple Silicon）

## 現在の問題

システムにx86_64版のCommandLineToolsがインストールされているため、ARM64（Apple Silicon）環境で正しく動作していません。

## 解決方法

### ステップ1: CommandLineToolsの再インストール

1. **古いCommandLineToolsを削除**（オプション）
   ```bash
   sudo rm -rf /Library/Developer/CommandLineTools
   ```

2. **新しいCommandLineToolsをインストール**
   ```bash
   xcode-select --install
   ```
   
   または、[Apple Developerサイト](https://developer.apple.com/download/all/)から直接ダウンロードしてインストール

3. **インストール後、パスを設定**
   ```bash
   sudo xcode-select --switch /Library/Developer/CommandLineTools
   ```

4. **動作確認**
   ```bash
   git --version
   python3 --version
   ```

### ステップ2: QMK CLIのインストール

#### 方法A: Homebrewを使用（推奨）

```bash
# Homebrewが正常に動作することを確認
brew --version

# QMK CLIをインストール
brew install qmk/qmk/qmk
```

#### 方法B: pipを使用

```bash
# pip3が正常に動作することを確認
python3 -m pip --version

# QMK CLIをインストール
python3 -m pip install qmk
```

### ステップ3: QMKリポジトリのセットアップ

```bash
# QMKリポジトリをセットアップ
qmk setup

# 初回実行時は、QMKリポジトリの場所を聞かれます
# デフォルトの ~/qmk_firmware で問題ありません
```

### ステップ4: 環境の確認

```bash
# QMK環境の状態を確認
qmk doctor
```

このコマンドで、不足している依存関係や設定の問題が表示されます。

### ステップ5: 必要な依存関係のインストール

`qmk doctor`の出力に従って、不足している依存関係をインストールします。

一般的に必要なもの：
- `avr-gcc` (AVRマイコン用コンパイラ)
- `dfu-programmer` (ファームウェア書き込み用)
- `dfu-util` (ファームウェア書き込み用)

```bash
# Homebrewでインストール
brew install avr-gcc dfu-programmer dfu-util
```

## トラブルシューティング

### Homebrewが動作しない場合

```bash
# Homebrewを再インストール
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### pipが動作しない場合

```bash
# pipをアップグレード
python3 -m pip install --upgrade pip
```

### QMK setupが失敗する場合

手動でQMKリポジトリをクローン：

```bash
# QMKリポジトリをクローン
git clone https://github.com/qmk/qmk_firmware.git ~/qmk_firmware

# QMK CLIにリポジトリの場所を設定
qmk config user.qmk_home=~/qmk_firmware
```

## 次のステップ

環境セットアップが完了したら、`BUILD_INSTRUCTIONS.md`を参照してファームウェアのビルドと書き込みを行ってください。

