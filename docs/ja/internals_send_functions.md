# `send_functions` グループ {#group__send__functions}

<!---
  original document: 0.10.9:docs/internals_send_functions.md
  git diff 0.10.9 HEAD -- docs/internals_send_functions.md | cat
-->

これらは、デバイスを介して MIDI データを送信するために使う関数です。

## 概要

メンバー                        | 説明                                        
--------------------------------|---------------------------------------------
`public void `[`midi_send_cc`](#group__send__functions_1gaaf884811c92df405ca8fe1a00082f960)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t val)` | 指定されたデバイスを介して、コントロールチェンジメッセージを送信します。
`public void `[`midi_send_noteon`](#group__send__functions_1ga467bcf46dbf03ec269ce565b46bc2775)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t vel)` | 指定されたデバイスを介してノートオンメッセージを送信します。
`public void `[`midi_send_noteoff`](#group__send__functions_1gaedb7d8805425eef5d47d57ddcb4c7a49)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t vel)` | 指定されたデバイスを介してノートオフメッセージを送信します。
`public void `[`midi_send_aftertouch`](#group__send__functions_1ga0014847571317a0e34b2ef46a6bc584f)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t note_num,uint8_t amt)` | 指定されたデバイスを介してアフタータッチメッセージを送信します。
`public void `[`midi_send_pitchbend`](#group__send__functions_1gae5a4a1e71611e7534be80af9ce3d3491)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,int16_t amt)` | 指定されたデバイスを介してピッチベンドメッセージを送信します。
`public void `[`midi_send_programchange`](#group__send__functions_1ga7b15588ef25e5e1ff09c2afc3151ce86)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num)` | 指定されたデバイスを介してプログラムチェンジメッセージを送信します。
`public void `[`midi_send_channelpressure`](#group__send__functions_1gaf23e69fdf812e89c0036f51f88ab2e1b)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t amt)` | 指定されたデバイスを介してチャンネルプレッシャーメッセージを送信します。
`public void `[`midi_send_clock`](#group__send__functions_1ga4e1b11a7cdb0875f6e03ce7c79c581aa)`(`[`MidiDevice`](#struct__midi__device)` * device)` | 指定されたデバイスを介してクロックメッセージを送信します。
`public void `[`midi_send_tick`](#group__send__functions_1ga2b43c7d433d940c5b907595aac947972)`(`[`MidiDevice`](#struct__midi__device)` * device)` | 指定されたデバイスを介してティックメッセージを送信します。
`public void `[`midi_send_start`](#group__send__functions_1ga1569749a8d58ccc56789289d7c7245cc)`(`[`MidiDevice`](#struct__midi__device)` * device)` | 指定されたデバイスを介してスタートメッセージを送信します。
`public void `[`midi_send_continue`](#group__send__functions_1gaed5dc29d754a27372e89ab8bc20ee120)`(`[`MidiDevice`](#struct__midi__device)` * device)` | 指定されたデバイスを介してコンティニューメッセージを送信します。
`public void `[`midi_send_stop`](#group__send__functions_1ga026e1a620276cb653ac501aa0d12a988)`(`[`MidiDevice`](#struct__midi__device)` * device)` | 指定されたデバイスを介してストップメッセージを送信します。
`public void `[`midi_send_activesense`](#group__send__functions_1ga9b6e4c6ce4719d2604187b325620db37)`(`[`MidiDevice`](#struct__midi__device)` * device)` | 指定されたデバイスを介してアクティブセンスメッセージを送信します。
`public void `[`midi_send_reset`](#group__send__functions_1ga3671e39a6d93ca9568fc493001af1b1b)`(`[`MidiDevice`](#struct__midi__device)` * device)` | 指定されたデバイスを介してリセットメッセージを送信します。
`public void `[`midi_send_tcquarterframe`](#group__send__functions_1ga5b85639910eec280bb744c934d0fd45a)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t time)` | 指定されたデバイスを介してタイムコードクォータフレームメッセージを送信します。
`public void `[`midi_send_songposition`](#group__send__functions_1gab1c9eeef3b57a8cd2e6128d18e85eb7f)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t pos)` | 指定されたデバイスを介してソングポジションメッセージを送信します。
`public void `[`midi_send_songselect`](#group__send__functions_1ga42de7838ba70d949af9a50f9facc3c50)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t song)` | 指定されたデバイスを介してソングセレクトメッセージを送信します。
`public void `[`midi_send_tunerequest`](#group__send__functions_1ga8db6c7e04d48e4d2266dd59118ca0656)`(`[`MidiDevice`](#struct__midi__device)` * device)` | 指定されたデバイスを介してチューンリクエストメッセージを送信します。
`public void `[`midi_send_byte`](#group__send__functions_1ga857e85eb90b288385642d4d991e09881)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t b)` | 指定されたデバイスを介してバイトを送信します。
`public void `[`midi_send_data`](#group__send__functions_1ga36e2f2e45369d911b76969361679054b)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t count,uint8_t byte0,uint8_t byte1,uint8_t byte2)` | 最大3バイトのデータを送信します。
`public void `[`midi_send_array`](#group__send__functions_1ga245243cb1da18d2cea18d4b18d846ead)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t count,uint8_t * array)` | フォーマットされた MIDI データの配列を送信します。

## メンバー

#### `public void `[`midi_send_cc`](#group__send__functions_1gaaf884811c92df405ca8fe1a00082f960)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t val)` {#group__send__functions_1gaaf884811c92df405ca8fe1a00082f960}

指定されたデバイスを介して、コントロールチェンジメッセージ(cc)を送信します。

#### パラメータ
* `device` 送信に使うデバイス

* `chan` 送信するチャンネル、0-15

* `num` コントロールチェンジナンバー

* `val` コントロールチェンジナンバーの値

#### `public void `[`midi_send_noteon`](#group__send__functions_1ga467bcf46dbf03ec269ce565b46bc2775)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t vel)` {#group__send__functions_1ga467bcf46dbf03ec269ce565b46bc2775}

指定されたデバイスを介してノートオンメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

* `chan` 送信するチャンネル、0-15

* `num` ノート番号

* `vel` ノートベロシティ

#### `public void `[`midi_send_noteoff`](#group__send__functions_1gaedb7d8805425eef5d47d57ddcb4c7a49)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t vel)` {#group__send__functions_1gaedb7d8805425eef5d47d57ddcb4c7a49}

指定されたデバイスを介してノートオフメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

* `chan` 送信するチャンネル、0-15

* `num` ノート番号

* `vel` ノートベロシティ

#### `public void `[`midi_send_aftertouch`](#group__send__functions_1ga0014847571317a0e34b2ef46a6bc584f)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t note_num,uint8_t amt)` {#group__send__functions_1ga0014847571317a0e34b2ef46a6bc584f}

指定されたデバイスを介してアフタータッチメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

* `chan` 送信するチャンネル、0-15

* `note_num` ノート番号

* `amt` アフタータッチ量

#### `public void `[`midi_send_pitchbend`](#group__send__functions_1gae5a4a1e71611e7534be80af9ce3d3491)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,int16_t amt)` {#group__send__functions_1gae5a4a1e71611e7534be80af9ce3d3491}

指定されたデバイスを介してピッチベンドメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

* `chan` 送信するチャンネル、0-15

* `amt` ベンド量の範囲: -8192..8191、0 はベンドしないことを意味します

#### `public void `[`midi_send_programchange`](#group__send__functions_1ga7b15588ef25e5e1ff09c2afc3151ce86)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num)` {#group__send__functions_1ga7b15588ef25e5e1ff09c2afc3151ce86}

指定されたデバイスを介してプログラムチェンジメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

* `chan` 送信するチャンネル、0-15

* `num` 変更先のプログラム

#### `public void `[`midi_send_channelpressure`](#group__send__functions_1gaf23e69fdf812e89c0036f51f88ab2e1b)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t amt)` {#group__send__functions_1gaf23e69fdf812e89c0036f51f88ab2e1b}

指定されたデバイスを介してチャンネルプレッシャーメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

* `chan` 送信するチャンネル、0-15

* `amt` チャンネルプレッシャーの量

#### `public void `[`midi_send_clock`](#group__send__functions_1ga4e1b11a7cdb0875f6e03ce7c79c581aa)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga4e1b11a7cdb0875f6e03ce7c79c581aa}

指定されたデバイスを介してクロックメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

#### `public void `[`midi_send_tick`](#group__send__functions_1ga2b43c7d433d940c5b907595aac947972)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga2b43c7d433d940c5b907595aac947972}

指定されたデバイスを介してティックメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

#### `public void `[`midi_send_start`](#group__send__functions_1ga1569749a8d58ccc56789289d7c7245cc)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga1569749a8d58ccc56789289d7c7245cc}

指定されたデバイスを介してスタートメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

#### `public void `[`midi_send_continue`](#group__send__functions_1gaed5dc29d754a27372e89ab8bc20ee120)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1gaed5dc29d754a27372e89ab8bc20ee120}

指定されたデバイスを介してコンティニューメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

#### `public void `[`midi_send_stop`](#group__send__functions_1ga026e1a620276cb653ac501aa0d12a988)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga026e1a620276cb653ac501aa0d12a988}

指定されたデバイスを介してストップメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

#### `public void `[`midi_send_activesense`](#group__send__functions_1ga9b6e4c6ce4719d2604187b325620db37)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga9b6e4c6ce4719d2604187b325620db37}

指定されたデバイスを介してアクティブセンスメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

#### `public void `[`midi_send_reset`](#group__send__functions_1ga3671e39a6d93ca9568fc493001af1b1b)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga3671e39a6d93ca9568fc493001af1b1b}

指定されたデバイスを介してリセットメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

#### `public void `[`midi_send_tcquarterframe`](#group__send__functions_1ga5b85639910eec280bb744c934d0fd45a)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t time)` {#group__send__functions_1ga5b85639910eec280bb744c934d0fd45a}

指定されたデバイスを介してタイムコードクォータフレームメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

* `time` このクォータフレームの時間。範囲は、0..16383

#### `public void `[`midi_send_songposition`](#group__send__functions_1gab1c9eeef3b57a8cd2e6128d18e85eb7f)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t pos)` {#group__send__functions_1gab1c9eeef3b57a8cd2e6128d18e85eb7f}

指定されたデバイスを介してソングポジションメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

* `pos` ソングポジション

#### `public void `[`midi_send_songselect`](#group__send__functions_1ga42de7838ba70d949af9a50f9facc3c50)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t song)` {#group__send__functions_1ga42de7838ba70d949af9a50f9facc3c50}

指定されたデバイスを介してソングセレクトメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

* `song` 選択するソング

#### `public void `[`midi_send_tunerequest`](#group__send__functions_1ga8db6c7e04d48e4d2266dd59118ca0656)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga8db6c7e04d48e4d2266dd59118ca0656}

指定されたデバイスを介してチューンリクエストメッセージを送信します。

#### パラメータ
* `device` 送信に使うデバイス

#### `public void `[`midi_send_byte`](#group__send__functions_1ga857e85eb90b288385642d4d991e09881)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t b)` {#group__send__functions_1ga857e85eb90b288385642d4d991e09881}

指定されたデバイスを介してバイトを送信します。

これは、指定された MIDI デバイスを介してデータを送信する一般的なメソッドです。これは、この API に実装されていない sysex データまたはメッセージがある場合、それらを送信するのに役立ちます。そのようなものを見つけた場合は、私たちがそれらを追加できるように、作者に連絡してください。

#### パラメータ
* `device` 送信に使うデバイス

* `b` 送信するバイト

#### `public void `[`midi_send_data`](#group__send__functions_1ga36e2f2e45369d911b76969361679054b)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t count,uint8_t byte0,uint8_t byte1,uint8_t byte2)` {#group__send__functions_1ga36e2f2e45369d911b76969361679054b}

最大3バイトのデータを送信します。

これを使って sysex を通過できるように count に4の剰余が適用されます。

#### パラメータ
* `device` 送信に使うデバイス

* `count` 送信するバイト数、4の剰余が適用されます

* `byte0` 最初のバイト

* `byte1` 2番目のバイト。cnt % 4 != 2 の場合は無視されます

* `byte2` 3番目のバイト。cnt % 4 != 3 の場合は無視されます

#### `public void `[`midi_send_array`](#group__send__functions_1ga245243cb1da18d2cea18d4b18d846ead)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t count,uint8_t * array)` {#group__send__functions_1ga245243cb1da18d2cea18d4b18d846ead}

フォーマットされた MIDI データの配列を送信します。

sysex に使うことができます。

#### パラメータ
* `device` 送信に使うデバイス

* `count` 送信するバイト数

* `array` バイトの配列

