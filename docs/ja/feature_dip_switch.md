# DIP スイッチ

<!---
  original document: 0.8.94:docs/feature_dip_switch.md
  git diff 0.8.94 HEAD -- docs/feature_dip_switch.md | cat
-->

DIP スイッチは、以下を `rules.mk` に追加することでサポートされます:

    DIP_SWITCH_ENABLE = yes

以下を `config.h` に追加します:

```c
#define DIP_SWITCH_PINS { B14, A15, A10, B9 }
```

## コールバック

コールバック関数を `<keyboard>.c` に記述することができます:

```c
void dip_switch_update_kb(uint8_t index, bool active) { 
    dip_switch_update_user(index, active); 
}
```


あるいは `keymap.c`:

```c
void dip_switch_update_user(uint8_t index, bool active) { 
    switch (index) {
        case 0:
            if(active) { audio_on(); } else { audio_off(); }
            break;
        case 1:
            if(active) { clicky_on(); } else { clicky_off(); }
            break;
        case 2:
            if(active) { music_on(); } else { music_off(); }
            break;
        case 3:
            if (active) {
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(plover_song);
                #endif
                layer_on(_PLOVER);
            } else {
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(plover_gb_song);
                #endif
                layer_off(_PLOVER);
            }
            break;
    }
}
```

更に、より複雑な処理ができるビットマスク関数をサポートします。


```c
void dip_switch_update_mask_kb(uint32_t state) { 
    dip_switch_update_mask_user(state); 
}
```


あるいは `keymap.c`:

```c
void dip_switch_update_mask_user(uint32_t state) { 
    if (state & (1UL<<0) && state & (1UL<<1)) {
        layer_on(_ADJUST); // C on esc
    } else {
        layer_off(_ADJUST);
    }
    if (state & (1UL<<0)) {
        layer_on(_TEST_A); // A on ESC
    } else {
        layer_off(_TEST_A);
    }
    if (state & (1UL<<1)) {
        layer_on(_TEST_B); // B on esc
    } else {
        layer_off(_TEST_B);
    }
}
```


## ハードウェア

DIP スイッチの片側は MCU のピンへ直接配線し、もう一方の側はグラウンドに配線する必要があります。機能的に同じであるため、どちら側が接続されているかは問題にはならないはずです。
