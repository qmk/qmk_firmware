# group `input_callback_reg` {#group__input__callback__reg}

<!---
  original document: 0.9.34:docs/internals_input_callback_reg.md
  git diff 0.9.34 HEAD -- docs/internals_input_callback_reg.md | cat
-->

これらは入力コールバックを登録するために使用する関数です。

関数は関連するデバイスの入力と適切な midi メッセージが一致した場合に呼び出されます。

## 概要

| メンバー | 説明 |
--------------------------------|---------------------------------------------
| `public void `[`midi_register_cc_callback`](#group__input__callback__reg_1ga64ab672abbbe393c9c4a83110c8df718)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` | コントロールチェンジメッセージコールバックを登録する。 |
| `public void `[`midi_register_noteon_callback`](#group__input__callback__reg_1ga3962f276c17618923f1152779552103e)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` | ノートオンコールバックを登録する。 |
| `public void `[`midi_register_noteoff_callback`](#group__input__callback__reg_1gac847b66051bd6d53b762958be0ec4c6d)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` | ノートオフコールバックを登録する。 |
| `public void `[`midi_register_aftertouch_callback`](#group__input__callback__reg_1gaa95bc901bd9edff956a667c9a69dd01f)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` | アフタータッチコールバックを登録する。 |
| `public void `[`midi_register_pitchbend_callback`](#group__input__callback__reg_1ga071a28f02ba14f53de219be70ebd9a48)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` | ピッチベンドコールバックを登録する。 |
| `public void `[`midi_register_songposition_callback`](#group__input__callback__reg_1gaf2adfd79637f3553d8f26deb1ca22ed6)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` | ソングポジションコールバックを登録する。 |
| `public void `[`midi_register_progchange_callback`](#group__input__callback__reg_1gae6ba1a35a4cde9bd15dd42f87401d127)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` | プログラムチェンジコールバックを登録する。 |
| `public void `[`midi_register_chanpressure_callback`](#group__input__callback__reg_1ga39b31f1f4fb93917ce039b958f21b4f5)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` | チャンネルプレッシャーコールバックを登録する。 |
| `public void `[`midi_register_songselect_callback`](#group__input__callback__reg_1gaf9aafc76a2dc4b9fdbb4106cbda6ce72)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` | ソングセレクトコールバックを登録する。 |
| `public void `[`midi_register_tc_quarterframe_callback`](#group__input__callback__reg_1ga0a119fada2becc628cb15d753b257e6e)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` | タイムコードクォータフレームコールバックを登録する。 |
| `public void `[`midi_register_realtime_callback`](#group__input__callback__reg_1ga764f440e857b89084b1a07f9da2ff93a)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_one_byte_func_t func)` | リアルタイムコールバックを登録する。 |
| `public void `[`midi_register_tunerequest_callback`](#group__input__callback__reg_1gae40ff3ce20bda79fef87da24b8321cb1)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_one_byte_func_t func)` | チューンリクエストコールバックを登録する１ |
| `public void `[`midi_register_sysex_callback`](#group__input__callback__reg_1ga63ce9631b025785c1848d0122d4c4c48)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_sysex_func_t func)` | システムエクスクルーシブコールバックを登録する。 |
| `public void `[`midi_register_fallthrough_callback`](#group__input__callback__reg_1ga7ed189164aa9682862b3181153afbd94)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_var_byte_func_t func)` | フォールスルーコールバックを登録する。 |
| `public void `[`midi_register_catchall_callback`](#group__input__callback__reg_1ga9dbfed568d047a6cd05708f11fe39e99)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_var_byte_func_t func)` | キャッチオールコールバックを登録する。 |

## メンバー

#### `public void `[`midi_register_cc_callback`](#group__input__callback__reg_1ga64ab672abbbe393c9c4a83110c8df718)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1ga64ab672abbbe393c9c4a83110c8df718}

コントロールチェンジメッセージコールバックを登録します。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_noteon_callback`](#group__input__callback__reg_1ga3962f276c17618923f1152779552103e)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1ga3962f276c17618923f1152779552103e}

ノートオンコールバックを登録します。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_noteoff_callback`](#group__input__callback__reg_1gac847b66051bd6d53b762958be0ec4c6d)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1gac847b66051bd6d53b762958be0ec4c6d}

ノートオフコールバックを登録します。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_aftertouch_callback`](#group__input__callback__reg_1gaa95bc901bd9edff956a667c9a69dd01f)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1gaa95bc901bd9edff956a667c9a69dd01f}

アフタータッチコールバックを登録します。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_pitchbend_callback`](#group__input__callback__reg_1ga071a28f02ba14f53de219be70ebd9a48)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1ga071a28f02ba14f53de219be70ebd9a48}

ピッチベンドコールバックを登録します。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_songposition_callback`](#group__input__callback__reg_1gaf2adfd79637f3553d8f26deb1ca22ed6)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1gaf2adfd79637f3553d8f26deb1ca22ed6}

ソングポジションコールバックを登録します。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_progchange_callback`](#group__input__callback__reg_1gae6ba1a35a4cde9bd15dd42f87401d127)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` {#group__input__callback__reg_1gae6ba1a35a4cde9bd15dd42f87401d127}

プログラムチェンジコールバックを登録します。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_chanpressure_callback`](#group__input__callback__reg_1ga39b31f1f4fb93917ce039b958f21b4f5)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` {#group__input__callback__reg_1ga39b31f1f4fb93917ce039b958f21b4f5}

チャンネルプレッシャーコールバックを登録します。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_songselect_callback`](#group__input__callback__reg_1gaf9aafc76a2dc4b9fdbb4106cbda6ce72)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` {#group__input__callback__reg_1gaf9aafc76a2dc4b9fdbb4106cbda6ce72}

ソングセレクトコールバックを登録します。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_tc_quarterframe_callback`](#group__input__callback__reg_1ga0a119fada2becc628cb15d753b257e6e)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` {#group__input__callback__reg_1ga0a119fada2becc628cb15d753b257e6e}

タイムコードクォータフレームコールバックを登録します。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_realtime_callback`](#group__input__callback__reg_1ga764f440e857b89084b1a07f9da2ff93a)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_one_byte_func_t func)` {#group__input__callback__reg_1ga764f440e857b89084b1a07f9da2ff93a}

リアルタイムコールバックを登録します。

全てのリアルタイムメッセージ型に対してコールバックが呼ばれます。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_tunerequest_callback`](#group__input__callback__reg_1gae40ff3ce20bda79fef87da24b8321cb1)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_one_byte_func_t func)` {#group__input__callback__reg_1gae40ff3ce20bda79fef87da24b8321cb1}

チューンリクエストコールバックを登録します１

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_sysex_callback`](#group__input__callback__reg_1ga63ce9631b025785c1848d0122d4c4c48)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_sysex_func_t func)` {#group__input__callback__reg_1ga63ce9631b025785c1848d0122d4c4c48}

システムエクスクルーシブコールバックを登録します。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_fallthrough_callback`](#group__input__callback__reg_1ga7ed189164aa9682862b3181153afbd94)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_var_byte_func_t func)` {#group__input__callback__reg_1ga7ed189164aa9682862b3181153afbd94}

フォールスルーコールバックを登録します。

より具体的なコールバックが見つからない場合にのみ呼ばれます。例えば、ノートオンコールバックを登録していないがノートオンメッセージを受け取った場合、フォールスルーコールバックが登録されている場合はそれが呼ばれます。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

#### `public void `[`midi_register_catchall_callback`](#group__input__callback__reg_1ga9dbfed568d047a6cd05708f11fe39e99)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_var_byte_func_t func)` {#group__input__callback__reg_1ga9dbfed568d047a6cd05708f11fe39e99}

キャッチオールコールバックを登録します。

登録されている場合は、より具体的なコールバックあるいはフォールスルーコールバックが登録されている場合でも、一致する全てのメッセージに対してキャッチオールコールバックが呼ばれます。

#### パラメータ
* `device` 関連するデバイス

* `func` 登録するコールバック関数

