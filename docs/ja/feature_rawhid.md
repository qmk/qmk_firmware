# Raw HID

<!---
  original document: 0.12.41:docs/feature_rawhid.md
  git diff 0.12.41 HEAD -- docs/feature_rawhid.md | cat
-->

Raw HID は、HID インタフェースを介して QMK とホストコンピュータ間の双方向通信を可能にします。これには、キーマップをその場で切り替えたり、RGB LED の色とモードを変更したりなど、多くの潜在的な使用方法があります。

キーボードで raw HID を機能させるには、2つの主要なコンポーネントがあります。

## キーボードファームウェア

ファームウェアの実装はとても簡単です。
`rules.mk` に以下を追加します:

```make
RAW_ENABLE = yes
```

`keymap.c` に `"raw_hid.h"` を include し、以下を実装します:

```C
void raw_hid_receive(uint8_t *data, uint8_t length) {
    // ここにコードを書きます。data はホストから受信したパケットです。
}
```

`"raw_hid.h"` ヘッダは、キーボードからホストにパケットを送信できる `void raw_hid_send(uint8_t *data, uint8_t length);` も宣言します。例として、全てのデータをホストに返すことで、ホストアプリケーションを構築する時のデバッグに使うこともできます。

```C
void raw_hid_receive(uint8_t *data, uint8_t length) {
    raw_hid_send(data, length);
}
```

これら2つの関数は、ホストとの間で長さ `RAW_EPSIZE` バイトのパケットを送受信します (LUFA/ChibiOS/V-USB では 32、ATSAM では 64)。

ホスト側での作業を進める前に、raw 対応のファームウェアを書き込むようにしてください。

## ホスト (Windows/macOS/Linux)

これは幾つかの掘り下げが必要になるため、より複雑な部分です。

ホストコンピュータを raw HID を使ってキーボードに接続するには、キーボードについての4つの情報が必要です。

1. Vendor ID
2. Product ID
3. Usage Page
4. Usage

前半の2つは、キーボードのメインディレクトリにあるキーボードの `config.h` で、`VENDOR_ID` と `PRODUCT_ID` で簡単に見つかります。

後半の2つは、キーボードのメインディレクトリにあるキーボードの `config.h` で、値を再定義することで上書きすることができます: `#define RAW_USAGE_PAGE 0xFF60` と `#define RAW_USAGE_ID 0x61`。

デフォルトでは、**Usage Page** は `0xFF60` で、**Usage** は `0x61` です。

### ホストの構築

独自に作成したくない場合は、利用可能な HID 実装ライブラリがある任意の言語を使ってホストを構築することができます。人気のある言語でよく使われるライブラリは以下の通りです:

* Node: [node-hid](https://github.com/node-hid/node-hid)。
* C: [hidapi](https://github.com/libusb/hidapi)。
* Java: [purejavahidapi](https://github.com/nyholku/purejavahidapi) と [hid4java](https://github.com/gary-rowe/hid4java)。
* Python: [pyhidapi](https://pypi.org/project/hid/)。

これは完全なクロスプラットフォームのリストではありませんが、最初に始めるのに十分なはずです。raw HID を使うための特別な要件は無いため、どの HID ライブラリでも動作するはずです。

これで、キーボードへの HID インタフェースを開くために必要な4つの情報全てが揃いました。必要なのは、ライブラリの利用可能な関数を使って ID パラメータを使ってデバイスを開くことだけです。

Vendor ID と Product ID はデバイスを開くために実際には必要ないことに注意してください。それらは接続した多くの HID デバイスから特定のデバイスをフィルターするためだけに使われます。多くのライブラリでは、代わりに製品名と製造元名を使ってデバイスを開くオプションがあります。`node-hid` が代表的な例です。これは USB ハブが組み込まれているデバイスや、同じ製品名または同じ製造元の複数のインタフェースがある特別な HID インタフェースで問題になります。Product ID と Vendor ID を合わせると単一のインタフェースの固有名を作成できるため、この問題を防げます。したがって、ライブラリで必要が無い場合でも、この問題を防ぐためにそれらを使うことをお勧めします。
ただし、Vendor ID や Product ID と異なり、Usage Page と Usage は通信を成功させるために必要です。

言うまでもなく、使っているライブラリに関係なく、終了したらインタフェースを必ず閉じる必要があります。オペレーティングシステムと特定の環境によっては、明示的に接続が閉じられていない場合、後で他のクライアントまたは同じクライアントの他のインスタンスに接続しなおした時に問題が発生する可能性があります。
