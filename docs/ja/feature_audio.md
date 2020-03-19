# オーディオ

<!---
  original document: 0d3f0889c:docs/feature_audio.md
  git diff 0d3f0889c HEAD -- docs/feature_audio.md | cat
-->

キーボードは音を出すことができます！Planck、Preonic あるいは特定の PWM 対応ピンにアクセスできる AVR キーボードがある場合は、シンプルなスピーカーを接続してビープ音を鳴らすことができます。これらのビープ音を使ってレイヤーの変化、モディファイア、特殊キーを示したり、あるいは単にファンキーな8ビットの曲を鳴らすことができます。

最大2つの同時オーディオ音声がサポートされ、1つはタイマー1によってもう一つはタイマー3によって駆動されます。以下のピンは config.h の中でオーディオ出力として定義することができます:

Timer 1:
`#define B5_AUDIO`
`#define B6_AUDIO`
`#define B7_AUDIO`

Timer 3:
`#define C4_AUDIO`
`#define C5_AUDIO`
`#define C6_AUDIO`

`rules.mk` に `AUDIO_ENABLE = yes` を追加すると、他の設定無しで自動的に有効になる幾つかの異なるサウンドがあります:

```
STARTUP_SONG // キーボードの起動時に再生 (audio.c)
GOODBYE_SONG // RESET キーを押すと再生 (quantum.c)
AG_NORM_SONG // AG_NORM キーを押すと再生 (quantum.c)
AG_SWAP_SONG // AG_SWAP キーを押すと再生 (quantum.c)
CG_NORM_SONG // CG_NORM キーを押すと再生 (quantum.c)
CG_SWAP_SONG // CG_SWAP キーを押すと再生 (quantum.c)
MUSIC_ON_SONG // 音楽モードがアクティブになると再生 (process_music.c)
MUSIC_OFF_SONG // 音楽モードが非アクティブになると再生 (process_music.c)
CHROMATIC_SONG // 半音階音楽モードが選択された時に再生 (process_music.c)
GUITAR_SONG // ギター音楽モードが選択された時に再生 (process_music.c)
VIOLIN_SONG // バイオリン音楽モードが選択された時に再生 (process_music.c)
MAJOR_SONG // メジャー音楽モードが選択された時に再生 (process_music.c)
```

`config.h` の中で以下のような操作を行うことで、デフォルトの曲を上書きすることができます:

```c
#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(STARTUP_SOUND)
#endif
```

サウンドの完全なリストは、[quantum/audio/song_list.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/audio/song_list.h) で見つかります - このリストに自由に追加してください！利用可能な音は [quantum/audio/musical_notes.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/audio/musical_notes.h) で見つかります。

特定の時にカスタムサウンドを再生するために、以下のように曲を定義することができます(ファイルの上部付近に):

```c
float my_song[][2] = SONG(QWERTY_SOUND);
```

以下のように曲を再生します:

```c
PLAY_SONG(my_song);
```

または、以下のようにループで再生することができます:

```c
PLAY_LOOP(my_song);
```

オーディオがキーボードに組み込まれていない時に問題が起きる事を避けるために、`#ifdef AUDIO_ENABLE` / `#endif` で全てのオーディオ機能をくるむことをお勧めします。

オーディオで利用可能なキーコードは以下の通りです:

* `AU_ON` - オーディオ機能をオン
* `AU_OFF` - オーディオ機能をオフ
* `AU_TOG` - オーディオ機能を切り替え

!> これらのキーコードは全てのオーディオ機能をオンおよびオフにします。オフにするとオーディオフィードバック、オーディオクリック、音楽モードなどが完全に無効になります。

## ARM オーディオボリューム

ARM デバイスの場合、DAC サンプル値を調整できます。キーボードがあなたやあなたの同僚にとって騒々しい場合、`config.h` 内の `DAC_SAMPLE_MAX` を使って最大量を設定することができます:

```c
#define DAC_SAMPLE_MAX 65535U
```

## 音楽モード

音楽モードは列を半音階に、行をオクターブにマップします。これは格子配列キーボードで最適に動作しますが、他のものでも動作させることができます。`0xFF` 未満の全てのキーコードはブロックされるため、音の演奏中は入力できません - 特別なキー/mod があればそれらは引き続き動作します。これを回避するには、音楽モードを有効にする前(あるいは後)で、KC_NO を使って別のレイヤーにジャンプします。

メモリの問題により、録音は実験的です - 奇妙な動作が発生した場合は、キーボードの取り外しと再接続で問題が解決するでしょう。

利用可能なキーコード:

* `MU_ON` - 音楽モードをオン
* `MU_OFF` - 音楽モードをオフ
* `MU_TOG` - 音楽モードの切り替え
* `MU_MOD` - 音楽モードの循環
   * `CHROMATIC_MODE` - 半音階。行はオクターブを変更します
   * `GUITAR_MODE` - 半音階、ただし行は弦を変更します (+5 st)
   * `VIOLIN_MODE` - 半音階。ただし行は弦を変換します (+7 st)
   * `MAJOR_MODE` - メージャースケール

音楽モードでは、以下のキーコードは動作が異なり、通過しません:

* `LCTL` - 録音を開始
* `LALT` - 録音を停止/演奏を停止
* `LGUI` - 録音を再生
* `KC_UP` - 再生をスピードアップ
* `KC_DOWN` - 再生をスローダウン

ピッチ標準 (`PITCH_STANDARD_A`) はデフォルトで 440.0f です - これを変更するには、`config.h` に以下のようなものを追加します:

    #define PITCH_STANDARD_A 432.0f

音楽モードも完全に無効にすることができます。コントローラの容量が足りなくて困っている場合に役に立ちます。無効にするには、これを `config.h` に追加します:

    #define NO_MUSIC_MODE

### 音楽マスク

デフォルトで、`MUSIC_MASK` は `keycode < 0xFF` に設定されます。これは、`0xFF` 未満のキーコードが音に変換され、何も出力しないことを意味します。`config.h` の中で以下のものを定義することで、これを変更することができます:

    #define MUSIC_MASK keycode != KC_NO

これは全てのキーコードを捕捉します - これは、キーボードを再起動するまで、音楽モードで動けなくなることに注意してください！

どのキーコードを引き続き処理するかを制御する、より高度な方法については、`<keyboard>.c` の中の `music_mask_kb(keycode)` および `keymap.c` の中の `music_mask_user(keycode)` を使うことができます:

    bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
    return false;
    default:
    return true;
    }
    }

false を返すものはマスクの一部では無く、常に処理されます。

### 音楽マップ

デフォルトでは、音楽モードはキーのスケールを決定するために列と行を使います。キーボードレイアウトに一致する長方形のマトリックスを使うキーボードの場合、これで十分です。しかし、(Planck Rev6 あるいは多くの分割キーボードなどのように)より複雑なマトリックスを使うキーボードの場合、非常に歪んだ感じを受けることになります。

しかしながら、音楽マップオプションにより、音楽モードのためにスケーリングを再マップすることができるため、レイアウトに一致し、より自然になります。

この機能を使うには、`#define MUSIC_MAP` を `config.h` ファイルに追加します。そして、`キーボードの名前.c` または `keymap.c` に `uint8_t music_map` を追加します。

```c
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_ortho_4x12(
	36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
	24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
	12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11
);
```

キーボードが使用する `LAYOUT` マクロも使用したいでしょう。これは正しいキーの位置にマップします。キーボードレイアウトの左下から開始し、右に移動してさらに上に移動します。完全なマトリックスができるまで、全てのエントリを入力します。

これを実装する方法の例として、[Planck Keyboard](https://github.com/qmk/qmk_firmware/blob/e9ace1487887c1f8b4a7e8e6d87c322988bec9ce/keyboards/planck/planck.c#L24-L29) を見ることができます。

## オーディオクリック

これは、ボタンを押すたびにクリック音を追加し、キーボードからのクリック音をシミュレートします。キーを押すたびにわずかに音が異なるため、すばやく入力しても長い単一の音のようには聞こえません。

* `CK_TOGG` - ステータスを切り替えます (有効にされた場合、音を再生します)
* `CK_ON` - オーディオクリックをオンにします (音を再生します)
* `CK_OFF` - オーディオクリックをオフにします (音を再生しません）
* `CK_RST` - 周波数をデフォルトの状態に再設定します (デフォルトの周波数で音を再生します)
* `CK_UP` - クリックの周波数を増やします (新しい周波数で音を再生します)
* `CK_DOWN` - クリックの周波数を減らします (新しい周波数で音を再生します)


容量を節約するためにデフォルトではこの機能は無効です。有効にするには、`config.h` に以下を追加します:

    #define AUDIO_CLICKY


これらの値を定義することで、デフォルト、最小および最大周波数、ステッピングおよび組み込みのランダム性を設定することができます:

| オプション | デフォルト値 | 説明 |
|--------|---------------|-------------|
| `AUDIO_CLICKY_FREQ_DEFAULT` | 440.0f | クリック音のデフォルト/開始音の周波数を設定します。 |
| `AUDIO_CLICKY_FREQ_MIN` | 65.0f | 最小周波数を設定します (60f 未満は少しバグがあります)。 |
| `AUDIO_CLICKY_FREQ_MAX` | 1500.0f | 最大周波数を設定します。高すぎると同僚があなたを攻撃する可能性があります。 |
| `AUDIO_CLICKY_FREQ_FACTOR` | 1.18921f | UP/DOWN キーコードのステップを設定します。これは掛け算の係数です。デフォルトでは、音楽のマイナーの1/3ずつ、周波数を上げ/下げします。 |
| `AUDIO_CLICKY_FREQ_RANDOMNESS` | 0.05f | クリックのランダム性の係数を設定します。これを `0f` に設定すると各クリックが同一になり、`1.0f` に設定するとこの音は90年代のコンピュータ画面のスクロール/タイピングの効果があります。 |
| `AUDIO_CLICKY_DELAY_DURATION` | 1 | 1がテンポの 1/16、または64分音符である整数音符の長さ (実装の詳細については、`quantum/audio/musical_notes.h` を見てください)。メインのクリック効果は、この時間だけ遅れます。これらを6-12前後の値に調整すると、うるさいスイッチの補正に役立ちます。 |




## MIDI 機能

これはまだ WIP ですが、何が起きているかを見るために、`quantum/process_keycode/process_midi.c` を調べてください。Makefile から有効にします。


## オーディオキーコード

| キー | エイリアス | 説明 |
|----------------|---------|----------------------------------|
| `AU_ON` |  | オーディオモードオン |
| `AU_OFF` |  | オーディオモードオフ |
| `AU_TOG` |  | オーディオモードを切り替えます |
| `CLICKY_TOGGLE` | `CK_TOGG` | オーディオクリックモードを切り替えます |
| `CLICKY_UP` | `CK_UP` | クリック音の周波数を増やします |
| `CLICKY_DOWN` | `CK_DOWN` | クリック音の周波数を減らします |
| `CLICKY_RESET` | `CK_RST` | 周波数をデフォルトに再設定します |
| `MU_ON` |  | 音楽モードをオンにします |
| `MU_OFF` |  | 音楽モードをオフにします |
| `MU_TOG` |  | 音楽モードを切り替えます |
| `MU_MOD` |  | 音楽モードを循環します |

<!-- FIXME: this formatting needs work

## Audio

```c
#ifdef AUDIO_ENABLE
    AU_ON,
    AU_OFF,
    AU_TOG,

    #ifdef FAUXCLICKY_ENABLE
        FC_ON,
        FC_OFF,
        FC_TOG,
    #endif

    // Music mode on/off/toggle
    MU_ON,
    MU_OFF,
    MU_TOG,

    // Music voice iterate
    MUV_IN,
    MUV_DE,
#endif
```

### Midi

#if !MIDI_ENABLE_STRICT || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))
    MI_ON,  // send midi notes when music mode is enabled
    MI_OFF, // don't send midi notes when music mode is enabled
#endif

MIDI_TONE_MIN,
MIDI_TONE_MAX

MI_C = MIDI_TONE_MIN,
MI_Cs,
MI_Db = MI_Cs,
MI_D,
MI_Ds,
MI_Eb = MI_Ds,
MI_E,
MI_F,
MI_Fs,
MI_Gb = MI_Fs,
MI_G,
MI_Gs,
MI_Ab = MI_Gs,
MI_A,
MI_As,
MI_Bb = MI_As,
MI_B,

MIDI_TONE_KEYCODE_OCTAVES > 1

where x = 1-5:
MI_C_x,
MI_Cs_x,
MI_Db_x = MI_Cs_x,
MI_D_x,
MI_Ds_x,
MI_Eb_x = MI_Ds_x,
MI_E_x,
MI_F_x,
MI_Fs_x,
MI_Gb_x = MI_Fs_x,
MI_G_x,
MI_Gs_x,
MI_Ab_x = MI_Gs_x,
MI_A_x,
MI_As_x,
MI_Bb_x = MI_As_x,
MI_B_x,

MI_OCT_Nx 1-2
MI_OCT_x 0-7
MIDI_OCTAVE_MIN = MI_OCT_N2,
MIDI_OCTAVE_MAX = MI_OCT_7,
MI_OCTD, // octave down
MI_OCTU, // octave up

MI_TRNS_Nx 1-6
MI_TRNS_x 0-6
MIDI_TRANSPOSE_MIN = MI_TRNS_N6,
MIDI_TRANSPOSE_MAX = MI_TRNS_6,
MI_TRNSD, // transpose down
MI_TRNSU, // transpose up

MI_VEL_x 1-10
MIDI_VELOCITY_MIN = MI_VEL_1,
MIDI_VELOCITY_MAX = MI_VEL_9,
MI_VELD, // velocity down
MI_VELU, // velocity up

MI_CHx 1-16
MIDI_CHANNEL_MIN = MI_CH1
MIDI_CHANNEL_MAX = MI_CH16,
MI_CHD, // previous channel
MI_CHU, // next channel

MI_ALLOFF, // all notes off

MI_SUS, // sustain
MI_PORT, // portamento
MI_SOST, // sostenuto
MI_SOFT, // soft pedal
MI_LEG,  // legato

MI_MOD, // modulation
MI_MODSD, // decrease modulation speed
MI_MODSU, // increase modulation speed
#endif // MIDI_ADVANCED

-->
