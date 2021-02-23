# `midi_util` グループ {#group__midi__util}

<!---
  original document: 0.10.9:docs/internals_midi_util.md
  git diff 0.10.9 HEAD -- docs/internals_midi_util.md | cat
-->

## 概要

| メンバー                      | 説明                                        
--------------------------------|---------------------------------------------
| `enum `[`midi_packet_length_t`](#group__midi__util_1gae29ff56aee2b430ffe53933b97e5e79e) | 可能なパケット長の値の列挙型。
| `public bool `[`midi_is_statusbyte`](#group__midi__util_1ga12e3b42ff9cbb4b4f2bc455fc8743ee5)`(uint8_t theByte)` | 指定されたバイトがステータスバイトであるかどうかを検査します。
| `public bool `[`midi_is_realtime`](#group__midi__util_1gad2f52c363e34a8000d80c983c324e2d7)`(uint8_t theByte)` | 指定されたバイトがリアルタイムメッセージであるかどうかを検査します。
| `public `[`midi_packet_length_t`](#group__midi__util_1gae29ff56aee2b430ffe53933b97e5e79e)` `[`midi_packet_length`](#group__midi__util_1gaa168b43af6ae9de0debce1625e4b8175)`(uint8_t status)` | 指定されたステータスバイトに関連付けられたパケットの長さを調べます。

## メンバー

#### `enum `[`midi_packet_length_t`](#group__midi__util_1gae29ff56aee2b430ffe53933b97e5e79e) {#group__midi__util_1gae29ff56aee2b430ffe53933b97e5e79e}

| 値                            | 説明                                        
--------------------------------|---------------------------------------------
UNDEFINED            | 
ONE            | 
TWO            | 
THREE            | 

可能なパケット長の値の列挙型。

#### `public bool `[`midi_is_statusbyte`](#group__midi__util_1ga12e3b42ff9cbb4b4f2bc455fc8743ee5)`(uint8_t theByte)` {#group__midi__util_1ga12e3b42ff9cbb4b4f2bc455fc8743ee5}

指定されたバイトがステータスバイトであるかどうかを検査します。

#### パラメータ
* `theByte` 検査するバイト

#### 返り値
指定されたバイトが MIDI ステータスバイトの場合は true

#### `public bool `[`midi_is_realtime`](#group__midi__util_1gad2f52c363e34a8000d80c983c324e2d7)`(uint8_t theByte)` {#group__midi__util_1gad2f52c363e34a8000d80c983c324e2d7}

指定されたバイトがリアルタイムメッセージであるかどうかを検査します。

#### パラメータ
* `theByte` 検査するバイト

#### 返り値
リアルタイムメッセージの場合は true、それ以外の場合は false

#### `public `[`midi_packet_length_t`](#group__midi__util_1gae29ff56aee2b430ffe53933b97e5e79e)` `[`midi_packet_length`](#group__midi__util_1gaa168b43af6ae9de0debce1625e4b8175)`(uint8_t status)` {#group__midi__util_1gaa168b43af6ae9de0debce1625e4b8175}

指定されたステータスバイトに関連付けられたパケットの長さを調べます。

#### パラメータ
* `status` ステータスバイト

#### 返り値
パケットの長さ。バイトがステータスバイトではない場合、あるいは sysex ステータスバイトの場合は、UNDEFINED を返します。

