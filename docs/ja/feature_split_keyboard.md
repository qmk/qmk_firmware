# 分割キーボード

<!---
  original document:0.14.14:docs/feature_split_keyboard.md
  git diff 0.14.14 HEAD -- docs/feature_split_keyboard.md | cat
-->

QMK ファームウェアリポジトリの多くのキーボードは、"分割"キーボードです。それらは2つのコントローラを使います — 1つは USB に接続し、もう1つは TRRS または同様のケーブルを介してシリアルまたは I<sup>2</sup>C 接続で接続します。

分割キーボードには多くの利点がありますが、有効にするには追加の作業が必要です。

QMK ファームウェアには、任意のキーボードで使用可能な一般的な実装と、多くのキーボード固有の実装があります。

このため、主に Let's Split とその他のキーボードで使われる一般的な実装について説明します。

!> ARM split は、'serial' と 'serial_usart' ドライバを使う場合、ほとんどの QMK サブシステムをサポートします。I2C スレーブは現在のところサポートされていません。

## 互換性の概要

| Transport | AVR | ARM |
|------------------------------|--------------------|--------------------|
| ['serial'](ja/serial_driver.md) | :heavy_check_mark: | :white_check_mark: <sup>1</sup> |
| I2C | :heavy_check_mark: |  |

注意:

1. ハードウェアとソフトウェアの両方の制限は、[ドライバーのドキュメント](ja/serial_driver.md)の中で説明されます。

## ハードウェア設定

2つの Pro Micro 互換のコントローラを使っており、キーボードの左右を接続するために TRRS ジャックを使っていることを前提とします。

### ハードウェア要件

左右それぞれのキーボードマトリックスのためのダイオードとスイッチとは別に、2個の TRRS ソケットと 1本の TRRS ケーブルが必要です。

あるいは、少なくとも3本のワイヤがあるケーブルとソケットを使うことができます。

キーボードの左右間で通信するために I<sup>2</sup>C を使いたい場合は、少なくとも4本のワイヤを備えたケーブルと 2個の 4.7kΩ プルアップ抵抗が必要です。

#### 考慮事項

最も一般的に使われる接続は、TRRS ケーブルとジャックです。これらは4本のワイヤを提供し、分割キーボードに非常に有用で、簡単に見つけることができます。

ただし、ワイヤのうちの1本が Vcc を供給するため、キーボードはホットプラグ不可能です。TRRS ケーブルを抜き差しする前に、必ずキーボードのUSB接続をはずす必要があります。そうしなければ、コントローラを短絡させたり、もっと悪いことが起こるかもしれません。

別のオプションは電話ケーブルを使うことです (例えば、旧式の RJ-11/RJ-14 ケーブル)。実際に4本のワイヤ/レーンをサポートするものを使うようにしてください。

ただし、USB ケーブル、SATA ケーブル、そして単に4本の電線でもコントローラ間の通信に使用できることがわかっています。

!> コントローラ間の通信に USB ケーブルを使っても問題ありませんが、コネクタは通常の USB 接続と間違えられるかもしれず、配線方法によってはキーボードが短絡する可能性があります。このため、分割キーボードの接続のためにはお勧めできません。

### シリアル配線

2つの Pro Micro 間で GND、Vcc、D0/D1/D2/D3 (別名 PD0/PD1/PD2/PD3) を TRS/TRRS ケーブルの3本のワイヤで接続します。

?> ここで使われるピンは実際には以下の `SOFT_SERIAL_PIN` によって設定されることに注意してください。

<img alt="sk-pd0-connection-mono" src="https://user-images.githubusercontent.com/2170248/92296488-28e9ad80-ef70-11ea-98be-c40cb48a0319.JPG" width="48%"/>
<img alt="sk-pd2-connection-mono" src="https://user-images.githubusercontent.com/2170248/92296490-2d15cb00-ef70-11ea-801f-5ace313013e6.JPG" width="48%"/>

### I<sup>2</sup>C 配線

2つの Pro Micro 間で GND、Vcc、さらに SCL と SDA (それぞれ 別名 PD0/ピン3 および PD1/ピン2) を TRRS ケーブルの4本のワイヤで接続します。

プルアップ抵抗はキーボードの左右どちら側にも配置することができます。もし各側を単独で使いたい場合は、4つの抵抗を使い、両側にプルアップ抵抗を配置することもできます。
接続されたシステムの総抵抗は、配置や数に関係なく、2.2k-10kΩ で仕様の範囲内であり、'理想的'には 4.7kΩ である必要があることに注意してください。

<img alt="sk-i2c-connection-mono" src="https://user-images.githubusercontent.com/2170248/92297182-92b98580-ef77-11ea-9d7d-d6033914af43.JPG" width="50%"/>

## ファームウェア設定

分割キーボード機能を有効にするには、以下を `rules.mk` に追加してください:

```make
SPLIT_KEYBOARD = yes
```

カスタムトランスポート (通信メソッド)を使っている場合は、以下を追加する必要もあります:

```make
SPLIT_TRANSPORT = custom
```

### 左右の設定

デフォルトでは、ファームウェアはどちら側がどちらであるかを認識しません; 決定するには幾つかの助けが必要です。これを行うには幾つかの方法があり、以下に優先順に列挙します。

#### ピンによる左右の設定

左右を決定するためにコントローラ上のピンを読むようにファームウェアを設定することができます。これを行うには、以下を `config.h` ファイルに追加します:

```c
#define SPLIT_HAND_PIN B7
```

これは指定されたピンを読み込みます。デフォルトでは、high の場合、コントローラはそれを左側だと仮定し、low の場合、それは右側であると仮定します。

この挙動は、以下を `config.h` ファイルに追加することで逆にすることができます:

```c
#define	SPLIT_HAND_PIN_LOW_IS_LEFT
```

#### マトリックスピンによる左右の設定

左右を決定するためにコントローラのキーマトリックスピンを読むようにファームウェアを設定することができます。これを行うには、以下を `config.h` ファイルに追加します:

```c
#define SPLIT_HAND_MATRIX_GRID D0, F1
```

最初のピンは出力ピンで、2つ目は入力ピンです。

キーマトリックスに未使用の交点があるキーボードがあります。この設定は、左右の決定にこれらの未使用の交点の1つを使用します。

通常、ダイオードが交点に接続されている場合、左側と判断されます。次の定義を追加すると、右側と判断されます。

```c
#define SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT
```

これまで使われていなかった交差点にダイオードを追加することは、事実上、その場所に押されているキーがあることをファームウェアに伝えることであることに注意してください。`MATRIX_MASKED` を定義し、キーボード設定に `matrix_row_t matrix_mask[MATRIX_ROWS]` 配列を定義することで、qmk に交差点を無視するように指示することができます。1つの値の各ビット(最下位ビットから開始)は、その交差点でのキーの押下に注意を払うかどうかを qmk に指示するために使われます。

`MATRIX_MASKED` は `SPLIT_HAND_MATRIX_GRID` を正常に使うためには必要ありませんが、これが無いと、キーボードが接続された状態でコンピュータをサスペンドしようとするときに、マトリックスが常に少なくとも1つのキー押下を報告するという問題を経験する可能性があります。

#### EEPROM による左右の設定

このメソッドは永続ストレージ(`EEPROM`)のフラグを設定することで、キーボードの左右を設定します。これはコントローラが最初に起動する時にチェックされ、キーボードのどちら側であるかとキーボードのレイアウトの向きを決定します。


このメソッドを有効にするには、以下を `config.h` ファイルに追加します:

```c
#define EE_HANDS
```

ただし、各コントローラに正しい側の EEPROM ファイルを書き込む必要があります。これを手動で行うこともできますが、ファームウェアを書き込む時にこれを行う avrdude および dfu のターゲットが存在します。

* `:avrdude-split-left`
* `:avrdude-split-right`
* `:dfu-split-left`
* `:dfu-split-right`
* `:dfu-util-split-left`
* `:dfu-util-split-right`

例:

```
make crkbd:default:avrdude-split-left
```

この設定は、`EEP_RST` キーや `eeconfig_init()` 関数を使って EEPROM を再初期化する時には変更されません。ただし、ファームウェアの組み込みオプション以外で EEPROM をリセット([QMK Toolbox]() の "Reset EEPROM" ボタンの動作のように、`EEPROM` を上書きするファイルを書きこむなど)した場合、`EEPROM` ファイルを再書き込みする必要があります。

`EEPROM` ファイルは、QMK ファームウェアのリポジトリ内の[ここ](https://github.com/qmk/qmk_firmware/tree/master/quantum/split_common)にあります。

#### `#define` による左右の設定

コンパイル時に左右を設定することができます。これは以下を `config.h` ファイルに追加することで行うことができます:

```c
#define MASTER_RIGHT
```

あるいは

```c
#define MASTER_LEFT
```

どちらも定義されていない場合、左右のデフォルトは `MASTER_LEFT` になります。


### 通信オプション

全ての分割キーボードが同一であるとは限らないため、`config.h` ファイル内で設定することができる多くの追加のオプションがあります。

```c
#define USE_I2C
```

これは、分割キーボードトランスポートの I<sup>2</sup>C サポートの使用を構成します (AVRのみ)。

```c
#define SOFT_SERIAL_PIN D0
```

これはシリアル通信用に使われるピンを設定します。シリアルを使っていない場合は、これを定義する必要はありません。

ただし、キーボード上でシリアルおよび I<sup>2</sup>C を使っている場合は、これを設定し、D0 および D1 以外の値に設定する必要があります (これらは I<sup>2</sup>C 通信のために使われます)。

```c
#define SELECT_SOFT_SERIAL_SPEED {#}`
```

シリアル通信に問題がある場合は、この値を変更して、シリアル用の通信速度を制御することができます。デフォルトは1で、可能な値は以下の通りです:

* **`0`**: 約189kbps (実験用途専用)
* **`1`**: 約137kbps (デフォルト)
* **`2`**: 約75kbps
* **`3`**: 約39kbps
* **`4`**: 約26kbps
* **`5`**: 約20kbps

```c
#define FORCED_SYNC_THROTTLE_MS 100
```

マスターからスレーブへのデータの同期を強制的に行うまでの最大ミリ秒を設定します。通常は、データの_変更_があるたびにこの同期が行われますが、安全のため、最後の同期以降に変更が検出されなかった場合に、このミリ秒後にデータ転送が行われます。

```c
#define SPLIT_MAX_CONNECTION_ERRORS 10
```
スレーブ部が接続されていないと見なされるまでの、マスター部からの失敗した通信の試行の最大数(スキャンサイクルごとに1回)を設定します。これにより、スレーブ部を接続せずにマスター部を使うことができます。

0に設定すると、切断チェックを完全に無効にします。

```c
#define SPLIT_CONNECTION_CHECK_TIMEOUT 500
```
通信が切断済みとしてフラグを立てられた後で、マスター部分がスレーブへの全ての接続の試行をブロックする時間(ミリ秒)(上記の `SPLIT_MAX_CONNECTION_ERRORS` を参照してください)。

前回の試行からこの時間が経過するたびに、1回の通信の試行が許可されます。試行が成功した場合、通信は再び機能していると見なされます。

0に設定すると、切断中の通信の抑制を無効にします。これにより、ファームウェアのサイズを数バイト節約することができます。

```c
#define SPLIT_TRANSPORT_MIRROR
```

これは、スレーブ側でマスター側のキー押下に反応したり、キー押下を知るための機能のために、マスター側のマトリックスをスレーブ側にミラーリングします。この機能の目的は、キーイベントの表面的な使用(例えば、キー押下に反応する RGB)をサポートすることです。この機能を有効にすると、分割通信プロトコルにオーバーヘッドが追加され、マトリックスのスキャン速度に悪影響を及ぼす可能性があります。

```c
#define SPLIT_LAYER_STATE_ENABLE
```

分割キーボードの両側でレイヤー状態の同期を有効にします。この機能の主な目的は、現在アクティブなレイヤーの OLED 表示などの使用をサポートできるようにすることです。この機能を有効にすると、分割通信プロトコルにオーバーヘッドが追加され、マトリックスのスキャン速度に悪影響を及ぼす可能性があります。

```c
#define SPLIT_LED_STATE_ENABLE
```

分割キーボードの両側でホスト LED 状態 (caps lock、num lock など) の同期を有効にします。この機能の主な目的は、ホスト LED の状態の OLED 表示などの使用をサポートできるようにすることです。この機能を有効にすると、分割通信プロトコルにオーバーヘッドが追加され、マトリックスのスキャン速度に悪影響を及ぼす可能性があります。

```c
#define SPLIT_MODS_ENABLE
```

モディファイアの状態(normal、weak、oneshot)を分割キーボードのプライマリではない側へ転送できるようにします。この機能の目的は、モディファイアの状態の表面的な使用(例えば、OLED 画面に状態を表示)をサポートすることです。この機能を有効にすると、分割通信プロトコルにオーバーヘッドが追加され、マトリックスのスキャン速度に悪影響を及ぼす可能性があります。

```c
#define SPLIT_WPM_ENABLE
```

分割キーボードのスレーブ側への現在の WPM の転送を有効にします。この機能の目的は、WPM の表面的な使用(例えば、OLED 画面に現在の値を表示)をサポートすることです。この機能を有効にすると、分割通信プロトコルにオーバーヘッドが追加され、マトリックスのスキャン速度に悪影響を及ぼす可能性があります。

```c
#define SPLIT_OLED_ENABLE
```

分割キーボードのスレーブ側への現在の OLED のオン/オフ の状態の転送を有効にします。この機能の目的は、状態(オン/オフ状態のみ)の同期をサポートすることです。この機能を有効にすると、分割通信プロトコルにオーバーヘッドが追加され、マトリックスのスキャン速度に悪影響を及ぼす可能性があります。

```c
#define SPLIT_ST7565_ENABLE
```

分割キーボードのスレーブ側への現在の ST7565 オン/オフ状態の転送を有効にします。この機能の目的は、状態(オン/オフ状態のみ)の同期をサポートすることです。この機能を有効にすると、分割通信プロトコルにオーバーヘッドが追加され、マトリックスのスキャン速度に悪影響を及ぼす可能性があります。

### 両側の独自のデータ同期 :id=custom-data-sync

QMK の分割トランスポートにより、キーボードレベルとユーザレベルの両方で任意のデータのトランザクションが可能になります。これはリモートプロシージャ―コールをモデル化したもので、マスターがスレーブ側の関数を呼び出し、マスターからスレーブにデータを送り、スレーブ側で処理し、スレーブからマスターにデータを送り返す機能を持ちます。

これを利用するために、キーボードやユーザ/キーマップは、_トランザクション ID_ のカンマ区切りのリストを定義できます:

```c
// キーボードレベルのデータの同期:
#define SPLIT_TRANSACTION_IDS_KB KEYBOARD_SYNC_A, KEYBOARD_SYNC_B
// ユーザレベルの同期:
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_A, USER_SYNC_B, USER_SYNC_C
```

これらの_トランザクション ID_ は、次に分割トランスポートに登録するスレーブ側のハンドラ関数が必要です。例えば:

```c
typedef struct _master_to_slave_t {
    int m2s_data;
} master_to_slave_t;

typedef struct _slave_to_master_t {
    int s2m_data;
} slave_to_master_t;

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
    slave_to_master_t *s2m = (slave_to_master_t*)out_data;
    s2m->s2m_data = m2s->m2s_data + 5; // whatever comes in, add 5 so it can be sent back
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
}
```

次に、マスター側はスレーブ側のハンドラを呼び出すことができます - 通常のキーボード機能への影響を最小限にするために、 データを同期しようとするキーボードレベルやユーザレベルのコードを調整する必要があります:

```c
void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // スレーブと500msごとにやり取りする
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            master_to_slave_t m2s = {6};
            slave_to_master_t s2m = {0};
            if(transaction_rpc_exec(USER_SYNC_A, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
                last_sync = timer_read32();
                dprintf("Slave value: %d\n", s2m.s2m_data); // スレーブ側が 5 を足すので、この値は 11 になります。
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
}
```

!> 左右の間のデータ同期は、マスター側の_ハウスキーピングタスク_の中で行うことをお勧めします。これにより、障害が発生した時にタイムリーに再試行することができます。

一方向のデータ転送のみが必要な場合は、ヘルパーメソッドが提供されます:

```c
bool transaction_rpc_exec(int8_t transaction_id, uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer);
bool transaction_rpc_send(int8_t transaction_id, uint8_t initiator2target_buffer_size, const void *initiator2target_buffer);
bool transaction_rpc_recv(int8_t transaction_id, uint8_t target2initiator_buffer_size, void *target2initiator_buffer);
```

デフォルトでは、受信データと送信データはそれぞれ最大32バイトに制限されています。必要に応じてサイズを変更できます:

```c
// マスターからスレーブへ:
#define RPC_M2S_BUFFER_SIZE 48
// スレーブからマスターへ:
#define RPC_S2M_BUFFER_SIZE 48
```

### ハードウェア設定オプション

ハードウェアのセットアップ方法に基づいて、設定する必要のある設定が幾つかあります。

```c
#define MATRIX_ROW_PINS_RIGHT { <row pins> }
#define MATRIX_COL_PINS_RIGHT { <col pins> }
```

これにより、右側のマトリックスに異なるピンのセットを指定することができます。これは、左右の形が違うキーボード (Keebio の Quefrency など)で、左右で別の構成が必要な場合に便利です。

```c
#define DIRECT_PINS_RIGHT { { F1, F0, B0, C7 }, { F4, F5, F6, F7 } }
```

これにより右側のための異なる直接ピンのセットを指定することができます。

```c
#define ENCODERS_PAD_A_RIGHT { encoder1a, encoder2a }
#define ENCODERS_PAD_B_RIGHT { encoder1b, encoder2b }
```

これにより右側のための異なるエンコーダピンのセットを指定することができます。

```c
#define RGBLIGHT_SPLIT
```

このオプションは、分割キーボードのコントローラ間で RGB ライトモードの同期を有効にします。これはコントローラに直接配線されている RGB LED を持つキーボード用です (つまり、それらは TRRS ケーブルで "追加データ"オプションを使っていません)。

```c
#define RGBLED_SPLIT { 6, 6 }
```

これは各コントローラに直接接続されている LED の数を設定します。最初の数は左側、2番目の数は右側です。

?> この設定は `RGBLIGHT_SPLIT` が有効になっていることを意味し、有効になっていない場合は強制的に有効にします。


```c
#define SPLIT_USB_DETECT
```

このオプションは、スタートアップの挙動を変更して、マスタ/スレーブを移譲するためにアクティブな USB 接続に聞き耳を立てます。このオプションを有効にして USB 通信を行った場合、こちら側がマスターであると仮定し、そうでなければスレーブであると仮定します。

このオプションが無い場合、物理的な USB 接続の電圧を検出できる側がマスターになります (VBUS 検出)。

ChibiOS/ARM ではデフォルトで有効になっています。

?> この設定はバッテリパックを使ったデモの機能を停止します。

```c
#define SPLIT_USB_TIMEOUT 2000
```
これは、`SPLIT_USB_DETECT` を使う時のマスタ/スレーブを検出する場合の最大タイムアウトを設定します。

```c
#define SPLIT_USB_TIMEOUT_POLL 10
```
これは `SPLIT_USB_DETECT` を使う時のマスタ/スレーブを検出する場合のポーリング頻度を設定します

## ハードウェアの考慮事項と改造

マスター/スレーブの移譲は、VBUS 接続の電圧を検出するか、USB 通信を待機 (`SPLIT_USB_DETECT`) することで行われます。Pro Micro のボードはそのままで VBUS 検出を使用でき、`SPLIT_USB_DETECT` の有無に関わらず使用できます。

全てではありませんが、多くの ARM ボードは、VBUS 検出をサポートしません。ARM ボードが VBUS 検出に対応していないことが一般的なため、ARM を対象とした場合は `SPLIT_USB_DETECT` が自動的に定義されます(技術的には ChibiOS が対象の場合)。

### Teensy ボード

Teensy のボードはそのままでは VBUS 検出が無いため、`SPLIT_USB_DETECT` を定義する必要があります。Teensy 2.0 と Teensy++ 2.0 には、VBUS 検出を追加するための簡単なハードウェア改造がありますので、`SPLIT_USB_DETECT` オプションは必要ありません。

以下の幾つかのことが必要なだけです:

* ナイフ (理想的には x-acto ナイフ)
* はんだステーションまたはホットエアステーション
* [PMEG2005EH](https://www.digikey.jp/product-detail/ja/nexperia-usa-inc/PMEG2005EH115/1727-3853-1-ND/1589924) などの適切なショットキーダイオード

Teensy の背面にある5Vとセンターパッドの間の小さなプリントパターンをカットする必要があります。

それが済んだら、5V パッドからセンターパッドにダイオードをはんだ付けする必要があります。

パッドが小さすぎてショットキーダイオードを適切に配置するには近すぎるため、上のレギュレータブロックの5Vパッドを使う必要があるかもしれません。

![Teensy++ 2.0](https://i.imgur.com/BPEC5n5.png)

## 追加のリソース(英語)

Nicinabox には Let's Split キーボードのための[非常に優れた詳細なガイド](https://github.com/nicinabox/lets-split-guide)があり、トラブルシューティング情報を含む知っておくべきほとんど全てをカバーします。

ただし、RGB ライトセクションは、RGB Split コードが QMK ファームウェアに追加されるずっと前に書かれたため、古くなっています。ガイドに従う代わりに、各 LED テーブ(訳注: LED strip とも呼びます)を直接コントローラに配線します。

<!-- I may port this information later, but for now ... it's very nice, and covers everything -->
