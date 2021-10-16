# `sysex_tools` グループ {#group__sysex__tools}

<!---
  original document: 0.10.9:docs/internals_sysex_tools.md
  git diff 0.10.9 HEAD -- docs/internals_sysex_tools.md | cat
-->

## 概要

| メンバー                      | 説明                                        
--------------------------------|---------------------------------------------
| `public uint16_t `[`sysex_encoded_length`](#group__sysex__tools_1ga061e5607030412d6e62e2390d8013f0a)`(uint16_t decoded_length)` | エンコード後のメッセージの長さを計算します。
| `public uint16_t `[`sysex_decoded_length`](#group__sysex__tools_1ga121fc227d3acc1c0ea08c9a5c26fa3b0)`(uint16_t encoded_length)` | デコード後のメッセージの長さを計算します。
| `public uint16_t `[`sysex_encode`](#group__sysex__tools_1ga54d77f8d32f92a6f329daefa2b314742)`(uint8_t * encoded,const uint8_t * source,uint16_t length)` | sysex メッセージで安全に送信できるようにデータをエンコードします。
| `public uint16_t `[`sysex_decode`](#group__sysex__tools_1gaaad1d9ba2d5eca709a0ab4ba40662229)`(uint8_t * decoded,const uint8_t * source,uint16_t length)` | エンコードされたデータをデコードします。

## メンバー

#### `public uint16_t `[`sysex_encoded_length`](#group__sysex__tools_1ga061e5607030412d6e62e2390d8013f0a)`(uint16_t decoded_length)` {#group__sysex__tools_1ga061e5607030412d6e62e2390d8013f0a}

エンコード後のメッセージの長さを計算します。

#### パラメータ
* `decoded_length` エンコードするメッセージの長さのバイト数。

#### 返り値
エンコード後のメッセージの長さのバイト数。

#### `public uint16_t `[`sysex_decoded_length`](#group__sysex__tools_1ga121fc227d3acc1c0ea08c9a5c26fa3b0)`(uint16_t encoded_length)` {#group__sysex__tools_1ga121fc227d3acc1c0ea08c9a5c26fa3b0}

デコード後のメッセージの長さを計算します。

#### パラメータ
* `encoded_length` エンコードされたメッセージの長さのバイト数。

#### 返り値
デコードされた後のメッセージの長さのバイト数。

#### `public uint16_t `[`sysex_encode`](#group__sysex__tools_1ga54d77f8d32f92a6f329daefa2b314742)`(uint8_t * encoded,const uint8_t * source,uint16_t length)` {#group__sysex__tools_1ga54d77f8d32f92a6f329daefa2b314742}

sysex メッセージで安全に送信できるようにデータをエンコードします。

#### パラメータ
* `encoded` 出力データバッファは、少なくとも sysex_encoded_length(length) バイトの長さが必要です。

* `source` エンコードされるデータの入力バッファ。

* `length` 入力バッファからエンコードするバイト数。

#### 返り値
エンコードされたバイト数。

#### `public uint16_t `[`sysex_decode`](#group__sysex__tools_1gaaad1d9ba2d5eca709a0ab4ba40662229)`(uint8_t * decoded,const uint8_t * source,uint16_t length)` {#group__sysex__tools_1gaaad1d9ba2d5eca709a0ab4ba40662229}

エンコードされたデータをデコードします。

#### パラメータ
* `decoded` 出力データバッファは、少なくとも sysex_decoded_length(length) バイトの長さが必要です。

* `source` デコードされるデータの入力バッファ。

* `length` 入力バッファからデコードするバイト数。

#### 返り値
デコードされたバイト数。

