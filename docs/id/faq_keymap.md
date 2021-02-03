# Sering Ditanya Mengenai Tata Letak

Laman ini berisi pertanyaan-pertanyaan yang sering ditanyakan mengenai tata letak. Bila anda belum membaca [Ikhtisar Tata Letak](id/keymap.md), silakan baca dokumen tersebut dahulu.

## Kode Tombol Apa Saja Yang Bisa Saya Gunakan?

See [Keycodes](keycodes.md) for an index of keycodes available to you. These link to more extensive documentation when available.
Lihat [Kode Tombol](id/keycodes.md) untuk indexs kode tombol yang tersedia untuk anda. Tautan tadi berisi dokumentasi yang lebih lengkap.

Kode tombol sebenarnya didefinisikan pada [common/keycode.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/keycode.h).

## Apa Saja Yang Menjadi Kode Tombol Bawaan?

Ada 3 standar peletakan papan ketik yang digunakan di seluruh dunia, ANSI, ISO, dan JIS. Amerika Utara secara umum menggunakan ANSI, Eropa dan Afrika menggunakan ISO, dan Jepang menggunakan JIS. Daerah-daerah yang tidak disebutkan biasanya menggunakan ANSI maupun ISO. Kode tombol yang berkorespondensi pada peletakan tombol papan ketik diperlihatkan pada gambar berikut:

<!-- Source for this image: https://www.keyboard-layout-editor.com/#/gists/bf431647d1001cff5eff20ae55621e9a -->
![Keyboard Layout Image](https://i.imgur.com/5wsh5wM.png)

## Bagaimana Saya Membuat Nama Buatan untuk Kode Tombol Kompleks?

Kadang kala, demi mudahnya terbaca, pendefinisian nama buatan untuk kode tombol sangat berguna. Orang-orang sering mendefinisikan nama buatan menggunakan `#define`. Sebagai contoh:

```c
#define FN_CAPS LT(_FL, KC_CAPSLOCK)
#define ALT_TAB LALT(KC_TAB)
```

Pendefinisian diatas memperkenankan anda menggunakan `FN_CAPS` dan `ALT_TAB` pada berkas tata letak anda dan membuatnya lebih mudah dibaca.

## Beberapa Tombol Saya Tertukar Atau Tidak Berfungsi

QMK mempunyai dua fitur, *Bootmagic* dan *Command* yang memperkenankan anda untuk mengubah perilaku papan ketik anda saat sedang digunakan. Hal ini juga termasuk, namun tidak terbatas, penukaran letak *Control* dan *Capslock*, mematikan *Gui*, menukar *Alt* dan *Gui*, menukar *backspace* dan *backslash*, mematikan semua tombol, dan modifikasi perilaku lainnya.

Salah satu usaha pembenahan adalah silakan tahan `Space` dan `Backspace` saat anda menyambungkan papan ketik anda ke komputer. Hal ini akan mereset pengaturan-pengaturan pada papan ketika anda sehingga mengembalikan tombol-tombol tadi kepada operasi normal. Bila masih tidak dapat dibenahi, silakan buka laman-laman berikut:

* [*Bootmagic*](id/feature_bootmagic.md)
* [*Command*](id/feature_command.md) 

## Tombol Menu Tidak Berfungsi

Tombol yang biasanya ditemukan pada papan ketik modern pada lokasi diantara `KC_RGUI` dan `KC_RCTL` sebenarnya disebut `KC_APP`. Hal ini dikarenakan saat tombol tersebut dibuat, sudah ada tombol dengan nama `MENU` pada standar-standar relevan. Sehingga, MicroSoft memilih untuk menamai tombol tersebut sebagai tombol `APP`.

## `KC_SYSREQ` Tidak Bekerja

Gunakan kode tombol *Print Screen* (`KC_PSCREEN` atau `KC_SCR`), bukan `KC_SYSREQ`. Kombinasi tombol 'Alt + *Print Screen*' dikenal sebagai *System Request*.

Lihat [isue #168](https://github.com/tmk/tmk_keyboard/issues/168) dan
* https://en.wikipedia.org/wiki/Magic_SysRq_key
* https://en.wikipedia.org/wiki/System_request

## Tombol *Power* Tidak Bekerja

Memang agak mengherankan saat ada dua kode tombol *Power* pada QMK: `KC_POWER` pada laman penggunaan Papan Ketik / Bantal Ketik (lol) HID, dan `KC_SYSTEM_POWER` (atau `KC_PWR`) pada laman Konsumer.

Kode tombol yang awal hanya dikenal pada macOS, sedangkan kode tombol setelahnya, `KC_SLEP` dan `KC_WAKE` didukung oleh 3 sistem operasi utama. Jadi sangat disarankan untuk menggunakan `KC_SYSTEM_POWER`. Pada Windows, tombol ini akan dieksekusi secara langsung sedangkan pada macOS, tombol-tombol tersebut harus ditahan sampai sebuah dialog muncul.

## *One Shot Modifier*

Fitur ini menyelesaikan masalah '*the*' penulis. Penulis sering kali menulis '*the*' atau '*THe*, bukan 'The'. *One Shot Shift* menyelesaikan masalah ini.
https://github.com/tmk/tmk_keyboard/issues/67

## *Modifier/Layer* Tersangkut

Tombol *modifier* atau *layer* bisa saja tersangkut bila pemindahan *layer*  tidak dikonfigurasi dengan benar.
Untuk tombol *modifier* dan *layer*, anda harus meletakkan `KC_TRANS, pada posisi yang sama pada *layer* tujuan untuk melepaskan tombol modifier atau mengembalikan pada *layer* sebelumnya saat pelepasan tombol.

* https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching
* https://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
* https://github.com/tmk/tmk_keyboard/issues/248


## Dukungan Tombol Kunci Mekanis

Fitur ini ditujukan untuk *tombol kunci mekanis* seperti [tombol Alps ini](https://deskthority.net/wiki/Alps_SKCL_Lock). Anda dapat menambah support untuk tombol ini dengan menambahkan baris-baris berikut pada `config.h` anda:

```
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

Setelah menambahkan fitur ini, anda dapat menggunakan `KC_LCAP`, `KC_LNUM`, dan `KC_LSCR` pada tata letak anda.

Papan ketik mekanis lawas kadang memiliki tombol kuncian semacam ini. Namun, papan ketik mekanis modern biasanya tidak memilikinya. ***Anda pada umumnya tidak membutuhkan fitur ini dan cukup gunakan kode tombol `KC_CAPS`, `KC_LCK`, dan `KC_SLCK`.***

## Menginput Karakter Spesial Selain ASCII seperti Cédille 'Ç'

Lihat fitur [Unikode](id/feature_unicode.md).

## Tombol `Fn` pada macOS

Tidak seperti kebanyakan tombol Fn, tombol Fn pada papan ketik Apple memiliki kode tombol khusus. Kode tombol ini bertempat pada kode tombol ke-enam pada raport 6KRO HID dasar. Maka dari itu, sebenarnya Apple hanya mendukung 5KRO.

Even worse, it is not recognized unless the keyboard's VID and PID match that of a real Apple keyboard. The legal issues that official QMK support for this feature may create mean it is unlikely to happen.
Terlebih lagi, modifikasi ini tidak akan dikenali opel macOS bilamana VID dan PID dari papan ketik tidak sesuai dengan papan ketik Apple yang sebenarnya. Masalah ini juga berarti QMK tidak dapat menambah fitur ini dengan alasan legal.

Lihat [masalah ini](https://github.com/qmk/qmk_firmware/issues/2179) untuk keterangan lebih lanjut.

## Tombol Yang Didukung pada Mac OSX?
You can know which keycodes are supported in OSX from this source code.
Anda dapat mengetahui kode tombol mana saja yang didukung pada OSX dari kode sumber berkut:

senarai `usb_2_adb_keymap` memetakan Keyboard/Keypad Page penggunaan ke kode pemindai ADB (kode tombol internal OSX).

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/Cosmo_USB2ADB.c

dan `IOHIDConsumer::dispatchConsumerEvent` mengatur penggunaan laman kode Consumer.

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/IOHIDConsumer.cpp


## Tombol JIS pada Mac OSX

tombol khusus pada papan ketik JIS Jepang seperti `無変換(Muhenkan)`, `変換(Henkan)`, `ひらがな(hiragana)` tidak dikenali pada OSX. Anda dapat menggunakan **Seil** untuk memfungsikan tombol-tombol tersebut dengan mengikuti opsi berikut:

* Nyalakan tombol NFER pada papan ketik PC
* Nyalakan tombol XFER pada papan ketik PC
* Nyalakan tombol KATAKANA pada papan ketik PC

https://pqrs.org/osx/karabiner/seil.html


## RN-42 Bluetooth Doesn't Work with Karabiner
## RN-42 Bluetooth Tidak Dapat Bekerja Dengan Karabiner

Karabiner - program tata letak papan ketik pada Mac OSX - mengabaikan masukan dari modul RN-42 secara bawaan. Anda harus menyalakan opsi ini agar Karabiner dapat bekerjasama dengan papan ketik anda.
https://github.com/tekezo/Karabiner/issues/403#issuecomment-102559237

Lihat tautan-tautan berikut untuk detail dari permasalahan.
https://github.com/tmk/tmk_keyboard/issues/213
https://github.com/tekezo/Karabiner/issues/403


## Esc dan <code>&#96;</code> Pada 1 Tombol

Lihat fitur [*Grave Escape*](id/feature_grave_esc.md).

## Eject on Mac OSX
Kode tombol `KC_EJECT` berfungsi pada OSX. https://github.com/tmk/tmk_keyboard/issues/250
Sedangkan Windows 10 mengabaikan kode tersebut dan Linux/Xorg, walaupun mengenali, tidak memiliki korespondensi bawaan.

Kami tidak yakin kode tombol *Eject* pada papan ketik Apple asli. HHKB menggunakan `F20` untuk tombol Eject (`Fn+f`) pada mode Mac. Namun, kemungkinan besar hal ini tidak sama dengan kode tombol *Eject* milik Apple.

## Apa itu `weak_mods` dan `real_mods` pada `action_util.c`
___TOLONG DIBENAHI___

`real_mods` ditujukan untuk mencatat kondisi dari tombol *modifier* fisik sedangkan `weak_mods` menahan kondisi *modifier* virtual / temporer yang, seharusnya` tidak berpengaruh pada kondisi *modifier* fisik.

Misalkan, anda menahan tombol *shift* kiri dan mengetuk `ACTION_MODS_KEY(LSHIFT, KC_A)`,

dengan `weak_mods`,
* (1) menahan *shift* kiri: `read_mods |= MOD_BIT(LSHIFT)`
* (2) mengetuk `ACTION_MODS_KEY(LSHIFT, KC_A)`: `weak_mods &= ~MOD_BIT(LSHIFT)`
* (3) melepas `ACTION_MODS_KEY(LSHIFT, KC_A)`: `weak_mods &= ~MOD_BIT(LSHIFT)`
`read_mods` tetap mencatat kondisi modifier.

tanpa `weak_mods`,
* (1) menahan *shift* kiri: `real_mods |= MOD_BIT(LSHIFT)`
* (2) mengetuk `ACTION_MODS_KEY(LSHIFT, KC_A)`: `real_mods |= MOD_BIT(LSHIFT)`
* (3) melepas `ACTION_MODS_KEY(LSHIFT, KC_A)`: `real_mods |= MOD_BIT(LSHIFT)`
`real_mods` disini kehilangan catatan kondisi dari tombol fisik *shift* kiri.

weak_mods is ORed with real_mods when keyboard report is sent.
https://github.com/tmk/tmk_core/blob/master/common/action_util.c#L57
