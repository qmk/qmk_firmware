# Silabus QMK

Laman ini membantu anda menuntut ilmu mengenai QMK dengan mengenalkan dasar-dasar terlebih dahulu dan membimbing anda memahami konsep-konsep yang harus anda tahu agar mahir dalam menggunakan QMK.

# Topik Pemula

Bila anda belum pernah membaca apapun mengenai QMK, anda harus membaca dokumen pada bab ini. Setelah membaca [Tutorial](id/newbs.md), anda diharapkan bisa membuat tata letak dasar, mengompilasinya, lalu menge-*flash*-nya ke papan ketik anda. Dokumen lain akan memperdalam pengetahuan anda pada dasar-dasar berikut.

* **Belajar Menggunakan Peralatan-Peralatan QMK**
    * [Tutorial](id/newbs.md)
    * [Antarmuka Perintah Baris](id/cli.md)
    * [Git](id/newbs_git_best_practices.md)
* **Belajar Mengenai Tata Letak**
    * [*Layer*](id/feature_layers.md)
    * [Kode Tombol](id/keycodes.md)
        * Daftar lengkap kode tombol yang bisa anda gunakan. Harap dicatat, beberapa kode mungkin membutuhkan pengetahuan yang ada pada topik-topik Menengah maupun Lanjutan.
* **Konfigurasi IDE** - Optional
    * [Eclipse](other_eclipse.md)
    * [VS Code](other_vscode.md)

# Topik Menengah

Topik-topik berikut mulai mendalami beberapa fitur yang didukung oleh QMK. Anda tidak harus membaca semua dokumen dokumen ini, namun beberapa dokumen pada topik lanjutan tidak akan masuk akal bila anda melewatkan beberapa dokumen pada bagian ini.

* **Mempelajari Konfigurasi Fitur**
    <!-- * Configuration Overview  FIXME(skullydazed/anyone): write this document -->
    * [Audio](id/feature_audio.md)
    * Pencahayaan
        * [Cahaya Belakang](id/feature_backlight.md)
        * [Matriks LED](id/feature_led_matrix.md)
        * [Cahaya RGB](id/feature_rgblight.md)
        * [Matriks RGB](id/feature_rgb_matrix.md)
    * [Konfigurasi Tekan-Tahan](tap_hold.md)
* **Learn More About Keymaps**
* **Mempelajari Lebih Lanjut Tentang Tata Letak**
    * [Tata Letak](id/keymap.md)
    * [Fungsi dan Kode Tombol *Custom*](id/custom_quantum_functions.md)
    * Makro
        * [Makro Dinamis](id/feature_dynamic_macros.md)
        * [Makro Terkompilasi](id/feature_macros.md)
    * [*Tap Dance*](id/feature_tap_dance.md)
    * [Kombo](id/feature_combo.md)
    * [Ruang apengguna](id/feature_userspace.md)

# Topik Lanjutan

Semua yang ada di bawah ini membutuhkan banyak pengetahuan dasar. Selain mampu membuat tata letak menggunaka fitur lanjutan, anda juga harus mahir menggunakan `config.h` dan `rules.mk` untuk mengkonfigurasi pilihan-pilihan untuk papan ketik anda.

* **Maintaining Keyboards Within QMK**
* **Pemeliharaan Papan Ketik Dengan QMK**
    * [Handwiring a Keyboard](id/hand_wire.md)
    * [Panduan Papan Ketik](id/hardware_keyboard_guidelines.md)
    * [referensi info.json](id/reference_info_json.md)
    * [Debounce API](id/feature_debounce_type.md)
* **Fitur Lanjutan**
    * [Unikode](id/feature_unicode.md)
    * [API](id/api_overview.md)
    * [Bootmagic](id/feature_bootmagic.md)
* **Perangkat Keras**
    * [Bagimana Papan Ketik Bekerja](id/how_keyboards_work.md)
    * [Bagaimana Matriks Papan Ketik Bekerja](id/how_a_matrix_works.md)
    * [Papan Ketik Belah](id/feature_split_keyboard.md)
    * [Stenografi](id/feature_stenography.md)
    * [Piranti Penunjuk](id/feature_pointing_device.md)
* **Pengembangan Inti**
    * [Konvensi Pemrogramman](id/coding_conventions_c.md)
    * [Kontroler Mikro yang Sesuai](id/compatible_microcontrollers.md)
    * [Matriks *custom*](id/custom_matrix.md)
    * [Memahami QMK](id/understanding_qmk.md)
* **Pengembangan Antarmuka Perintah Baris**
    * [Konvensi Pemrograman](id/coding_conventions_python.md)
    * [Ikhtisar Pengembangan Antarmuka Perintah Baris](id/cli_development.md)
