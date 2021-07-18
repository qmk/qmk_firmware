# ワンショットキー

<!---
  original document: 0.9.34:docs/one_shot_keys.md
  git diff 0.9.34 HEAD -- docs/one_shot_keys.md | cat
-->

ワンショットキーは次のキーが押されるまでアクティブのままになり、そのあと放されるキーです。これにより一度に1つ以上のキーを押すことなく、キーボードの組み合わせを入力することができます。これらのキーは通常「スティッキーキー」あるいは「デッドキー」と呼ばれます。

例えば、キーを `OSM(MOD_LSFT)` と定義する場合、最初にシフトを押して放し、続いて A を押して放すことで、大文字の A キャラクタを入力することができます。コンピュータには、シフトが押された瞬間にシフトが押し続けられ、A が放された後ですぐにシフトキーが放されるように見えます。

ワンショットキーは通常のモディファイアのようにも動作します。ワンショットキーを押しながら他のキーを入力すると、キーを放した直後にワンショットキーが解除されます。

さらに、短時間でキーを5回押すと、そのキーをロックします。これはワンショットモディファイアとワンショットレイヤーに適用され、`ONESHOT_TAP_TOGGLE` 定義によって制御されます。

`config.h` でこれらを定義することでワンショットキーの挙動を制御することができます:

```c
#define ONESHOT_TAP_TOGGLE 5  /* この回数をタップすると、もう一度タップするまでキーが押されたままになります。*/
#define ONESHOT_TIMEOUT 5000  /* ワンショットキーが解除されるまでの時間 (ms) */
```

* `OSM(mod)` - *mod*を一時的に押し続けます。[モッドタップ](ja/mod_tap.md)で示したように、`KC_*` コードでは無く、`MOD_*` キーコードを使わなければなりません。
* `OSL(layer)` - 一時的に*レイヤー*に切り替えます。

ワンショットキーをマクロあるいはタップダンスルーチンの一部として有効にしたい場合があります。

ワンショットレイヤーについては、キーを押した時に `set_oneshot_layer(LAYER, ONESHOT_START)` を呼び出し、キーを放した時に `clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED)` を呼び出す必要があります。ワンショットをキャンセルする場合は、`reset_oneshot_layer()` を呼び出してください。

ワンショットモッドについては、設定するためには `set_oneshot_mods(MOD)` を呼び出し、キャンセルするためには `clear_oneshot_mods()` を呼び出す必要があります。

!> リモートデスクトップ接続で OSM 変換に問題がある場合は、設定を開いて「ローカル リソース」タブに移動し、キーボードセクションでドロップダウンを「このコンピューター」に変更することで修正することができます。これにより問題が修正され、OSM がリモートデスクトップ上で適切に動作するようになります。

## コールバック

ワンショットキーを押す時にカスタムロジックを実行したい場合、実装を選択できる幾つかのコールバックがあります。例えば、LED を点滅させたり、音を鳴らしたりして、ワンショットキーの変化を示すことができます。

`OSM(mod)` のためのコールバックがあります。ワンショット修飾キーの状態が変更されるたびに呼び出されます: オンに切り替わる時だけでなく、オフに切り替わる時にも呼び出されます。以下のように使うことができます:

```c
void oneshot_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    println("Oneshot mods SHIFT");
  }
  if (mods & MOD_MASK_CTRL) {
    println("Oneshot mods CTRL");
  }
  if (mods & MOD_MASK_ALT) {
    println("Oneshot mods ALT");
  }
  if (mods & MOD_MASK_GUI) {
    println("Oneshot mods GUI");
  }
  if (!mods) {
    println("Oneshot mods off");
  }
}
```

`mods` 引数は変更後のアクティブな mod が含まれるため、現在の状態が反映されます。

(`config.h` に `#define ONESHOT_TAP_TOGGLE 2` を追加して) ワンショットタップトグルを使う場合、指定された回数だけ修飾キーを押してロックすることができます。そのためのコールバックもあります:

```c
void oneshot_locked_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    println("Oneshot locked mods SHIFT");
  }
  if (mods & MOD_MASK_CTRL) {
    println("Oneshot locked mods CTRL");
  }
  if (mods & MOD_MASK_ALT) {
    println("Oneshot locked mods ALT");
  }
  if (mods & MOD_MASK_GUI) {
    println("Oneshot locked mods GUI");
  }
  if (!mods) {
    println("Oneshot locked mods off");
  }
}
```

最後に、`OSL(layer)` ワンショットキーのためのコールバックもあります:

```c
void oneshot_layer_changed_user(uint8_t layer) {
  if (layer == 1) {
    println("Oneshot layer 1 on");
  }
  if (!layer) {
    println("Oneshot layer off");
  }
}
```

いずれかのワンショットレイヤーがオフの場合、`layer` は 0 になります。ワンショットレイヤーの変更では無く、レイヤーの変更で何かを実行したい場合は、`layer_state_set_user` は使用するのに良いコールバックです。

独自のキーボードを作成している場合、`_kb` と同等の機能もあります:

```c
void oneshot_locked_mods_changed_kb(uint8_t mods);
void oneshot_mods_changed_kb(uint8_t mods);
void oneshot_layer_changed_kb(uint8_t layer);
```

他のコールバックと同様に、更にカスタマイズを可能にするために `_user` バージョンを呼ぶようにしてください。
