# How to Customize Your Keyboard's Behavior
# Bagaimana Mengubah Perilaku Papan Ketik Anda

Untuk kebanyakon orang, papan ketik *custom* lebih dari sekedar mengirimkan penekanan tombol ke komputer. Anda juga ingin dapat melakukan hal-hal yang lebih rumit dari sekedar penekanan tombol dan makro. QMK memiliki kode pengait yang memperkenankan anda untuk menambah kode, mengesampingkan fungsionalitas, dan mengubah bagaimana papan ketik anda berperilaku pada situasi yang berbeda.

Laman ini tidak mengasumsikan pengetahuan khusus mengenai QMK, namun anda akan terbantu bila anda membaca [Memahami QMK](id/understanding_qmk.md)  saat ingin memahami apa yang terjadi di balik layar.

## Sebuah Petuah mengenai Inti vs Papan Ketik vs Tata Letak :id=a-word-on-core-vs-keyboards-vs-keymap

Kami menentukan struktur QMK sebagai sebuah hierarki:

* Inti (`_quantum`)
  * Papan Ketik/Revisi (`_kb`)
    * Tata Letak (`_user`)

Tiap fungsi yang dideskripsikan di bawah dapat didefinisikan dengan akhiran `_kb()` atau `_user()`. Kami bermaksud agar anda menggunakan fungsi dengan akhiran `_kb()` pada tingkat Papan Ketik/Revisi sedangkan `_user()` harus digunakan pada tingkat Tata Letak. 

Saat mendefinisikan fungsi pada tingkat Papan Ketik/Revisi, mohon untuk memastikan implementasi `_kb()` anda untuk memanggil `_user()` sebelum mengeksekusi fungsi lainnya. Bila anda tidak melakukan hal ini, fungsi pada tingkat tata letak tidak akan pernah dipanggil.

# Kode Tombol *Custom*

Sampai saat ini, hal yang paling sering dilakukan adalah mengubah perilaku dari kode tombol yang sudah ada ataupun membuat kode tombol baru. Dari sudut pandang kode, mekanisme kedua hal tersebut sangat mirip.

## Mendefinisikan sebuah Kode Tombol Baru

Langkah pertama dalam membuat kode tombol *custom* anda adalah dengan mengenumerasi mereka satu per satu. Hal ini berarti anda harus menomori dan menamai kode tombol tersebut secara unik. Kami memilih untuk membuat makro `SAFE_RANGE` yang memastikan setiap kode tombol mendapatkan nomor dan nama yang unik dibandingkan memberi batas jumlah kode tombol yang anda buat.


Sebagai contoh, berikut adalah enumerasi 2 kode tombol. Setelah menambah blok ini ke `keymap.c` anda, anda akan dapat menggunakan `FOO` dan `BAR` pada tata letak anda.

```c
enum my_keycodes {
  FOO = SAFE_RANGE,
  BAR
};
```

## Memogram Perilaku Kode Tombol Manapun :id=programming-the-behavior-of-any-keycode

Saat anda ingin mengesampingkan perilaku bawaan dari tombol yang sudah ada atau ingin mendefinisikan perilaku sebuah tombol baru, anda harus menggunakan fungsi `process_record_kb()` dan `process_record_user()`. Kedua fungsi tersebut dipanggil QMK saat pemrosesan tombol sebelum *event* tombol benar benar diproses. Bila fungsi-fungsi tadi mengembalikan nilai `true`, QMK akan memproses kode tombol seperti biasa. Hal tersebut berguna pada saat menambah fungsionalitas sebuah tombol. Namun, bila fungsi tersebut mengembalikan nilai `false`, QMK akan melewatkan penangangan tombol tersebut dan menyerahkan kepada anda untuk mengatur apa yang harus dilakukan pada saat *event* tombol naik maupun turun.

Fungsi-fungsi ini dipanggil pada saat sebuah tombol ditekan maupun dilepas.

### Contoh Implementasi `process_record_user()`

Pada contoh ini, terjadi dua hal yaitu, menentukan perilaku kode tombol *custom* `FOO` dan menambah perilaku tombol `Enter` dengan memainkan nada setiap kali tombol tersebut ditekan.

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // Lakukan sesuatu saat ditekan
      } else {
        // Lakukan hal lain saat dilepas
      }
      return false; // Lewatkan semua pemrosesan lebih lanjut tombol ini
    case KC_ENTER:
      // Mainkan nada ketika `enter` ditekan
      if (record->event.pressed) {
        PLAY_SONG(tone_qwerty);
      }
      return true; // Biarkan QMK mengirimkan *event* tekan/lepas
    default:
      return true; // Proses semua kode tombol secara normal
  }
}
```

### Dokumentasi Fungsi `process_record_*`

* Papan Ketik/Revisi: `bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
* Tata Letak: `bool process_record_user(uint16_t keycode, keyrecord_t *record)`

Argumen `keycode` merupakan apapun yang didefinisikan pada tata letak anda, misalkan `MO(1)`, `KC_L`, dll. Anda harus menggunakan blok `switch...case` untuk menangani *event* ini.

Argemen `record` berisi semua informasi mengenai penekanan:

```c
keyrecord_t record {
  keyevent_t event {
    keypos_t key {
      uint8_t col
      uint8_t row
    }
    bool     pressed
    uint16_t time
  }
}
```

# Kode Penginisialisasian Papan Ketik

Dikarenakan penginisialisasian papan ketik terdiri dari beberapa langkah, fungsi yang harus anda gunakan akan bergantung dari apa yang ingin and lakukan. 

Berikut tiga fungsi utama dari penginisialisasikan, urut berdasarkan pemanggilan.

* `keyboard_pre_init_*` - Dipanggil sebelum, hampir semua, dijalankan. Disarankan untuk setup perangkat keras yang ingin anda jalankan sangat awal.
* `matrix_init_*` - Dipanggil pada saat proses pemulaian perangkat tegar. Perangkat keras sudah diinisialisasi, namun fitur fitur lain mungkin belum dipanggil.
* `keyboard_post_init_*` - Dipanggil pada akhir proses pemulian perangkat tegar. Anda hampir selalu ingin menulis kode *custom* disini.

!> Bagi kebanyakan orang, fungsi `keyboard_post_init_user` adalah  fungsi yang semestinya anda gunakan. Sebagai contoh, disinilah anda harus mengatur fitur-fitur seperti RGB, misalnya.

## Kode Pra-Inisialisasi Papan Ketik

Kode ini akan dijalankan sangat awal pada saat pemulaian, bahkan sebelum USB dijalankan.

Setelahnya, baru matriks diinisialisasi.

Bagi kebanyakan pengguna, kode ini tidak perlu ditambahkan karena utamanya bagian ini dimaksudkan untuk inisialisasi perangkat keras.

Namun, bila perangkat keras yang ingin anda gunakan harus diinisialisasi seperti pin LED, proses ini merupakan tempat yang paling tepat.

### Contoh Implementasi `keyboard_pre_init_user()`

Pada contoh ini, pada tingkat papan ketik, mengatur B0, B1, B2, B3, dan B4 sebagai pin LED.

```c
void keyboard_pre_init_user(void) {
  // panggil kode pra-inisialiasi papan ketik.

  // Atur pin LED sebagai keluaran
  setPinOutput(B0);
  setPinOutput(B1);
  setPinOutput(B2);
  setPinOutput(B3);
  setPinOutput(B4);
}
```

### Dokumentasi fungsi `keyboard_pre_init_*`

* Papan Ketik/Revisi: `void keyboard_pre_init_kb(void)`
* Tata Letak: `void keyboard_pre_init_user(void)`

## Kode Inisialisasi Matriks

Kode ini dipanggil saat matriks diinisialisasi dan setelah beberapa bagian perangkat keras dimulai. Namun, sebelum banyak fitur lain diinisialisasi. Kode ini berguna untuk mempersiapkan hal-hal yang mungkin anda butuhkan di bagian lain, namun tidak berhubungan dengan perangkat keran maupun bergantung dimana bagian tersebut dimulai.


### Dokumentasi Fungsi `matrix_init_*`

* Papan Ketik/Revisi: `void matrix_init_kb(void)`
* Tata Letak: `void matrix_init_user(void)`


## Kode Pasca-Inisialisasi Papan Ketik

Kode ini dijalankan pada bagian akhir proses inisialisasi. Bagian ini berguna bila anda ingin mengubah fitur-fitur tertentu karena fitur tersebut sudah terinisialisasi.


### Contoh Implementansi `keyboard_post_init_user()`

Pada contoh ini yang dijalankan setelah semua terinisialisasi, mengatur konfigurasi cahaya bawah RGB.

```c
void keyboard_post_init_user(void) {
  // Panggil kode pasca-inisialisasi.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
}
```

### Dokumentasi Fungsi `keyboard_post_init_*`

* Papan Ketik/Revisi: `void keyboard_post_init_kb(void)`
* Tata Letak: `void keyboard_post_init_user(void)`

# Kode Pemindaian Matrikss

Sebisa mungkin, anda harus meng-*custom* papan ketik anda menggunakan `process_record_*()` dan mengaitkannya ke *event* untuk memastikan bahwa kode anda tidak memiliki pengaruh negatif pada performa papan ketik anda. Namun, pada situasi tertentu, pengaitan pada pemindaian matriks sangat diperlukan. Mohon untuk sangat amat berhati hati terhadap performa kode pada fungsi ini dikarenakan fungsi ini akan dipanggil setidaknya 10 kali per detik.

### Example `matrix_scan_*` Implementation
### Contoh Implementasi `matrix_scan_*`

Contoh ini dihilangkan. Seharusnya, anda sudah paham betul atas internal QMK untuk menulis kode ini tanpa contoh sebelum mengaitkannya kepada area yang sensitif terhadap performa. Bila anda butuh bantuan, [silakan buka isu](https://github.com/qmk/qmk_firmware/issues/new) atau [berbincang dengan kami](https://discord.gg/Uq7gcHh).

### `matrix_scan_*` Function Documentation

* Papan Ketik/Revisi: `void matrix_scan_kb(void)`
* Tata Letak: `void matrix_scan_user(void)`

Fungsi ini dipanggil tiap kali matriks dipindai, yang pada dasarnya sesering-mungkin dan sekuat UKM mampu. Selalu berhati-hati atas apapun yang anda letakkan disini karena akan dipanggil sangat sering.

Anda harus menggunakan fungsi ini bila anda membutuhkan kode pemindaian matriks *custom* . Kode ini juga digunakan untuk status keluaran *custom* seperti LED atau layar atau fungsionalitas lain yang ingin anda picu secara reguler bahkan ketika pengguna tidak sedang mengetik.

# Pemeliharaan Papan Ketik

* Papan Ketik/Revisi: `void housekeeping_task_kb(void)`
* Tata Letak: `void housekeeping_task_user(void)`

Fungsi ini dipanggil pada akhir dari semua pemrosesan QMK, sebelum iterasi proses selanjutnya. Anda dapat mengasumsikan bahwa QMK sudah mengurus pemindaian matriks saat fungsi ini sudah dijalankan. Misalkan, kondisi *layer* sudah dimutakhirkan, laporan USB sudah dikirim ke komputer inang, LED sudah mutakhirkan, dan layar sudah digambar.

Mirip dengan `matrix_scan_*` fungsi ini dipanggil sesering mungkin dan sekuat UKM mampu. Agar papan ketik anda tetap selalu responsif, sangat disarankan untuk tidak melakukan banyak hal pada pemanggilan fungsi ini dikarenakan potensi tercekiknya performa bila memang anda benar benar butuh melakukan sesuatu pada bagian ini.

# Keyboard Idling/Wake Code

Bila papan ketik anda mendukung, anda dapat mengaturnya pada mode "diam" dengan menghentikan beberapa fungsi. Contoh yang mudah adalah pencahayaan latar atau RGB. Penghentian semacam ini dapat menghemat konsumsi energi or bahkan dapat memperbaikan perilaku papan ketik anda.

Mode ini diatur oleh dua fngsi, `suspend_power_down_*` dan `suspend_wakeup_init_*` yang dipangil ketika sistem papan ketik sedang diam atau terbangun.


### Contoh Implementasi `suspend_power_down_user()` dan `suspend_wakeup_init_user()`


```c
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}
```

### Keyboard suspend/wake Function Documentation

* Papan Ketik/Revisi: `void suspend_power_down_kb(void)` dan `void suspend_wakeup_init_user(void)`
* Tata Letak: `void suspend_power_down_kb(void)` dan `void suspend_wakeup_init_user(void)`

# Kode Perubahan *Layer* :id=layer-change-code

Kode ini dijalankan tiap kali *layer* berubah. Hal ini berguna untuk indikasi *layer* atau penangangan *layer custom*.

### Contoh Implementasi `layer_state_set_*`

Contoh berikut menunjukkan bagaimana mengatur [Cahaya Bawah RGB](id/feature_rgblight.md) berdasarkan pada *layer*, menggunakan Planck sebagai contoh.

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        rgblight_setrgb (0x00,  0x00, 0xFF);
        break;
    case _LOWER:
        rgblight_setrgb (0xFF,  0x00, 0x00);
        break;
    case _PLOVER:
        rgblight_setrgb (0x00,  0xFF, 0x00);
        break;
    case _ADJUST:
        rgblight_setrgb (0x7A,  0x00, 0xFF);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0x00,  0xFF, 0xFF);
        break;
    }
  return state;
}
```

Gunakan makro `IS_LAYER_ON_STATE(state, layer)` dan `IS_LAYER_OFF_STATE(state, layer)` untuk memeriksa status dari *layer* tertentu.

Di luar fungsi `layer_state_set_*`, anda dapat menggunakan makro `IS_LAYER_ON(layer)` dan `IS_LAYER_OFF(layer)` untuk memeriksa status global *layer*.

### Dokumentasi Fungsi `layer_state_set_*`

* Papan Ketik/Revisi: `layer_state_t layer_state_set_kb(layer_state_t state)`
* Tata Letak: `layer_state_t layer_state_set_user(layer_state_t state)`


`state` merupakan *bitmask* dari *layer* aktif sebagaimana yang diterangkan pada [Tinjauan Tata Letak](id/keymap.md#keymap-layer-status)


# Konfigurasi Persisten (EEPROM)

Fitur ini dapat digunakan untuk mengkonfigurasi pengaturan persisten papan ketik anda. Pengaturan ini disimpan pada EEPROM kontroler anda, dan tersimpan seteleh mati lampu. Pengaturan ini dapat dibaca dengan fungsi `eeconfig_read_kb` dan `eeconfig_read_user` dan dapat ditulis menggunakan `eeconfig_update_kb` dan `eeconfig_update_user`. Fitur ini berguna untuk fitur-fitur yang bisa dimatikan oleh anda seperti pemindahan indikasi *layer rgb*. Terlebih lanjut, anda dapat menggunakan `eeconfig_init_kb` dan `eeconfig_init_user` untuk mengatur nilai bawaan pada EEPROM.

Namun, bagian yang rumit adalah, ada beberapa cara untuk menyimpan dan mengakses data melalui EEPROM dan tidak ada cara yang benar-benar "benar" untuk melakukannya. Terlebih lagi, anda hanya memiliki 1 DWORD (4 byte) untuk tiap fungsi.

Dan harap diingat bahwa EEPROM memiliki batas atas penulisan. Walaupun batas atas ini cukup tinggi, fitur ini bukan satu-satunya yang menulis pada EEPROM. Dan, bila anda menulis terlalu sering, anda dapat memperpendek waktu pakai papan ketik anda.

* Bila anda tidak paham dengan contoh ini, mungkin anda tidak harus menggunakan fitur ini karena cukup rumit.

### Contoh Implementasi

Berikut contoh menambah, membaca, dan menulis pengaturan. Kita menggunakan tata letak pengguna sebagai contoh disini. Contoh ini merupakan fungsi yang rumit dan banyak hal yang terjadi di dalamnya. Terlebih lagi, fungsi berikut menggunakan banyak fungsi-fungsi diatas agar bisa digunakan.


Pada berkas tata letak anda (keymap.c), tambah blok ini pada bagian paling atas.
```c
typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;

user_config_t user_config;
```

Kode diatas membuat struktur 32 bit yang bisa kit gunakan untuk menyimpan pengaturan pada memori dan menyimpannya pada EEPROM. Penggunaan struktur diatas menghilangkan kebutuhan untuk mendefinisikan variabel karena variabel-variabel sudah terdefinisi pada struktur ini. Harap diingat, `bool` menggunakan 1 bit, `uint8_t` menggunakan 8 bit, `uint16_t` menggunakan 16 bit. Anda dapat memadu-padankan tipe data, namun mengubah urutan dapat menyebabkan beberapa masalah karena pengubahan urutan juga mengubah nilai yang dibaca maupun yang ditulis.

Kita menggunakan `rgb_layer_change` untuk fungsi `layer_state_set_*` dan menggunakan `keyboard_post_init_user` dan `process_record_user` untuk mengkonfigurasi semuanya.

Sekarang, dengan menggunakan `keyboard_post_init_user` di atas, anda harus menambah `eeconfig_read_user()` untuk membuat struktur yang sudah anda buat. Dan sekarang anda dapat menggunakan struktur ini untuk mengatur fungsionalitas pada tata letak anda. Dan fungsi tersebut akan terlihat seperti ini.
```c
void keyboard_post_init_user(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();

  // Set default layer, if enabled
  if (user_config.rgb_layer_change) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_cyan();
    rgblight_mode_noeeprom(1);
  }
}
```
Fungsi di atas akan menggunakan konfigurasi EEPROM sesegera-mungkin setelah membacanya untuk mengatur warna bawaan dari RGB *layer*. Nilai *raw* pada fungsi diatas dikonversi ke struktur yang bisa digunakan berdasarkan pada apa yang telah anda buat sebelumnya.

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1); }
        break;
    case _LOWER:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_red(); rgblight_mode_noeeprom(1); }
        break;
    case _PLOVER:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_green(); rgblight_mode_noeeprom(1); }
        break;
    case _ADJUST:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_white(); rgblight_mode_noeeprom(1); }
        break;
    default: //  for any other layers, or the default layer
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_cyan(); rgblight_mode_noeeprom(1); }
        break;
    }
  return state;
}
```
Kode ini akan mengakibatkan pencahayaan bawah RGB berubah HANYA JIKA nilainya dinyalakan. Dan untuk mengkonfigurasi nilai ini, buat sebuah ode tombol baru untuk `process_record_user` dengan nama `RGB_LYR`. Sebagai tambahan, anda harus memastikan bahwa anda menggunakan kode RGB normal yang bisa dimatikan. Menggunakan kode pada bagian sebelumnya, buat menjadi seperti ini.
```c

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // Do something when pressed
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    case KC_ENTER:
        // Play a tone when enter is pressed
        if (record->event.pressed) {
            PLAY_SONG(tone_qwerty);
        }
        return true; // Let QMK send the enter press/release events
    case RGB_LYR:  // This allows me to use underglow as layer indication, or as normal
        if (record->event.pressed) {
            user_config.rgb_layer_change ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
            if (user_config.rgb_layer_change) { // if layer state indication is enabled,
                layer_state_set(layer_state);   // then immediately update the layer color
            }
        }
        return false;
    case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // For any of the RGB codes (see quantum_keycodes.h, L400 for reference)
        if (record->event.pressed) { //This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
            if (user_config.rgb_layer_change) {        // only if this is enabled
                user_config.rgb_layer_change = false;  // disable it, and
                eeconfig_update_user(user_config.raw); // write the setings to EEPROM
            }
        }
        return true; break;
    default:
      return true; // Process all other keycodes normally
  }
}
```
Dan bagian terakhir, anda harus menambah fungsi `eeconfig_init_user` sehingga ketika EEPROM direset, anda dapat menntukan nilai bawaan atau bahkan perlakuan khusus. Untuk memaksa peresetan EEPROM, gunakan kode tombol `EEP_RST` atau [*Bootmagic*](id/feature_bootmagic.md). Sebagai contoh, bila anda ingin mengatur nilai bawaan indikasi *layer rgb* dan menyimpannya.

```c
void eeconfig_init_user(void) {  // EEPROM is getting reset!
  user_config.raw = 0;
  user_config.rgb_layer_change = true; // We want this enabled by default
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM now

  // use the non noeeprom versions, to write these values to EEPROM too
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv_cyan();  // Set it to CYAN by default
  rgblight_mode(1); // set to solid by default
}
```

Dan selesai. Indikasi *layer RGB* hanya akan bekerja bila anda mengaktifkannya. Dan pengaturan ini tersimpan bahkan setelah anda melepas papan ketik dari komputer inang. Dan bila anda menggunakan kode RGB apapun, penggunaan kode tersebut akan mematikan indikasi *layer* sehingga akan tetap pada mode dan warna yang sudah anda atur.

### Dokumentasi Fungsi 'EECONFIG'

* Papan Ketik/Revisi: `void eeconfig_init_kb(void)`, `uint32_t eeconfig_read_kb(void)` dan `void eeconfig_update_kb(uint32_t val)`
* Tata Letak: `void eeconfig_init_user(void)`, `uint32_t eeconfig_read_user(void)` dan `void eeconfig_update_user(uint32_t val)`

The `val` is the value of the data that you want to write to EEPROM.  And the `eeconfig_read_*` function return a 32 bit (DWORD) value from the EEPROM. 
