# `midi_device` グループ {#group__midi__device}

<!---
  original document: 0.10.9:docs/internals_midi_device.md
  git diff 0.10.9 HEAD -- docs/internals_midi_device.md | cat
-->

独自の MIDI デバイスを実装する時に、関数を使います。

実際にデバイスを介してバイトを送信するために、送信関数を設定します。このメソッドは、このデバイスで例えば midi_send_cc のような送信関数を呼ぶ時に呼ばれます。

midi_device_input を使ってデバイスからの入力データを処理し、それをデバイスに関連付けられたコールバックで渡します。

デバイスのプロセス関数の最初に呼び出される関数が必要な場合、midi_device_set_pre_input_process_func を使います。通常、入力をポーリングして midi_device_input に渡します。

## 概要

メンバー                        | 説明                                        
--------------------------------|---------------------------------------------
`define `[`MIDI_INPUT_QUEUE_LENGTH`](#group__midi__device_1ga4aaa419caebdca2bbdfc1331e79781a8)            | 
`enum `[`input_state_t`](#group__midi__device_1gac203e877d3df4275ceb8e7180a61f621) | 
`public void `[`midi_device_input`](#group__midi__device_1gad8d3db8eb35d9cfa51ef036a0a9d70db)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t cnt,uint8_t * input)` | 入力バイトを処理します。この関数はバイトを解析し、指定されたデバイスに関連する適切なコールバックを呼びます。この関数は、カスタムデバイスを作成していて、MIDI 入力が必要な場合に使います。
`public void `[`midi_device_set_send_func`](#group__midi__device_1ga59f5a46bdd4452f186cc73d9e96d4673)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_var_byte_func_t send_func)` | 出力データバイトの送信に使われるコールバック関数を設定します。これは、カスタムデバイスを作成している場合のみ使われます。ロックを気にすることなく様々な MIDI 送信関数を呼び出すことができるように、コールバック関数で割り込みを無効にすることができます。
`public void `[`midi_device_set_pre_input_process_func`](#group__midi__device_1ga4de0841b87c04fc23cb56b6451f33b69)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_no_byte_func_t pre_process_func)` | midi_device_process 呼び出しの最初に呼ばれるコールバックを設定します。これは入力データをポーリングし、midi_device_input 関数を介してデータを送信できます。カスタムデバイスを作成している場合のみ、これを使う可能性があります。
`struct `[`_midi_device`](docs/api_midi_device.md#struct__midi__device) | この構造体は、MIDI デバイスの入出力関数と処理データを表します。

## メンバー

#### `define `[`MIDI_INPUT_QUEUE_LENGTH`](#group__midi__device_1ga4aaa419caebdca2bbdfc1331e79781a8) {#group__midi__device_1ga4aaa419caebdca2bbdfc1331e79781a8}

#### `enum `[`input_state_t`](#group__midi__device_1gac203e877d3df4275ceb8e7180a61f621) {#group__midi__device_1gac203e877d3df4275ceb8e7180a61f621}

値                              | 説明                                        
--------------------------------|---------------------------------------------
IDLE            | 
ONE_BYTE_MESSAGE            | 
TWO_BYTE_MESSAGE            | 
THREE_BYTE_MESSAGE            | 
SYSEX_MESSAGE            | 

#### `public void `[`midi_device_input`](#group__midi__device_1gad8d3db8eb35d9cfa51ef036a0a9d70db)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t cnt,uint8_t * input)` {#group__midi__device_1gad8d3db8eb35d9cfa51ef036a0a9d70db}

入力バイトを処理します。この関数はバイトを解析し、指定されたデバイスに関連する適切なコールバックを呼びます。この関数は、カスタムデバイスを作成していて、MIDI 入力が必要な場合に使います。

#### パラメータ
* `device` 入力を関連付ける MIDI デバイス

* `cnt` 処理中のバイト数

* `input` 処理するバイトデータ

#### `public void `[`midi_device_set_send_func`](#group__midi__device_1ga59f5a46bdd4452f186cc73d9e96d4673)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_var_byte_func_t send_func)` {#group__midi__device_1ga59f5a46bdd4452f186cc73d9e96d4673}

出力データバイトの送信に使われるコールバック関数を設定します。これは、カスタムデバイスを作成している場合のみ使われます。ロックを気にすることなく様々な MIDI 送信関数を呼び出すことができるように、コールバック関数で割り込みを無効にすることができます。

#### パラメータ
* `device` このコールバックを関連付ける MIDI デバイス

* `send_func` 送信を行うコールバック関数

#### `public void `[`midi_device_set_pre_input_process_func`](#group__midi__device_1ga4de0841b87c04fc23cb56b6451f33b69)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_no_byte_func_t pre_process_func)` {#group__midi__device_1ga4de0841b87c04fc23cb56b6451f33b69}

midi_device_process 呼び出しの最初に呼ばれるコールバックを設定します。これは入力データをポーリングし、midi_device_input 関数を介してデータを送信できます。カスタムデバイスを作成している場合のみ、これを使う可能性があります。

#### パラメータ
* `device` このコールバックを関連付ける MIDI デバイス

* `midi_no_byte_func_t` 実際のコールバック関数

# `_midi_device` 構造体 {#struct__midi__device}

この構造体は、MIDI デバイスの入出力関数と処理データを表します。

デバイスは、実際の物理デバイス [シリアルポート、USB ポート]、または仮想デバイスを表すことができます。この構造体を直接変更する必要はありません。

## 概要

| メンバー                      | 説明                                        
--------------------------------|---------------------------------------------
`public midi_var_byte_func_t `[`send_func`](docs/api_midi_device.md#struct__midi__device_1a25d4c94b4bbccd5b98f1032b469f3ff9) | 
`public midi_three_byte_func_t `[`input_cc_callback`](docs/api_midi_device.md#struct__midi__device_1a6da5236c1bc73877728df92d213a78d1) | 
`public midi_three_byte_func_t `[`input_noteon_callback`](docs/api_midi_device.md#struct__midi__device_1aa10b15cf1a7fb825a5df0d2abbe34a1c) | 
`public midi_three_byte_func_t `[`input_noteoff_callback`](docs/api_midi_device.md#struct__midi__device_1aaf290043078534d3a5a0ea4c840eba84) | 
`public midi_three_byte_func_t `[`input_aftertouch_callback`](docs/api_midi_device.md#struct__midi__device_1acb0b4901c545cec4b28b126f2d8c315f) | 
`public midi_three_byte_func_t `[`input_pitchbend_callback`](docs/api_midi_device.md#struct__midi__device_1a305fea672caeb996f2233bf8cd2bef18) | 
`public midi_three_byte_func_t `[`input_songposition_callback`](docs/api_midi_device.md#struct__midi__device_1a5f3f13638b3fef3fc561ed1bf301d586) | 
`public midi_two_byte_func_t `[`input_progchange_callback`](docs/api_midi_device.md#struct__midi__device_1adaf1da617c9a10a9dcad00ab1959d3da) | 
`public midi_two_byte_func_t `[`input_chanpressure_callback`](docs/api_midi_device.md#struct__midi__device_1ab7ca2925c539915d43974eff604d85f7) | 
`public midi_two_byte_func_t `[`input_songselect_callback`](docs/api_midi_device.md#struct__midi__device_1a89bed8a5a55376120cfc0a62b42f057f) | 
`public midi_two_byte_func_t `[`input_tc_quarterframe_callback`](docs/api_midi_device.md#struct__midi__device_1ad9813e75d22e284f9f65a907d20600f0) | 
`public midi_one_byte_func_t `[`input_realtime_callback`](docs/api_midi_device.md#struct__midi__device_1a9448eba4afb7e43650434748db3777be) | 
`public midi_one_byte_func_t `[`input_tunerequest_callback`](docs/api_midi_device.md#struct__midi__device_1a0cb8fd53e00cf1d4202d4fa04d038e8d) | 
`public midi_sysex_func_t `[`input_sysex_callback`](docs/api_midi_device.md#struct__midi__device_1afff9a0ce641762aaef24c1e6953ec9a2) | 
`public midi_var_byte_func_t `[`input_fallthrough_callback`](docs/api_midi_device.md#struct__midi__device_1abb974ec6d734001b4a0e370f292be503) | 
`public midi_var_byte_func_t `[`input_catchall_callback`](docs/api_midi_device.md#struct__midi__device_1aae0d535129d4fd650edc98eb3f7584f8) | 
`public midi_no_byte_func_t `[`pre_input_process_callback`](docs/api_midi_device.md#struct__midi__device_1aeb0bb8923d66c23d874e177dc4265754) | 
`public uint8_t `[`input_buffer`](docs/api_midi_device.md#struct__midi__device_1a7c5684857d6af4ebc4dc12da27bd6b2a) | 
`public input_state_t `[`input_state`](docs/api_midi_device.md#struct__midi__device_1a69a687d2d1c449ec15a11c07a5722e39) | 
`public uint16_t `[`input_count`](docs/api_midi_device.md#struct__midi__device_1a68dea8e7b6151e89c85c95caa612ee5d) | 
`public uint8_t `[`input_queue_data`](docs/api_midi_device.md#struct__midi__device_1ada41de021135dc423abedcbb30f366ff) | 
`public `[`byteQueue_t`](#structbyte_queue__t)` `[`input_queue`](#struct__midi__device_1a49c8538a8a02193c58e28a56eb695d8f) | 

## メンバー

#### `public midi_var_byte_func_t `[`send_func`](docs/api_midi_device.md#struct__midi__device_1a25d4c94b4bbccd5b98f1032b469f3ff9) {#struct__midi__device_1a25d4c94b4bbccd5b98f1032b469f3ff9}

#### `public midi_three_byte_func_t `[`input_cc_callback`](docs/api_midi_device.md#struct__midi__device_1a6da5236c1bc73877728df92d213a78d1) {#struct__midi__device_1a6da5236c1bc73877728df92d213a78d1}

#### `public midi_three_byte_func_t `[`input_noteon_callback`](docs/api_midi_device.md#struct__midi__device_1aa10b15cf1a7fb825a5df0d2abbe34a1c) {#struct__midi__device_1aa10b15cf1a7fb825a5df0d2abbe34a1c}

#### `public midi_three_byte_func_t `[`input_noteoff_callback`](docs/api_midi_device.md#struct__midi__device_1aaf290043078534d3a5a0ea4c840eba84) {#struct__midi__device_1aaf290043078534d3a5a0ea4c840eba84}

#### `public midi_three_byte_func_t `[`input_aftertouch_callback`](docs/api_midi_device.md#struct__midi__device_1acb0b4901c545cec4b28b126f2d8c315f) {#struct__midi__device_1acb0b4901c545cec4b28b126f2d8c315f}

#### `public midi_three_byte_func_t `[`input_pitchbend_callback`](docs/api_midi_device.md#struct__midi__device_1a305fea672caeb996f2233bf8cd2bef18) {#struct__midi__device_1a305fea672caeb996f2233bf8cd2bef18}

#### `public midi_three_byte_func_t `[`input_songposition_callback`](docs/api_midi_device.md#struct__midi__device_1a5f3f13638b3fef3fc561ed1bf301d586) {#struct__midi__device_1a5f3f13638b3fef3fc561ed1bf301d586}

#### `public midi_two_byte_func_t `[`input_progchange_callback`](docs/api_midi_device.md#struct__midi__device_1adaf1da617c9a10a9dcad00ab1959d3da) {#struct__midi__device_1adaf1da617c9a10a9dcad00ab1959d3da}

#### `public midi_two_byte_func_t `[`input_chanpressure_callback`](docs/api_midi_device.md#struct__midi__device_1ab7ca2925c539915d43974eff604d85f7) {#struct__midi__device_1ab7ca2925c539915d43974eff604d85f7}

#### `public midi_two_byte_func_t `[`input_songselect_callback`](docs/api_midi_device.md#struct__midi__device_1a89bed8a5a55376120cfc0a62b42f057f) {#struct__midi__device_1a89bed8a5a55376120cfc0a62b42f057f}

#### `public midi_two_byte_func_t `[`input_tc_quarterframe_callback`](docs/api_midi_device.md#struct__midi__device_1ad9813e75d22e284f9f65a907d20600f0) {#struct__midi__device_1ad9813e75d22e284f9f65a907d20600f0}

#### `public midi_one_byte_func_t `[`input_realtime_callback`](docs/api_midi_device.md#struct__midi__device_1a9448eba4afb7e43650434748db3777be) {#struct__midi__device_1a9448eba4afb7e43650434748db3777be}

#### `public midi_one_byte_func_t `[`input_tunerequest_callback`](docs/api_midi_device.md#struct__midi__device_1a0cb8fd53e00cf1d4202d4fa04d038e8d) {#struct__midi__device_1a0cb8fd53e00cf1d4202d4fa04d038e8d}

#### `public midi_sysex_func_t `[`input_sysex_callback`](docs/api_midi_device.md#struct__midi__device_1afff9a0ce641762aaef24c1e6953ec9a2) {#struct__midi__device_1afff9a0ce641762aaef24c1e6953ec9a2}

#### `public midi_var_byte_func_t `[`input_fallthrough_callback`](docs/api_midi_device.md#struct__midi__device_1abb974ec6d734001b4a0e370f292be503) {#struct__midi__device_1abb974ec6d734001b4a0e370f292be503}

#### `public midi_var_byte_func_t `[`input_catchall_callback`](docs/api_midi_device.md#struct__midi__device_1aae0d535129d4fd650edc98eb3f7584f8) {#struct__midi__device_1aae0d535129d4fd650edc98eb3f7584f8}

#### `public midi_no_byte_func_t `[`pre_input_process_callback`](docs/api_midi_device.md#struct__midi__device_1aeb0bb8923d66c23d874e177dc4265754) {#struct__midi__device_1aeb0bb8923d66c23d874e177dc4265754}

#### `public uint8_t `[`input_buffer`](docs/api_midi_device.md#struct__midi__device_1a7c5684857d6af4ebc4dc12da27bd6b2a) {#struct__midi__device_1a7c5684857d6af4ebc4dc12da27bd6b2a}

#### `public input_state_t `[`input_state`](docs/api_midi_device.md#struct__midi__device_1a69a687d2d1c449ec15a11c07a5722e39) {#struct__midi__device_1a69a687d2d1c449ec15a11c07a5722e39}

#### `public uint16_t `[`input_count`](docs/api_midi_device.md#struct__midi__device_1a68dea8e7b6151e89c85c95caa612ee5d) {#struct__midi__device_1a68dea8e7b6151e89c85c95caa612ee5d}

#### `public uint8_t `[`input_queue_data`](docs/api_midi_device.md#struct__midi__device_1ada41de021135dc423abedcbb30f366ff) {#struct__midi__device_1ada41de021135dc423abedcbb30f366ff}

#### `public `[`byteQueue_t`](#structbyte_queue__t)` `[`input_queue`](#struct__midi__device_1a49c8538a8a02193c58e28a56eb695d8f) {#struct__midi__device_1a49c8538a8a02193c58e28a56eb695d8f}

