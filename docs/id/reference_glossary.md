# Glosarium Istilah QMK

## ARM
Merupakan lini unit kontroler mikro yang diproduksi oleh beberapa perusahaan seperti Atmel, Cypress, akinetis, NXP, ST, dan TI.

## AVR
Merupakan lini unit kontroler mikuro yang diproduksi oleh [Atmel](https://microchip.com). AVR merupakan platform asli yang didukung TMK.

## AZERTY
Standar tata letak papan ketik Français (Perancis). Dinamai dari 6 tombol pertama pada papan ketik.

## Bluetooth
Merupakan protokol nirkabel ujung-ke-ujung jarak dekat. Merupakan protokol nirkabel paling jamak ditemui pada papan ketik.

## *Bootloader*
Program kuhusus yang ditulis pada area terlindungi pada unit kontroler mikro anda yang memperkenannka unit kontroler mikro untuk memutakhirkan perangkat tegarnya sendiri yang biasanya melalui USB.

## *Bootmagic*
Sebuah fitur yang memperkenankan berbagai macam perubahan perilaku papan ketik pada saat papan ketik digunakan. Seperti penukaran atau penonaktifan tombol-tombol umum.

## C
Merupakan bahasa pemrograman tingkat rendah yang cocok untuk kode pada sistem. Kebanyakan kode QMK ditulis menggunakan C.

## Cahaya Bawah
Merupakan istilah umum untuk LED yang menyinari bagian bawah papan. LED ini biasanya bersinar dari bagian bawah PCB menuju permukaan dimana papan ketik bersandar.

## Cahaya Belakang
Merupakan istilah umum untuk pencahayaan pada papan ketik. Cahaya lakang biasanya, namun tidak selalu, merupakan senarai LED yang bersinar melalui helm tombol dan/atau saklar.

## Colemak
Merupakan tata letak alternatif yang mulai populer.

## Dvorak
An alternative keyboard layout developed by Dr. August Dvorak in the 1930's. A shortened form of the Dvorak Simplified Keyboard.
Merupakan tata letak alternatif yang dikembangkan oleh Dr. August Dvorak pada tahun 1930an. Merupakan kependekan dari *Dvorak Simplified Keyboard*.

## Eclipse
Merupakan IDE yang populer di kalangan pengembang C.

* [Instruksi pengaturan Eclipse](id/other_eclipse.md)

## git
Perangkat lunak pemversian yang digunakan pada perintah baris.

## GitHub
Merupakan situs yang menjadi induk semang dari proyek QMK. situs ini menyediakan integrasi dengan git, pelacakan masalah, dan berbagai fitur yang membantu kami menjalankan QMK.

## ISP
*In-system programming*, sebuah metoda pemrograman pada ovr menggunakan perangkat keras eksternal dan menggunakan pin JTAG.

## hid_listen
Merupakan antarmuka untuk menerima pesan-pesan pengawakutuan dari papan ketik anda. Anda dapat melihat pesan-pesan tersebut menggunakan [QMK Flasher](https://gihtub.com/qmk/qmk_flasher) atau [hid_listen buatan PJRC](https://pjrc.com/teensy/hid_listen.html).

## Kode Pemindaian
Merupakan angka 1 byte yang dikirim sebagai laporan HID melalui USB yang merepresentasikan sebuah tombol. Angka ini didokumentasikan pada [Tabel penggunaan HID](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf) yang diterbitkan oleh [USB-IF](https://www.usb.org).

## Kode Tombol
Merupakan nomor dengan ukuran 2-byte yang merepresentasikan tombol tertentu. `0x00` - `0xFF` digunakan untuk [Kode Tombol Dasar](id/keycodes_basic.md) sedangkan `0x100` - `0xFFFF` digunakan untuk [Kode Tombol Quantum](id/quantum_keycodes.md).

## Kompilasi
Proses pengubahan kode yang terbaca manusia menjadi kode yang bisa dijalankan oleh unit kontroler mikro anda.

## *Layer*
Merupakan abstraksi yang digunakan agar sebuah tombol dapat digunakan untuk berbagai fungsi. *Layer* paling tinggi diprioritaskan.

## LED
*Light Emitting Diode*, merupakan piranti yang paling umum digunakan untuk indikator pada sebuah papan ketik.

## `Make`
Merupakan perangkat lunak yang digunakan untuk mengompilasi semua kode sumber. Anda menjalankan `make` dengan berbagai pilihan untuk mengompilas perangkat tegar papan ketik anda.

## Makro Dinamis
Merupakan makro yang direkan pada papan ketik dan akan hilang saat papan ketik dilepas ataupun setelah komputer dinyalakan ulang.

* [Dokumentasi Makro Dinamis](id/feature_dynamic_macros.md)

## Matriks
Pola pengkabelan pada kolom dan baris yang memperkenankan unit kontroler mikro untuk mendeteksi ketukan pada tombol dengan penggunaan jumlah pin yang lebih rendah. Matriks sering kali juga menggunakan dioda agar NKRO bisa digunakan.

## Makro
Merupakan fitur yang memperkenankan anda untuk mengirimpan beberapa kejadian pengetukan tombol  (laporan hid) setelah mengetuk satu tombol saja.

* [Dokumentasi Makro](feature_macros.md)

## MCU
Unit Kontroler Mikro, prosesor yang mendayagunakan papan ketik anda.

## *Modifier*
Sebuah tombol yang bila ditahan saat mengetuk tombol lain akan mengubah fungsi dari tombol tadi. Sebagai contoh, *Ctrl*, *Alt*, dan *Shift*.

## *N-Key Rollover (NKRO)*
Sebuah istilah yang mengacu pada papan ketik yang mampu melaporkan berapapun kejadian pengetukan tombol pada saat yang bersamaan.

## *Oneshot Modifier*
Sebuah *modifier* yang berperilaku seakan tetap ditahan sampai tombol loin dilepaskan. Hal ini memperkenankan anda untuk mengetuk tombol *mod* dan mengetuk tombol, bukan menahan *mod* sambil mengetuk tombol. Juga dikenali sebagai tombol lengket atau tombol mati.

## Permintaan Tarik
Sebuah permintaan untuk mengirimkan kode ke QMK. Kami mendorong semua pengguna untuk mengirimkan permintaan tarik untuk tata letak personal mereka.

## Perangkat Tegar
Perangkat lunak yang mengendalikan unit kontroler mikro anda.

## ProMicro
Merupakan papan pengembangan AVR yang rendah. Klon dari piranti ini sering kali ditemukan di internet dengan harga sangat murah (kurang dari Rp. 700.000,00) walaupun sering kali memiliki masalah pada saat penge-*flash*-an.

## QWERTY
Merupakan tata letak standar papan ketik Inggris dan sering kali merupakan nama panggilan untuk tata letak bahasa lain. Dinamai dari 6 huruf pertama pada papan ketik.

## QWERTZ
Merupakan tata letak standar papan ketik Jerman. Dinamai dari 6 huruf pertama pada papan ketik.

## *Rollover*
Istilah untuk pengetukan tombol saat sebuah tombol sudah terketuk. Varian mencakup 2KRO, 6KRO, dan NKRO.

## *Space Cadet Shift*
Kumpulan tombol *shift* khusus yang memperkenankan anda untuk menulis berbagai macam tanda kurung dengan mengetuk *shift* kiri ataupun kanan satu kali atau lebih.

* [Dokumentasi Space Cadet Shift](id/feature_space_cadet_shift.md)

## Ketuk
Menekan dan melepaskan sebuah tombol. Pada beberapa situasi, anda harus membedakan antara kejadian tombol turun dan tombol naik. Ketuk selalu mengacu pada keduanya secara berurutan.

## Tata Letak
Merupakan seranai tombol kode yang dipetakan pada tata letak fisik papan ketik yang diproses pada pengetukan dan pelepasan tombol.

## Tombol Turun
Merupakan kejadian dimana sebuah tombol diketuk yang selesai sebelum tombol tersebut dilepas.

## Tombol Naik
Merupakan kejadian dimana sebuah tombol dilepas setelah diketuk.

## Tombol *Leader*
Fitur yang memperkenankan anda untuk mengetuk tombol *leader* disusul beberapa tombol (bisa 1, 2, atau 3) untuk mengaktifkan pengetukan tombol atau fitur *quantum* lainnya.

* [Dokumentasi Tombol *Leader*](id/feature_leader_key.md)

## Tombol Tetikus
Fitur yang memperkenankan anda untuk mengendalikan kursor tetikus anda dan mengeklik dari papan ketik anda.

* [Dokumentasi Tombol Tetikus](id/feature_mouse_keys.md)

## *Tap Dance*
Fiture yang memperkenankan anda untuk menetapkan beberapa kode tombol pada tombol yang sama berdasarkan berapa kali anda menekannya.

* [Dokumentasi *Tap Dance*](id/feature_tap_dance.md)

## Teensy
Merupakan papan pengembangan AVR yang sering digunakan pada pembuatan yang menggunakan pengkabelan manual. Sebuah teensy sering dipilih walaupun memakan biaya beberapa puluh ribu lebih mahal karena *bootloader* halfkay yang membuat penge-*flash*-an sangat mudah.

## Unikode
Merupakan skema penyandian yang digunakan untuk merepresentasikan karakter pada semua bahasa. Karena hal ini berkaitan dengan QMK, berarti QMK menggunakan skema dari bermacam-macam sistem operasi untuk mengirim titik kode unikode, bukan kode pindai.

* [Dokumentasi Unikode](id/feature_unicode.md)

A framework for running automated tests against QMK. Unit testing helps us be confident that our changes do not break anything.
Sebuah kerangka kerja untuk menjalankan tes terotomasi pada QMK. *Unit testing* membantu kami untuk lebih percaya diri bahwa perubahan yang kami lakukan tidak merusak apapun.

* [Dokumentasi *Unit Testing*](id/unit_testing.md)

## USB
Universal Serial Bus, merupakan antarmuka kabel yang paling umum untuk papan ketik.

## USB Inang (atau Inang)
USB Inang merupakan komputer anda ataupun piranti apapun yang papan ketik anda menyambung. 

# Tidak Dapat Menemukan Istilah Yang Anda Cari?

[Buka isu](https://github.com/qmk/qmk_firmware/issues) yang berisi pertanyaan anda dan istilah yang bisa jadi dimasukkan pada dokumentasi ini. Adalah lebih bagus bila anda membuat permintaan tarik berisi definisi tersebut. :)