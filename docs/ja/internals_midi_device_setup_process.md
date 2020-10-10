# `midi_device_setup_process` グループ {#group__midi__device__setup__process}

<!---
  original document: 0.10.9:docs/internals_midi_device_setup_process.md
  git diff 0.10.9 HEAD -- docs/internals_midi_device_setup_process.md | cat
-->

これらは、デバイスを初期化して実行するために使う必要があるメソッドです。

## 概要

メンバー                        | 説明                                        
--------------------------------|---------------------------------------------
`public void `[`midi_device_init`](#group__midi__device__setup__process_1gaf29deddc94ea98a59daa0bde1aefd9d9)`(`[`MidiDevice`](#struct__midi__device)` * device)` | デバイスを初期化します。
`public void `[`midi_device_process`](#group__midi__device__setup__process_1gaa3d5993d0e998a1b59bbf5ab9c7b492b)`(`[`MidiDevice`](#struct__midi__device)` * device)` | 入力データを処理します。

## メンバー

#### `public void `[`midi_device_init`](#group__midi__device__setup__process_1gaf29deddc94ea98a59daa0bde1aefd9d9)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__midi__device__setup__process_1gaf29deddc94ea98a59daa0bde1aefd9d9}

デバイスを初期化します。

問題のデバイスを使う前にこれを呼び出す必要があります。

#### パラメータ
* `device` 初期化するデバイス

#### `public void `[`midi_device_process`](#group__midi__device__setup__process_1gaa3d5993d0e998a1b59bbf5ab9c7b492b)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__midi__device__setup__process_1gaa3d5993d0e998a1b59bbf5ab9c7b492b}

入力データを処理します。

このメソッドは入力処理を駆動します。入力コールバックが呼び出されることが予想される場合は、このメソッドを頻繁に呼び出す必要があります。

#### パラメータ
* `device` 処理するデバイス

