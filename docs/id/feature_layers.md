# *Layer* :id=layers

Salah satu fitur yang paling manjur sering digunakan pada Perangkat Tegar QMK merupakan dapat digunakannya *layer*. Bagi kebanyakan orang, fitur ini mirip dengan tombol *function* yang memperkenankan beberapa jenis tombol pada satu tombol fisik, seperti yang anda sering jumpai pada laptop ataupun tablet.

Untuk penjelasan lebih detail bagaimana tumpukan *layer* bekerja, silakan lihat [ulasan tata letak](id/keymap.md#keymap-and-layers).

## Switching and Toggling Layers :id=switching-and-toggling-layers
## Berpindah dan Mengubah *Layer* :id=switching-and-toggling-layers

Fungsi berikut memperkenankan anda untuk mengaktifkan *layer* dengan cara yang beragam. Harap diperhatikan bahwa *layer* pada umumnya tidak berada pada ruang hampa - terlepas dari tata letak - banyak *layer* dapat diaktifkan secara bersama sama. Selain itu, hal yang sering digunakan untuk memperkenankan penekanan tombol tembus ke *layer* yang lebih rendah adalah dengan menggunakan `KC_TRNS`. Saat menggunakan perpindahan *layer* dengan `MO()`, `LM()`, `TT()`, atau `LT()`, pastikan untuk munggunakan `KC_TRNS` pada tombol yang tidak anda gunakan pada *layer* bagian atas agar berfungsi dengan normal.

* `DF(layer)` - mengubah *layer* bawaan. *Layer* bawaan merupakan *layer* yang selalu aktif dan ditumpuki oleh *layer* lain. Silakan lihat di bawah untuk keterangan lebih lanjut. Makro ini digunakan untuk berpindah dari tata letak QWERTY ke Dvorak. (Harap diperhatika bahwa perpindahan ini hanya sementara dan akan hilang bila papan ketik terlepas dari komputer inang. Untuk mengubah *layer* bawaan secara permanen, dibutuhkan kustomasi lebih mendalam seperti memanggil fungsi `set_single_persistent_default_layer` pada [`process_record_user](custom_quantum_functions.md#programming-the-behavior-of-any-keycode).)
* `MO(layer)` - mengaktifkan *layer* sementara. Pada saat anda melepas tombol tersebut, *layer* tidak lagi aktif.
* `LM(layer, mod)` - mengaktifkan *layer* sementara (seperti `MO`), namun *modifier* aktif. Hanya mendukung *layer* 0-15 dan *modifier* kiri: `MOD_LCTL`, `MOD_LSFT`, `MOD_LALT`, `MOD_LGUI` (perhatikan penggunaan `MOD_`, bukan `KC_`). *Modifier* ini dapat dikombinasi dengan menggunakan `bitwise OR` seperti `LM(_RAISE, MOD_LCTL | MOD_LALT)`.
* `LT(layer, kc)` - mengaktifkan *layer* saat ditahan, dan mengirim *kc* saat diketuk. Hanya mendukung *layer* 0-15.
* `OSL(layer)` - mengaktifkan *layer* sampai tombol berikutnya ditekan. Lihat [*One Shot Keys*](id/one_shot_keys.md) untuk detail dan fungsionalitas lebih lanjut.
* `TG(layer)` - memindah *layer*, mengaktifkannya bila tidak aktif dan sebaliknya.
* `TO(layer)` - mengaktifkan *layer* dan menon-aktifkan semua *layer* lainnya (selain *layer* bawaan). Fungsi ini sedikit spesial karena fungsi ini hanya menambah / mengurangi *layer* pada tumpukan *layer* aktif anda, tetapi fungsi ini mengganti *layer* aktif anda sepenuhnya sehingga memperkenankan anda untuk mengganti *layer* tinggi dengan yang lebih rendah. Fungsi ini diaktifkan pada saat tombol turun (sesegera mungkin setelah tombol ditekan).
* `TT(layer)` - *Layer Tap-Toggle*. Bila anda menahan tombol ini, *layer* akan diaktifkan, dan bila anda melepaskannya, *layer* akan dinon-aktifkan sebagaimana `MO`. Bila anda menekannya berulang kli, *layer* akan berpindah ke nyala maupun mati (seperti `TG()`). Tombol ini harus ditekan 5 kali, secara bawaan. Walaupun anda dapat menentukannya dengan `TAPPING_TOGGLE` seperti `#define TAPPING_TOGGLE 2`  untuk memindah layer hanya dengan dua kali ketuk.

### Peringatan :id=caveats

Saat ini, `LT()` dan `MT()` hanya bisa digunakan dengan [Kode Tombol Dasar](id/keycodes_basic.md), yang berarti anda tidak dapat menggunakan kode tombol seperti `LCTL()`, `KC_TILD`, atau apapun yang memiliki kode tombol lebih besar dari `0xFF`. Lebih khususnya, tombol dengan fungsi ganda seperti `LT` dan `MT` menggunakan kode tombol 16 bit. 4bit digunakan untuk identifikator fungsi, 12 bit selanjutnya dibagi ke parameter-parameter. *Layer* ketuk menggunakan 4 bit untuk *layer* (inilah alasan kenapa hanya terbatas pada *layer* 0-15). *mod*-tap menggunakan 4 bit untuk identifikator, 4 bit untuk *mod* mana yang digunakan, dan 8 bit untuk kode tombol. Karena ini, kode tombol yang digunakan terbatas sampai `0xFF` (0-255) yang berarti hanya kode tombol dasar saja.

Memperluas cakupan fitur ini, paling bagus, akan sangat rumit. Berpindah ke kode tombol 32 bit akan menyelesaikan banyak hal, namun akan membuat penggunaan ruang oleh matriks tata letak berlipat ganda. Terlebih lagi, perluasan ini dapat menyebabkan beberapa masalah. Bila anda ingin menerapkan *modifier* pada kode tombol yang and ketuk, [*Tap Dance*](feature_tap_dance.md#example-5-using-tap-dance-for-advanced-mod-tap-and-layer-tap-keys) dapat menjadi solusi.

Sebagi tambahan, bila setidaknya *modifier* bagian kanan ditentukan pada *mod* ketuk atau *layer* ketuk, *modifier* ini akan mengakibatkan semua menjadi *modifier* sebelah kanan. Sehingga, percampuran keduanya tidak mungkin dilakukan.

## Bekerja dengan Layer :id=working-with-layers

Perpindahan *layer* harus dilakukan secara hati hati. Terkuncinya pengguna pada sebuah *layer* tanpa ada cara untuk menon-aktifkan *layer* tersebut adalah tidak mungkin. Kami telah membuat beberapa panduan untuk membantu pengguna agar terhindar dari masalah-masalah yang jamak ditemui.

### Pemula :id=beginners

Bila anda baru saja memulai menggunakan QMK, sangat disarankan untuk tetap menggunakan konfigurasi sederhana. Ikuti panduan berikut saat mempersiapkan *layer* anda:

* Persiapkan *layer* 0 sebagai *layer* bawaan atau dasar anda. *Layer* ini merupakan *layer* yang anda gunakan untuk mengetik dan bisa dalam bentuk tata letak apapun (qwerty, dvorak, colemak, dkk). Harap mengatur *layer* ini sebagai *layer* paling rendah karena *layer* ini berisi hampir semua tombol-tombol yang anda gunakan. Sehingga, *layer* ini akan menghalangi *layer* lain yang berada di bawahnya.
* Atur *layer* anda dalam bentuh *tree*, dengan *layer* 0 sebagai akarnya. Sebisa mungkin untuk tidak berpindah ke satu *layer* dari banyak *layer*.
* Pada tata letak sebuah *layer*, selalu rujuk pada *layer* dengan nomor lebih tinggi. Karena *layer* diproses dari nomor tertinggi yang aktif lalu turun ke bawah, memodifikasi kondisi dari *layer* dengan nomor lebih rendah akan rumit dan mudah terjadi kesalahan.

### Pengguna Menengah :id=intermediate-users

Kadang kala, anda membutuhkan lebih dari 1 *layer* dasar. Misalkan, anda ingin berpindah antara QWERTY dan Dvorak, berpindah tata letak untuk tata letak negara yang berbeda, atau berpindah tata letak untuk gim yang berbeda. *Layer* dasar anda harus selalu dinomori dengan nomor serendah mungkin. Dan bila anda memilki beberapa *layer* dasar, anda harus memperlakukan *layer-layer* tersebut sebagai *layer-layer* yang benar benar terpisah satu sama lain dikarenakan bila satu *layer* dasar aktif, maka *layer* dasar lain akan dimatikan. 

### Pengguna Lanjutan :id=advanced-users

Bila anda sudah merasa cukup paham tentang cara kerja *layer* dan anda mengetahui apa yang dapat anda lakukan dengan *layer*, anda dapat berkreasi. Aturan-aturan pada bagian Pemula akan membantu anda dalam menghindari detail-detail yang agak rumit terutama untuk pengguna papan ketik yang sangat latam. Pemahaman mengenai bagaimana *layer* bekerja akan membantu anda dalam menggunakannya secara lebih canggih.

Secara konsep, *layer* disusun bertumpuk secara berurutan dan dinomori dengan nomor 0 sebagai *layer* paling bawah. Saat menentukan apa yang harus dilakukan saat terjadi sebuah penekanan tombol, QMK akan memindai *layer* dari atas ke bawah dan berhenti bila QMK mencapai *layer* pertama yang aktif dan tombol tersebut tidak diset sebagai `KC_TRNS`. Kode tombol tersebutlah yang akan dikirim , bukan tombol pada *layer* yang anda aktifkan. Hal inilah yang sering membuat orang bertanya-tanya, "kenapa layer saya tidak berpindah?".

Kadang kala, anda mungkin ingin berpindah antar *layer* pada sebuah makro atau sebagai bagiandari *tap-dance*. `layer_on` mengaktifkan sebuah *layer* dan `layer_off` mematikannya. Fungsi-fungsi yang berkaitan dengan *layer* dapat anda temukan pada [`action_layer.h`](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/action_layer.h).

## Fungsi :id=functions

Ada beberapa fungsi dan variabel yang berhubungan dengan bagaimana anda menggunakan ataupun memanipulasi *layer*.

|Fungsi                                        |Deskripsi                                                                                                |
|----------------------------------------------|---------------------------------------------------------------------------------------------------------|
| `layer_state_set(layer_mask)`                | Mengubah status *layer* secara langsung (direkomendasikan, jangan gunakan bila anda tidak tahu apa ini) |
| `layer_clear()`                              | Mematikan seluruh *layer*                                                                               |
| `layer_move(layer)`                          | Menyalakan *layer* yang dimaksud dan mematikan *layer* selainnya.                                       |
| `layer_on(layer)`                            | Menyalakan *layer*  yang dimaksud dan membiarkan *layer* lain pada status yang sudah ada.               |
| `layer_off(layer)`                           | Mematikan *layer* yang dimaksud dan membiarkan *layer* lain pada status yang sudah ada.                 |
| `layer_invert(layer)`                        | Mengubah status dari *layer* yang dimaksud.                                                             |
| `layer_or(layer_mask)`                       | Mengaktifkan *layer* berdasarkan pada bit yang sama antara *layer* yang dimaksud dengan *layer* yang sudah ada    |
| `layer_and(layer_mask)`                      | Mengaktifkan *layer* berdasarkan pada bit yang sama dan nyala antara *layer* yang dimaksud dengan *layer* yang sudah ada. |
| `layer_xor(layer_mask)`                      | Mengaktifkan *layer* berdasarkan pada bit yang berbeda antara *layer* yang dimaksud dengan *layer* yang sudah ada. |
| `layer_debug(layer_mask)`                    | Cetak bit *mask* dan *layer* aktif tertinggi pada konsol pengawakutuan.                                 |
| `default_layer_set(layer_mask)`              | Tentukan *layer* bawaan secara langsung (direkomendasikan namun jangan gunakan bila anda tidak tahu ini apa). |
| `default_layer_or(layer_mask)`               | Nyalakan *layer* berdasarkan pada bit yang sama antara *layer* yang dimaksud dengan *layer* bawaan yang sudah ada.     |
| `default_layer_and(layer_mask)`              | Nyalakan *layer* berdasarkan pada bit yang sama dan aktif antara *layer* yang dimaksud dengan *layer* bawaan yang sudah ada. |
| `default_layer_xor(layer_mask)`              | Nyalakan *layer* berdasarkan pada bit yang berbeda antara *layer* yang dimaksud dengan *layer* bawaan yang sudah ada. |
| `default_layer_debug(layer_mask)`            | Prints out the current bit mask and highest active default layer to debugger console.                   |
| [`set_single_persistent_default_layer(layer)`](ref_functions.md#setting-the-persistent-default-layer) | Atur *layer* bawaan dan tulis ke memori persisten (EEPROM).          |
| [`update_tri_layer(x, y, z)`](ref_functions.md#update_tri_layerx-y-z) | Periksa bila *layer* `x` dan `y` nyala dan nyalakan `z` berdasarkan keduanya (nyala bila keduanya nyala, selainnya mati). |
| [`update_tri_layer_state(state, x, y, z)`](ref_functions.md#update_tri_layer_statestate-x-y-z) | Sama seperti `update_tri_layer(x, y, z)`, namun dari fungsi `layer_state_set_*`. |

Sebagai tambahan dari fungsi-fungsi yang dapat anda panggil, ada beberapa fungsi panggilan-balik yang dipanggil tiap kali *layer* berubah. Fungsi-fungsi tersebut akan mengumpankan status *layer* ke fungsi dimana status tersebut akan dibaca dan/atau dimodifikasi.

|Callback                                             |Description                                                                             |
|-----------------------------------------------------|----------------------------------------------------------------------------------------|
| `layer_state_set_kb(layer_state_t state)`           | Panggilan balik untuk fungsi *layer*, pada tingkat papan ketik.                        |
| `layer_state_set_user(layer_state_t state)`         | Panggilan balik untuk fungsi *layer*, pada tingkat pengguna.                           |
| `default_layer_state_set_kb(layer_state_t state)`   | Panggilan balik untuk fungsi *layer* default, pada tingkat papan ketik. Dipanggil pada saat inisialisasi papan ketik. |
| `default_layer_state_set_user(layer_state_t state)` | Panggilan balik untuk fungsi *layer* default, pada tingkat pengguna. Dipanggil pada saat inisialisasi papan ketik. |

?> Untuk detail tambahan bagaimana anda dapat menggunakan panggilan-balik ini, silakan periksa dokumen  [Kode Penggantian *Layer*](id/custom_quantum_functions.md#layer-change-code)

Juga dimungkinkan untuk memeriksa status dari *layer* tertentu dengan menggunakan fungsi dan makro berikut:

|Function                         |Description                                                                                      |Aliases
|---------------------------------|-------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------|
| `layer_state_is(layer)`         | Memeriksa apakan `layer` dinyalakan secara global.                                            | `IS_LAYER_ON(layer)`, `IS_LAYER_OFF(layer)`                           |
| `layer_state_cmp(state, layer)` | Memeriksa `state` untuk mengetahui apakah `layer` dinyalakan. Dimaksudkan pada penggunaan saat pemanggilan balik *layer* | `IS_LAYER_ON_STATE(state, layer)`, `IS_LAYER_OFF_STATE(state, layer)` |
