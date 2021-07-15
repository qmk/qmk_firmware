# Ulasan Tata Letak

Tata letak QMK didefinisikan pada berkas sumber C. Struktur data yang digunakan merupakan larik dari larik. Larik terluar merupakan daftar dari larik *layer* sedangkan larik bagian dalam merupakan daftar dari tombol-tombol. Kebanyakan papan ketik mendefinisikan makro `LAYOUT()` untuk membantu anda membuat larik-larik ini.

## Tata Letak dan *Layer* :id=keymap-and-layers
Pada QMK, ** `const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS]` ** mengandung beberapa *layer* tata letak pada data 16 bit **kode tindakan**. Anda dapat mendefinisikan sebanyak, maksimal, **32 *layer* **

Untuk definisi tombol sederhana, 8bit data paling tinggi pada **kode tindakan** semuanya bernilai 0 dan 8bit yang rendah berisi kode penggunaan USB HID yang dibuat tombol sebagai **kode tombol**.

*Layer* dapat divalidasi secara bersamaan dan diindeks dengan 0 sampai 31. Layer dengan indeks lebih tinggi lebih diprioritaskan.

    Tata letak: 32 *Layer*              *Layer*: aksi kode matriks
    -----------------                   ---------------------
    tumpukan *layer*                    array_of_action_code[baris][kolom]
           ____________ preseden                 _______________________
          /           / | tinggi                / ESC / F1  / F2  / F3   ....
      31 /___________// |                      /-----/-----/-----/-----
      30 /___________// |                     / TAB /  Q  /  W  /  E   ....
      29 /___________/  |                    /-----/-----/-----/-----
       :   _:_:_:_:_:__ |               :   /LCtrl/  A  /  S  /  D   ....
       :  / : : : : : / |               :  /  :     :     :     :
       2 /___________// |               2 `--------------------------
       1 /___________// |               1 `--------------------------
       0 /___________/  V rendah        0 `--------------------------


Kadangkala, kode aksi yang tersimpan pada tata letak dirujuk sebagai ode tombol pada beberapa dokumen dikarenakan riwayat dari TMK.

### Status Layer Tata Letak :id=keymap-layer-status

Kondisi dari *layer* tata letak ditentukan oleh dua parameter 32bit:

* **`default_layer_state`** mengindikasikan *layer* tata letak dasar (0-31) yang selalu valid dan dapat dirujuk (*layer* bawaan).
* **`layer_state`** memiliki status aktif/tidak dari tiap layer pada bit-nya.

*Layer* tata letak '0' biasanya merupakan *layer* bawaan dimana semua *layer* lain tidak aktif setelah *boot up* perangkat tegar, walaupun pengaturan bawaan semacam ini dapat diatur pada `config.h`. Pengubahan *layer* bawaan juga berguna bila anda mengubah tata letak umum, misalkan saat anda ingin menggunakan Colemak dari Qwerty.

    Kondisi awal tata letak          Perubahan layout dasar
    -----------------------          ------------------

      31                               31
      30                               30
      29                               29
       :                                :
       :                                :   ____________
       2   ____________                 2  /           /
       1  /           /              ,->1 /___________/
    ,->0 /___________/               |  0
    |                                |
    `--- default_layer = 0           `--- default_layer = 1
         layer_state   = 0x00000001       layer_state   = 0x00000002

Pada sisi lain, ana dapat mengubah `layer_state` untuk menutupi *layer* dasar dengan *layer* lainnya untuk fitur seperti tombol navigasi, tombol fungsi (F1-F12), tombol media, dan/atau aksi khusus.

    Overlay feature layer
    ---------------------      bit|status
           ____________        ---+------
      31  /           /        31 |   0
      30 /___________// -----> 30 |   1
      29 /___________/  -----> 29 |   1
       :                        : |   :
       :   ____________         : |   :
       2  /           /         2 |   0
    ,->1 /___________/  ----->  1 |   1
    |  0                        0 |   0
    |                                 +
    `--- default_layer = 1            |
         layer_state   = 0x60000002 <-'



### Layer Precedence and Transparency

Harap perhatikan bahwa ***layer lebih tinggi memiliki prioritas lebih tinggi pada tumpukan layer***. Perangkat tegar memeriksa kode tombol satu-per-satu pada *layer* yang aktif dari *layer* paling tinggi yang aktif lalu turun ke bawah. Setelah perangkat tegar menemukan sebuah kode tombol selain `KC_TRNS` (transparan) pada *layer* aktif, perangkat tegar akan berhenti mencari dan *layer* yang lebih rendah tidak akan dirujuk.

           ____________
          /           /  <--- *Layer* lebih tinggi
         /  KC_TRNS  //
        /___________//   <--- *Layer* lebih rendah (KC_A)
        /___________/
    
    Pada skenario di atas, tombol non-transparan pada *layer* lebih tinggi akan dapat digunakan. namun, kapanpun `KC_TRNS` (atau setara) didefinisikan, kode tombol `KC_A` pada tingkat yang lebih rendah akan digunakan.

**Catatan:** Cara yang valid untuk menunjukkan transparansi pada layer tertentu adalah:
* `KC_TRANSPARENT`
* `KC_TRNS` (alias)
* `_______` (alias)

Kode tombol di atas memperkenankan pemrosesan untuk tembus ke *layer* bawah pada pencarian kode tombol non-transparan untuk diproses.

## Anatomi dari `keymap.c`

Untuk contoh ini, kita akan menelusuri [versi lama dari tata letak bawaan Clueboard 66%](https://github.com/qmk/qmk_firmware/blob/ca01d94005f67ec4fa9528353481faa622d949ae/keyboards/clueboard/keymaps/default/keymap.c). Akan sangat membantu bila anda membuka berkas tersebut pada jendela peramban lain sehingga anda dapat melihatnya pada konteks yang sesuai.

Ada 3 bagian utama dari sebuah berkas `keymap.c` yang harus anda perhatikan:

* [Definisi](#definitions)
* [Struktur Data *Layer*/Tata Letak](#layers-and-keymaps)
* [Fungsi *Custom*](#custom-functions), bila ada

### Definisi

Pada bagian atas dari berkas, anda akan menemukan hal semacam ini:

    #include QMK_KEYBOARD_H

    // Helpful defines
    #define GRAVE_MODS  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)|MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
     *  You can use _______ in place for KC_TRNS (transparent)   *
     *  Or you can use XXXXXXX for KC_NO (NOOP)                  *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    // Each layer gets a name for readability.
    // The underscores don't mean anything - you can
    // have a layer called STUFF or any other name.
    // Layer names don't all need to be of the same
    // length, and you can also skip them entirely
    // and just use numbers.
    #define _BL 0
    #define _FL 1
    #define _CL 2

Pada bagian diatas, ada beberapa pendefinisian yang berguna saat membangun tata letak dan fungsi *custom* anda. Definisi `GRAVE_MODS` akan digunakan nanti pada fungsi *custom* dan pendefinisian `_BL`, `_FL`, dan `_CL` akan mempermudah perujukan tiap *layer*.

Catatan: anda mungkin menemukan berkas tata letak yang lama yang munking memiliki definisi `_______` dan/atau `XXXXXXX`. Kedua definsi ini dapat digunakan sebagai pengganti `KC_TRNS` dan `KC_NO` untuk mempermudah melihat layer mana yang dikesampingkan. Kedua definisi tadi sekarang tidak diperlukan karena sudah dimasukkan secara bawaan.

### *Layer* dan Tata Letak

Bagian utama pada berkas ini merukapan definisi `keymaps[]`. Pada definisi ini anda mengurutkan semua *layer* anda beserta isinya. Bagian ini dimulai dengan definisi berikut:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

Setelah ini, anda akan menemukan senarai makro `LAYOUT()`. sebuah `LAYOUT()` hanya merupakan senarai tombol tombol untuk mendefinisikan sebuah *layer*. Umumnya, anda akan memiliki satu atau lebih "*layer* bawaan" seperti QWERTY, Dvorak, atau Colemak dan anda akan menempelkan satu atau *layer* "fungsi". Dikarenakan bagaimana *layer* diproses, anda tidak dapat melapisi *layer* yang lebih rendah di atas *layer* yang lebih tinggi.

`keymaps[][MATRIX_ROWS][MATRIX_COLS]` pada QMK mengandung 16 bit kode aksi (kadang dirujuk sebagai kode quantum). Dikarenakan kode tombol merepresentasikan tombol tombol pada umumnya, nilai byte tingginya 0 dan nilai byte rendahnya merupakan ID penggunaan USB HID untuk papan ketik.

> TMK yang merupakan asal dari QMK menggunakan `const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS]` sehingga mengandung kode tombol 8 bit. Beberapa nilai kode tombol ini dicadangkan untuk menginduksi beberapa kode aksi dengan menggunakan larik `fn_actions[]`.

#### *Layer* Dasar

Berikut merupakan contoh *layer* dasar dari Clueboard:

      /* Keymap _BL: Base Layer (Default Layer)
       */
    [_BL] = LAYOUT(
      F(0),    KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_GRV,  KC_BSPC,          KC_PGUP, \
      KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,                   KC_PGDN, \
      KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,                             \
      KC_LSFT, KC_NUBS, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH,  KC_RO,    KC_RSFT,          KC_UP,            \
      KC_LCTL, KC_LGUI, KC_LALT, KC_MHEN,          KC_SPC,KC_SPC,                        KC_HENK,  KC_RALT,  KC_RCTL,  MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT),

Beberapa hal yang patut dicatat mengenai hal ini adalah:

* Dari sudut pandang kode sumber C, definisi di atas hanya merupakan larik tunggal. Namun, spasi dan baris baru disisipkan agar visualisasi lebih mudah dilakukan dimana tiap tombol berada pada lokasi di piranti fisik.
* Kode pindai papan ketik polos diawali dengan KC, sedangkan tombol "khusus" tidak.
* Bagian kiri atas mengaktivasi fungsi *custom* 0 (`F(0)`)
* Tombol "Fn" didefinisikan dengan `MO(_FL)` yang memindah ke *layer* `_FL` saat tombol tersebut ditahan.

#### Lapisan Atas *Layer* Fungsi

*Layer* fungsi ini, bila dilihat dari sudut pandang kode, tidak berbeda dengan *layer* dasar. Walaupun secara konsep, anda menggunakan *layer* tersebut sebagai lapisan atas, bukan pengganti. Bagi banyak orang, perbedaan ini tidak begitu berarti. Namun, bila anda menggunakan banyak *layer* yang rumit, hal ini menjadi semakin penting.

    [_FL] = LAYOUT(
      KC_GRV,  KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______, KC_DEL,           BL_STEP, \
      _______, _______, _______,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK, KC_PAUS,  _______,  _______,  _______,                   _______, \
      _______, _______, MO(_CL),_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,                           \
      _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,          KC_PGUP,         \
      _______, _______, _______, _______,        _______,_______,                        _______,  _______,  _______,  MO(_FL), KC_HOME, KC_PGDN, KC_END),

Some interesting things to note:
Beberapa hal yang patut dicatat:

* Penggunaan `_______` membuat perubahan yang sudah dibuat terlihat lebih jelas.
* Bila anda sedang berada pada *layer* ini dan menekan salah satu `_______`, anda akan mengaktifkan tombol pada *layer* yang lebih rendah.

# Detail Lebih Lanjut

Laman ini seharusgia sudah memberikan anda ulasan umum untuk membuat tata letak anda sendiri. Untuk detail lebih lanjut, silakan buka sumber daya berikut:

* [Kode Tombol](id/keycodes.md)
* [Pertanyaan Sering Ditanyakan Tentang Tata Letak](id/faq_keymap.md)

Kami berusaha terus menerus dalam memperbaiki dokumen ini. Bila anda memiliki kritik dan saran untuk meningkatkan kualitas, silakan [buat isu](https://github.com/qmk/qmk_firmware/issues/new).
