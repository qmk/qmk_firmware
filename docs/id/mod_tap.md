# Mod-Tap

Tombol *Mod*-Ketuk `MT(mod, kc)` berperilaku sebagai sebuah *modifier* saat ditahan dan berperilaku sebagai kode tombol biasa saat diketuk. Dengan kata lain, anda dapat memiliki sebuah tombol yang mengirim `Escape` saat anda mengetuknya dan mengirim tombol *Control*  atau *Shift* bila anda menahannya.

*Modifier* yang diterima kode tombol ini dan `OSM()` diawali dengan `MOD_`, bukan `KC_`:

|*Modifier*|Deskripsi                                       |
|----------|------------------------------------------------|
|`MOD_LCTL`|*Control* Kiri                                  |
|`MOD_LSFT`|*Shift* Kiri                                    |
|`MOD_LALT`|*Alt* Kiri                                      |
|`MOD_LGUI`|*GUI* Kiri (Windows/Command/Meta key)           |
|`MOD_RCTL`|*Control* Kanan                                 |
|`MOD_RSFT`|*Shift* Kanan                                   |
|`MOD_RALT`|*Alt* Kanan (AltGr)                             |
|`MOD_RGUI`|*GUI* Kanan (Windows/Command/Meta key)          |
|`MOD_HYPR`|Hyper (*Control* Kiri, *Shift*, *Alt* dan *GUI*)|
|`MOD_MEH` |Meh (*Control* Kiri, *Shift*, dan *Alt*)        |

Anda dapat menggabung tombol ini dengan ORing seperti berikut:

```c
MT(MOD_LCTL | MOD_LSFT, KC_ESC)
```

Tombol ini akan mengaktivasi *Control* Kiri dan Left *Shift* saat ditahan, dan mengirim `Escape` saat diketuk.

Demi kenyamanan anda, QMK mengikutsertakan beberapa pintasan *Mod*-Ketuk untuk membuat beberapa kombinasi umum lebih ringkas pada tata letak anda:

|Tombol      |Alias                                                            |Deskripsi                                                     |
|------------|-----------------------------------------------------------------|--------------------------------------------------------------|
|`LCTL_T(kc)`|`CTL_T(kc)`                                                      |*Control* Kiri saat ditahan, `kc` saat diketuk                      |
|`LSFT_T(kc)`|`SFT_T(kc)`                                                      |*Shift* Kiri saat ditahan, `kc` saat diketuk                        |
|`LALT_T(kc)`|`LOPT_T(kc)`, `ALT_T(kc)`, `OPT_T(kc)`                           |*Alt* Kiri saat ditahan, `kc` saat diketuk                          |
|`LGUI_T(kc)`|`LCMD_T(kc)`, `LWIN_T(kc)`, `GUI_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)`|*GUI* Kiri saat ditahan, `kc` saat diketuk                          |
|`RCTL_T(kc)`|                                                                 |*Control* Kanan saat ditahan, `kc` saat diketuk                     |
|`RSFT_T(kc)`|                                                                 |*Shift* Kanan saat ditahan, `kc` saat diketuk                       |
|`RALT_T(kc)`|`ROPT_T(kc)`, `ALGR_T(kc)`                                       |*Alt* Kanan saat ditahan, `kc` saat diketuk                         |
|`RGUI_T(kc)`|`RCMD_T(kc)`, `RWIN_T(kc)`                                       |*GUI* Kanan saat ditahan, `kc` saat diketuk                         |
|`SGUI_T(kc)`|`SCMD_T(kc)`, `SWIN_T(kc)`                                       |Left *Shift* dan *GUI* saat ditahan, `kc` saat diketuk                |
|`LCA_T(kc)` |                                                                 |*Control* Kiri dan *Alt* saat ditahan, `kc` saat diketuk              |
|`LSA_T(kc)` |                                                                 |*Shift* Kiri dan *Alt* saat ditahan, `kc` saat diketuk                |
|`RSA_T(kc)` |`SAGR_T(kc)`                                                     |*Shift* Kanan dan *Alt* Kanan (AltGr) saat ditahan, `kc` saat diketuk |
|`RCS_T(kc)` |                                                                 |*Control* Kanan dan *Shift* Kanan saat ditahan, `kc` saat diketuk     |
|`LCAG_T(kc)`|                                                                 |*Control* Kiri, *Alt* dan *GUI* saat ditahan, `kc` saat diketuk         |
|`RCAG_T(kc)`|                                                                 |*Control* Kanan, *Alt* dan *GUI* saat ditahan, `kc` saat diketuk        |
|`C_S_T(kc)` |                                                                 |*Control* Kiri dan *Shift* saat ditahan, `kc` saat diketuk            |
|`MEH_T(kc)` |                                                                 |*Control* Kiri, *Shift* dan *Alt* saat ditahan, `kc` saat diketuk       |
|`HYPR_T(kc)`|`ALL_T(kc)`                                                      |*Control* Kiri, *Shift*, *Alt* dan *GUI* saat ditahan, `kc` saat diketuk - more info [here](https://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)|

## Caveats

Sayangnya, beberapa kode tombol ini tidak dapat digunakan pada *Mod*-Ketuk atau *Layer*-Ketuk karena *modifier* yang ditentukan pada kode tombol diabaikan.

Sebagai tambahan, anda mungkin akan menemukan masalah bila menggunakan Remote Desktop Connection pada Windows karena kode kode tersebut mengirimkan *Shift* terlalu cepat dan mengakibatkan RDC melewatkan kode tersebut.

Untuk menyelesaikan masalah ini, buka Remote Desktop Connection, klik *Show Options*, buka tab *Local Resources*. Pada bagian *keyboard*, ubah drop-down ke *On this Computer*. Pengubahan ini akan memperkenankan karakter bekerja sebagaimana mestinya.

## Sumber Daya Lai

Lihat [Opsi Konfigurasi Ketuk-Tahan](tap_hold.md) untuk panji tambahan yang mengubah perilaku *mod*-ketuk.
