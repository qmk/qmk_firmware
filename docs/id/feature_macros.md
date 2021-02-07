# Makro

Makro memperkenankan anda untuk mengirim beberapa penekanan tombol hanya dengan menekan 1 tombol. QMK memiliki beberapa cara untuk menentukan dan menggunakan makro. Makro tersebut dapat berupa apapun yang anda inginkan seperti mengetik kalimat-kalimat umum, *copypasta*, pergerakan gim yang repetitif, atau bahkan membantu anda dalam menulis program.

!> **Catatan Keamanan**: Walaupun penggunaan makro untuk mengirim kata-sandi, nomor kartu kredit, dan informasi sensitif lainnya adalah mungkin. Hal semacam ini merupakan hal yang bodoh. Siapapun dapat memegang papan ketik anda dan dapat mengkses informasi tadi dengan menggunakan penyunting berkas.

## Cara Baru: `SEND_STRING()` & `process_record_user`

Kadang kala, anda ingin memilki sebuah tombol yang dapat menulis kata maupun kalimat. Pada situasi kebanyakan, kami sudah menyediakan `SEND_STRING()` yang akan mengetik string (mis., rentetan karakter) untuk anda. Semua karakter ASCII yang dapat dengan mudah diterjemahkan ke kode tombol didukung oleh makro tersebut, (mis. `qmk 123\n\t`).

Berikut sebuah contoh `keymap.c` untuk papan ketik dengan dua tombol:

```c
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            // Saat kode tombol QMKBEST ditekan
            SEND_STRING("QMK is the best thing ever!");
        } else {
            // saat kode tombol QMKBEST dilepaskan
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {QMKBEST, KC_ESC},
        // ...
    },
};
```

Yang terjadi di sini adalah:
Pertama, sebuah kode tombol *custom* didefinisikan pada rentang yang tidak digunakan oleh kode tombol lain. Dilanjutkan dengan menggunakan fungsi `process_record_user` yang dipanggil ketika sebuah tombol ditekan maupun dilepaskan untuk memeriksa apakah kode tombol *custom* kita telah diaktifkan. Bila kode tombol tersebut diaktifkan, strin `"QMK is the best thing ever"` akan dikirimkan ke komputer dengan makro `SEND_STRING` (makro ini merupakan makro C, bukan makro QMK). Dilanjutkan dengan mengembalikan `true` untuk mengindikasikan pada pemanggil bahwa tombol yang barusan diproses harus lanjut diproses seperti biasa (karena tombol tersebut tidak diubah fungsionalitasnya). Pada akhirnya, kita mendefinisikan tata letak yang sedemikian hingga pada tombol pertama akan mengaktifkan makro tadi, dan tombol kedua hanya berupa tombol `escape`.

Bisa jadi anda ingin menambah lebih dari satu makro. Hal tersebut bisa dicapai dengan menambah kode tombol lain dan menambahkan `case` lain pada statemen `switch` seperti berikut:

```c
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
    MY_OTHER_MACRO,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            // saat kode tombol QMKBEST ditekan.
            SEND_STRING("QMK is the best thing ever!");
        } else {
            // saat kode tombol QMKBEST dilepaskan.
        }
        break;

    case QMKURL:
        if (record->event.pressed) {
            // saat kode tombol QMKURL ditekan.
            SEND_STRING("https://qmk.fm/\n");
        } else {
            // saat kode tombol QMKURL dilepaskan.
        }
        break;

    case MY_OTHER_MACRO:
        if (record->event.pressed) {
           SEND_STRING(SS_LCTL("ac")); // memilih semua dan menyalinnya.
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {MY_CUSTOM_MACRO, MY_OTHER_MACRO},
        // ...
    },
};
```

### Makro Lanjutan

Sebagai tambahan pada fungsi `process_record_user()`, ada juga fungsi `post_process_record_user()`. Fungsi ini dijalankan setelah `process_record` dan dapat digunakan untuk melakukan hal-hal setelah sebuah penekanan tombol dikirim ke komputer. Fungsi ini berguna, misalkan, saat anda ingin menekan dan melepaskan sebuah tombol setelah tombol lain.

Pada contoh ini, kita memodifikasi penekanan tombol normal sedemikian rupa sehingga `F22` ditekan sebelum rapor penekanan tombol lain dikirim ke komputer dan melepaskan tombol `F22` __hanya setelah__ tombol lain tadi dilepaskan.

```c
static uint8_t f22_tracker;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_A ... KC_F21: // perhatikan bahwa F22 dilewatkan
    case KC_F23 ... KC_EXSEL: // exsel merupakan kode tombol terakhir sebelum tombol *modifier*
      if (record->event.pressed) {
        register_code(KC_F22); // baris ini berarti QMK menekan tombol F22
        f22_tracker++;
        register_code(keycode);
        return false;
      }
      break;
  }
  return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_A ... KC_F21: // perhatikan bahwa F22 dilewatkan
    case KC_F23 ... KC_EXSEL: // exsel merupakan kode tombol terakhir sebelum tombol *modifier*
      if (!record->event.pressed) {
        f22_tracker--;
        if (!f22_tracker) {
            unregister_code(KC_F22); // baris ini berarti QMK melepaskan tombol F22
        }
      }
      break;
  }
}
```


### *TAP*, *DOWN*, dan *UP*

Anda mungkin ingin menggunakan tombol-tombol yang tidak bisa anda tulis pada makro anda seperti `Ctrl` atau `Home`. Walaupun anda tidak dapat menulis kode-kode semacam itu, anda dapat mengirimkan kode tombol arbiter dengan membalut kode tersebut dengan:

* `SS_TAP()` menekan dan melepaskan sebuah tombol.
* `SS_DOWN()` menekan namun tidak melepas tombol.
* `SS_UP()` melepas tombol.

Sebagai contoh:

    SEND_STRING(SS_TAP(X_HOME));

Akan mengetuk `KC_HOME`. Harap perhatikan awalannya adalah `X_`, bukan `KC_`. Anda juga dapat mengkombinasi dengan string lain seperti:

    SEND_STRING("VE"SS_TAP(X_HOME)"LO");

Yang akan mengirimkan "VE" diikuti dengan sebuah ketukan pada `KC_HOME` dan "LO" ("LOVE" akan tereja bila kursor ada pada baris baru).

Jeda juga dapat ditambahkan ke string.

* `SS_DELAY(msecs)` akan memberi jeda untuk angka yang ditentukan dalam milidetik.

Sebagai contoh:

    SEND_STRING("VE" SS_DELAY(1000) SS_TAP(X_HOME) "LO");

Yang akan mengirim "VE" dilanjutkan dengan jeda 1 detik dan sebuah ketikan `KC_HOME`, dan pada akhirnya "LO" ("LOVE" akan tereja bila kursor ada pada barus baru, namun terjeda pada tengah tengah).

Ada juga beberapa pintasan untuk *mod* yang dapat anda gunakan:

* `SS_LCTL(string)`
* `SS_LSFT(string)`
* `SS_LALT(string)` atau `SS_LOPT(string)`
* `SS_LGUI(string)`, `SS_LCMD(string)` atau `SS_LWIN(string)`
* `SS_RCTL(string)`
* `SS_RSFT(string)`
* `SS_RALT(string)`, `SS_ROPT(string)` atau `SS_ALGR(string)`
* `SS_RGUI(string)`, `SS_RCMD(string)` atau `SS_RWIN(string)`

Pintasan diatas akan menekan *modifier* terkait dan mengirimkan string dilanjutkan dengan pelepasan *modifier* tersebut. Pintasa tersebut dapat digunakan seperti ini:

    SEND_STRING(SS_LCTL("a"));

Yang akan mengirimkan *Control* Kiri+`a` (*Control* Kiri turun, `a`, *Control* Kiri naik). Harap diperhatikan bahwa pintasan-pintasan diatas menerima string, bukan kode tombol seperti `X_K`.

### Tata Letak Alternatif

Secara bawaan, makro selalu mengasumsikan penggunaan tata letak US QWERTY; bila anda ingin menggantinya (misal, sistem operasi anda menggunakan perangkat lunak Colemak), ikutsertakan baris berikut pada tata letak anda:

```c
#include "sendstring_colemak.h"
```

### String pada Memori

Bila anda, untuk alasan-alasan tertentu, memanipulasi string dan mengharuskan untuk mencetak string yang barusan anda manipulasi (bukan string konstan pada umumnya), anda dapat menggunakan `send_string()` seperti berikut:

```c
char my_str[4] = "ok.";
send_string(my_str);
```

Pintasan yang didefinisikan di atas tidk akan bekerja dengan `send_string()`, namun anda dapat memisahkannya menjadi beberapa bagian, bila diperlukan:

```c
char my_str[4] = "ok.";
SEND_STRING("I said: ");
send_string(my_str);
SEND_STRING(".."SS_TAP(X_END));
```


## Fungsi Makro Lanjutan

Ada beberapa fungsi yang mungkin berguna bila anda menulis makro. Mohon diingat walaupun anda dapat menulis kode yang cukup rumit dengan sebuah makro, bila fungsi yang ingin anda capai terlalu kompleks, mohon untuk mempertimbangkan menggunakan sebuah kode tombol *custom* dikarenakan makro seharusnya sederhana.

?> Anda juga dapat menggunakan fungsi-fungsi yang dideskripsikan pada [Fungsi-fungsi berguna](id/ref_functions.md) untuk tambahan fungsionalitas. sebagai contoh, `reset_keyboard()` memperkenankan anda untuk mereset papan ketik sebagai bagian dari sebuah makro.

### `record->event.pressed`

`record->event.pressed` merupakan sebuah nilai boolean yang dapat dites untuk mengetahui apaka sebuah tombol sedang ditekan atau tidak. Sebuah contoh untuk penggunaan nilai ini adalah:

```c
    if (record->event.pressed) {
        // on keydown
    } else {
        // on keyup
    }
```

### `register_code(<kc>);`

Fungsi ini mengirim *event* tombol turun `<kc>` ke komputer. Beberapa contoh bisa jadi `KC_ESC`, `KC_C`, `KC_4`, dan bahkan *modifier* seperti `KC_LSFT` dan `KC_LGUI`.

### `unregister_code(<kc>);`

Paralel dengan fungsi `register_code`, fungsi ini mengirim *event* tombol naik `<kc>` ke komputer. Bila anda tidak menggunakan fungsi ini, tombol akan tetap ditahan sampai dikirimkan.

### `tap_code(<kc>);`

Fungsi ini akan mengirim `register_code(<kc>)` dan `unregister_code(<kc>)`. Tombol ini berguna bila anda ingin mengirim *event* penekanan dan pelepasan ("ketuk" tombol, bukan menahannya).

Bila anda mengalami masalah dengan ketukan yang tidak terlepas, anda dapat menambah jeda antar *event* penekanan dan pelepasangan dengan menyetting `#define TAP_CODE_DELAY 100` pada berkas `config.h` anda. Nilai `100` tadi dalam mili detik.

### `register_code16(<kc>);`, `unregister_code16(<kc>);` dan `tap_code16(<kc>);`

Fungsi-fungsi ini bekerja mirip dengan fungsi pembandingnya. Namun, fungsi ini menggunakan kode tombol ter-*mod* dengan *Shift, Alt, Control,* dan/atau *GUI*.

Misalkan, anda dapat menggunakan `register_code16(S(KC_5));` bukan meregister *mod* lalu meregister kode tombol.

### `clear_keyboard();`

Fungsi ini akan melepaskan semua tombol dan *mod* yang sedang ditekan.

### `clear_mods();`

Fungsi ini akan melepaskan semua *mod* yang sedang ditekan.

### `clear_keyboard_but_mods();`

Fungsi ini akan melepaskan semua tombol kecuali *mod* yang sedang ditekan.

## Contoh Lanjutan:

### Super ALT↯TAB

Makro ini akan meregister `KC_LALT` dan mengetuk `KC_TAB` lalu menanti 1000milidetik. Bila tombol ini diketuk lagi, tombol tersebut akan mengirim `KC_TAP`. Bila tidak ada pengetukan, `KC_LALT` akan diunregister. Makro ini memperkenankan anda untuk memutar jendela-jendela yang terbuka.

```c
bool is_alt_tab_active = false;    # Tambahkan baris ini pada awal keymap.c
uint16_t alt_tab_timer = 0;        # kita akan menggunakannya segera.

enum custom_keycodes {             # Pastikan kode tombol sudah disiapkan.
  ALT_TAB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {               # Bagian ini akan menangani apa yang harus dilakukan pada kode tombol.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {     # Timer ini sangat penting.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
```

---

##  **(DEPRECATED)** The Old Way: `MACRO()` & `action_get_macro`
##  **(USANG)** Cara Lama: `MACRO()` & `action_get_macro`

!> Cara ini diwarisi dari TMK dan tidak dimutakhirkan. Anda dianjurkan untuk menggunakan `SEND_STRING` dan `process_record_user`.

Secara bawaan, QMK menganggap anda tidak memiliki makro. Untuk mendefinisikan makro, anda harus membuat fungsi `action_get_macro()`. Sebagai contoh:

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO(D(LSFT), T(H), U(LSFT), T(I), D(LSFT), T(1), U(LSFT), END);
            case 1:
                return MACRO(D(LSFT), T(B), U(LSFT), T(Y), T(E), D(LSFT), T(1), U(LSFT), END);
        }
    }
    return MACRO_NONE;
};
```

Fungsi ini mendefinisikan dua makro yang akan dijalankan ketika tombol yang ditentukan tertekan. Bila anda ingin menjalankan makro saat tombol dilepas, mohon ubah statemen percabangan menjadi:

    if (!record->event.pressed) {

### Perintah Makro

Sebuah makro dapat mengikutsertakan perintah berikut:

* I() mengubah interval penekanan pada milidetik.
* D() menekan tombol.
* U() melepas tombol.
* T() mengetuk tombol (tekan dan lepas).
* W() tunggu (milidetik).
* END tanda selesai.

### Mapping a Macro to a Key
### Memetakan Makro ke Tombol

Gunakan fungsi `M()` pada tata letak anda untuk memanggil sebuah makro. Sebagai contoh, berikut tata letak dari papan ketik dua tombol:

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        M(0), M(1)
    ),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO(D(LSFT), T(H), U(LSFT), T(I), D(LSFT), T(1), U(LSFT), END);
            case 1:
                return MACRO(D(LSFT), T(B), U(LSFT), T(Y), T(E), D(LSFT), T(1), U(LSFT), END);
        }
    }
    return MACRO_NONE;
};
```

Bila anda menekan tombol kiri, tombol tersebut akan mengetik "Hi!" dan bila anda menekan tombol kanan, tombol tersebut akan mengetik "Bye!".

### Menamai Makro Anda

Bila anda memiliki beberapa makro, mungkin anda ingin merujuknya dari tata letak sembari tetap berupaya agar tata letak tersebut tetap mudah dibaca. Anda dapat menamainya dengan menggunakan `#define` pada bagian atas `keymap.c` anda.

```c
#define M_HI M(0)
#define M_BYE M(1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        M_HI, M_BYE
    ),
};
```


## Contoh Lanjutan:

### Tombol Salin/Tempel Tunggal

This example defines a macro which sends `Ctrl-C` when pressed down, and `Ctrl-V` when released.
Contoh berikut mendefinisikan sebeuah makro yang mengirim `Ctrl-C` saat ditekan dan `Ctrl-V` saat dilepaskan.

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch(id) {
        case 0: {
            if (record->event.pressed) {
                return MACRO( D(LCTL), T(C), U(LCTL), END  );
            } else {
                return MACRO( D(LCTL), T(V), U(LCTL), END  );
            }
            break;
        }
    }
    return MACRO_NONE;
};
```
