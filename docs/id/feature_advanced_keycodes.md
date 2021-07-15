# Tombol *Modifier* :id=modifier-keys

Tombol berikut memperkenankan anda mengombinasikan sebuah *modifier* dengan sebuah kode tombol. Saat ditekan, *event* tombol turun akan dikirimkan lalu dilanjutkan dengan `kc`. Pada pelepasan tombol, *event* tombol naik untuk `kc` akan dikirim lalu diikuti *modifier*.

|Tombol    |Alias                          |Deskripsi                                             |
|----------|-------------------------------|------------------------------------------------------|
|`LCTL(kc)`|`C(kc)`                        |Tahan *Control* Kiri dan tekan `kc`                      |
|`LSFT(kc)`|`S(kc)`                        |Tahan *Shift* Kiri dan tekan `kc`                        |
|`LALT(kc)`|`A(kc)`, `LOPT(kc)`            |Tahan *Alt* Kiri dan tekan `kc`                          |
|`LGUI(kc)`|`G(kc)`, `LCMD(kc)`, `LWIN(kc)`|Tahan *GUI* Kiri dan tekan `kc`                          |
|`RCTL(kc)`|                               |Tahan *Control* Kanan dan tekan `kc`                     |
|`RSFT(kc)`|                               |Tahan *Shift* Kanan dan tekan `kc`                       |
|`RALT(kc)`|`ROPT(kc)`, `ALGR(kc)`         |Tahan *Alt* Kanan dan tekan `kc`                         |
|`RGUI(kc)`|`RCMD(kc)`, `LWIN(kc)`         |Tahan *GUI* Kanan dan tekan `kc`                         |
|`SGUI(kc)`|`SCMD(kc)`, `SWIN(kc)`         |Tahan *Shift* Kiri and GUI dan tekan `kc`                |
|`LCA(kc)` |                               |Tahan *Control* Kiri and Alt dan tekan `kc`              |
|`LSA(kc)` |                               |Tahan *Shift* Kiri and *Alt* Kiri dan tekan `kc`           |
|`RSA(kc)` |`SAGR(kc)`                     |Tahan *Shift* Kanan and *Alt* Kanan (AltGr) dan tekan `kc` |
|`RCS(kc)` |                               |Tahan *Control* Kanan and *Shift* Kanan dan tekan `kc`     |
|`LCAG(kc)`|                               |Tahan *Control* Kiri, *Alt* and *GUI* dan tekan `kc`         |
|`MEH(kc)` |                               |Tahan *Control* Kiri, *Shift* and *Alt* dan tekan `kc`       |
|`HYPR(kc)`|                               |Tahan *Control* Kiri, *Shift*, *Alt* and *GUI* dan tekan `kc`  |

Anda juga dapat merangkai tombol-tombol diatas, misalkan `LCTL(LALT(KC_DEL))` atau `C(A(KC_DEL))` untuk membuat tombol yang mengirim *Control+Alt+Delete* dengan satu penekanan tombol.

# Konten Peninggalan :id=legacy-content

Laman ini digunakan untuk meliputi fitur-fitur. Kita sudah memindah banyak bagian yang dulu merupakan bagian dari laman ini ke laman fitur tersebut. Semua bagian di bawah hanya merupakan pengalihan sehingga orang-orang akan yang membuka pranala lama pada web akan menemukan apa yang mereka cari.

## *Layer* :id=switching-and-toggling-layers

* [*Layer*](id/feature_layers.md)

## *Mod* Ketuk :id=mod-tap

* [*Mod* Ketuk](id/mod_tap.md)

## One Shot Keys :id=one-shot-keys

* [*One Shot Keys*](id/one_shot_keys.md)

## Pilihan Konfigurasi Ketuk-Tahan :id=tap-hold-configuration-options

* [Pilihan Konfigurasi Ketuk-Tahan](id/tap_hold.md)
