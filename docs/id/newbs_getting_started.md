# Mempersiapkan Lingkungan Bangun QMK

Sebelum anda dapat membangun tata letak papan ketik, anda harus memasang beberapa perangkat lunak dan mempersiapkan lingkungan bangun anda. Persiapan ini hanya perlu dilakukan sekali, tanpa mempedulikan berapa banyak perangkat tegar papan ketik yang ingin kompilasi.

## 1. Prasyarat

Ada beberapa perangkat lunak yang anda butuhkan untuk memulai.

* [Penyunting teks](id/newbs_learn_more_resources.md#text-editor-resources)
  * Anda akan membutuhkan sebuah program yang mampu menyunting dan menyimpan berkas teks biasa. Penyunting bawaan banyak Sistem Operasi tidak dapat menyimpan berkas teks biasa yang mengharuskan anda untuk berhati hati dalam memilih penyunting.
* [*Toolbox* (pilihan)](https://github.com/qmk/qmk_toolbox)
  * Sebuah proogram grafis untuk Windows dan macOS yang memungkinkan anda untuk memprogram dan mengawakutu papan ketik *custom* anda.

?> Bila anda belum pernah menggunakan antarmuka baris perintah Linux/Unix, ada beberapa konsep dasar dan perintah-perintah yang harus anda pelajari. [Sumber daya berikut](id/newbs_learn_more_resources.md#command-line-resources) akan membantu anda dalam menggunakan QMK.

## 2. Prepare Your Build Environment :id=set-up-your-environment
## 2. Persiapkan Lingkungan Bangun Anda :id=set-up-your-environment

Kami telah berusaha agar QMK dapat dipersiapkan semudah mungkin. Anda hanya perlu mempersiapkan lingkungan Linux atau Unix anda, lalu biarkan QMK mengatur sisanya.

<!-- tabs:start -->

### ** Windows **

QMK memelihara sebuah bundel MSYS2 yang berisi antarmuka baris perintah dan semua ketergantungannya. Bundel ini juga menyediakan pintasan `QMK MSYS` agar anda dapat langsung menggunakan lingkungan yang tepat.

#### Prasyarat

Anda harus memasang [QMK MSYS](https://msys.qmk.fm/). Rilis terbaru tersedia pada [pranala ini](https://github.com/qmk/qmk_distro_msys/releases/latest).

Bila anda tidak menggunakan QMK MSYS, anda dapat memasang MSYS2 secara manual dengan mengikuti langkah langkah berikut.

<details>
  <summary>Pemasangan Manual</summary>

?> Abakaikan langkah berikut bila anda menggunakan `QMK MSYS`.

#### Prasyarat

Anda harus memasang MSYS2, Git, dan Python. Ikuti instruksi pemasangan pada https://www.msys2.org.

Setelah MSYS2 terpasang, tutup semua terminal MSYS dan buka terminal MinGW 64-bit baru.

!> **CATATAN:** Terminal MinGW 64-bit *tidak* sama dengan terminal MSYS yang terbuka pada saat pemasangan selesai. *Prompt* anda harus menunjukkan "MINGW64" dengan teks warna ungu, bukan "MSYS". Lihat [laman ini](https://www.msys2.org/wiki/MSYS2-introduction/#subsystems) untuk informasi perbedaan lebih lanjut.

Lalu jalankan perintah berikut:

    pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip

#### Pemasangan

Pasang antarmuka baris perintah QMK dengan menjalankan:

    python3 -m pip install qmk

</details>

### ** macOS **

QMK memelihara keran dan formula Homebrew yang akan memasang antarmuka baris perintah QMK dan semua ketergantungan yang dibutuhkan.

#### Prasyarat

Anda harus memasang Homebrew. Ikuti instruksi berikut pada https://brew.sh.

#### Pemasangan

Pasang antarmuka baris perintah QMK dengan menjalankan:

    brew install qmk/qmk/qmk

### ** Linux/WSL **

#### Prasyarat

Anda harus memasang Git dan Python. Sangat memungkinkan bila kedua program tersebut telah terpasang pada komputer anda. Namun, bila keduanya belum terpasang, ikuti perintah berikut untuk melakukannya:

* Debian / Ubuntu / Devuan: `sudo apt install -y git python3-pip`
* Fedora / Red Hat / CentOS: `sudo yum -y install git python3-pip`
* Arch / Manjaro: `sudo pacman --needed --noconfirm -S git python-pip libffi`
* Void: `sudo xbps-install -y git python3-pip`
* Solus: `sudo eopkg -y install git python3`
* Sabayon: `sudo equo install dev-vcs/git dev-python/pip`
* Gentoo: `sudo emerge dev-vcs/git dev-python/pip`

#### Pemasangan

Pasang antarmuka baris perintah QMK dengan menjalankan:

    python3 -m pip install --user qmk

#### Paket Komunitas

Paket paket berikut dipelihara oleh anggota komunitas. Jadi, sangat memungkinkan bila bukan merupakan versi paling mutakhir maupun sepenuhnya berfungsi. Bila anda mengalami masalah, mohon laporkan masalah tersebut kepada pemelihara masing-masing.

Pada distribusi yang berbasis Arch, anda dapat memasang antarmuka baris perintah dari lumbung resmi (CATATAN: saat penulisan, beberapa ketergantungan ditandai sebagai ketergantungan pilihan yang tidak seharusnya demikian):

    sudo pacman -S qmk

Anda juga dapat mencoba paket `qmk-git` dari AUR:

    yay -S qmk-git

###  ** FreeBSD **

#### Prasyarat

Anda harus memasang Git dan Python. Sangat memungkinkan bila kedua program tersebut telah terpasang pada komputer anda. Namun, bila keduanya belum terpasang, ikuti perintah berikut untuk melakukannya:

    pkg install git python3

Pastikan bahwa `$HOME/.local/bin` sudah dimasukkan ke `$PATH` sehingga paket Python yang terpasang secara lokal tersedia.

#### Pemasangan

Pasang antarmuka baris perintah QMK dengan menjalankan:

    python3 -m pip install --user qmk

<!-- tabs:end -->

## 3. Jalankan QMK Setup :id=set-up-qmk

<!-- tabs:start -->

### ** Windows **

Setelah memasang QMK, anda dapat mempersiapkannya dengan perintah ini:

    qmk setup

Pada kebanyakan situasi, adalah lebih baik bila anda menjawab `y` untuk semua pertanyaan.

### ** macOS **

Setelah memasang QMK, anda dapat mempersiapkannya dengan perintah ini:

    qmk setup

Pada kebanyakan situasi, adalah lebih baik bila anda menjawab `y` untuk semua pertanyaan.

### ** Linux/WSL **

Setelah memasang QMK, anda dapat mempersiapkannya dengan perintah ini:

    qmk setup

Pada kebanyakan situasi, adalah lebih baik bila anda menjawab `y` untuk semua pertanyaan.

?>**Catatan untuk Debian, Ubuntu, dan turunannya**:
Bisa jadi anda akan mendapatkan pesan galat semacam berikut: `bash: qmk: command not found`.
Hal ini disebabkan oleh sebuah [kutu](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=839155) yang didatangkan oleh Debian pada rilis Bash 4.4 mereka. Pada rilis tersebut, `$HOME/.local/bin` tidak termasuk pada PATH. Kutu ini sudah ditepok pada Debian dan Ubuntu.
Sayangnya, Ubuntu mendatangkan kembali kutu ini dan belum [menepuknya kembali](https://bugs.launchpad.net/ubuntu/+source/bash/+bug/1588562).
Untungnya, menepuk kutu ini mudah. Jalankan perintah berikut sebagai pengguna anda: `echo 'PATH="$HOME/.local/bin:$PATH"' >>  $HOME/.bashrc && source $HOME/.bashrc`

###  ** FreeBSD **

Setelah memasang QMK, anda dapat mempersiapkannya dengan perintah ini:

    qmk setup

Pada kebanyakan situasi, adalah lebih baik bila anda menjawab `y` untuk semua pertanyaan.

?>**Catatan pada FreeBSD**:
Sangat disarankan untuk menjalankan `qmk setup` sebagai pengguna non-`root` untuk memulai menggunakan QMK.
Hal ini juga akan mengidentifikasi berkas yang harus dipasang ke sistem anda menggunakan `pkg`. Namun, pemasangan akan gagal bila dijalankan sebagai pengguna tanpa privilese. Untuk memasang ketergantungan dasar secara manual, jalankan `./util/qmk_install.sh` sebagai `root` atau menggunakan `sudo`. Bila sudah selesai, jalankan ulang `qmk setup` untuk menyelesaikan pengaturan.

<!-- tabs:end -->

?> Direktori rumah qmk dapat ditentukan pada saat persiapan dengan `qmk setup -H <path>`. Bisa juga diubah menggunakan [konfigurasi antarmuka baris perintah](id/cli_configuration.md?id=single-key-example) dan juga variabel `user.qmk_home`. Untuk semua opsi yang ada, jalankan `qmk setup --help`.

?> Bila anda sudah tahu [cara menggunakan GitHub](id/getting_started_github.md), kami menyarankan agar anda membuat cabang anda sendiri dan menggunakan `qmk setup <github_username>/qmk_firmware` untuk menyalin cabang anda. Bila anda tidak paham maksud paragraf ini, anda dapat mengabaikannya.

## 4. Periksa Lingkungan Bangun Anda

Pada saat ini, lingkungan bangun QMK anda sudah siap. Anda dapat membangun sebuah perangkat tegar untuk papan ketik anda. Mulai dengan membangun tata letak bawaan untuk papan ketik tersebut. Seharusnya, anda dapat melakukannya dengan perintah pada format berikut:

    qmk compile -kb <papanketik> -km default

Sebagai conoth, untuk membangun perangkat tegar untuk Clueboard 66%, anda akan menggunakan:

    qmk compile -kb clueboard/66/rev3 -km default

Dan bila sudah selesai, anda akan melihat keluaran antarmuka baris perintah yang mirip seperti di bawah ini:

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

## 5. Konfigurasi Lingkungan Bangun Anda (Pilihan)

Anda dapat mengkonfigurasi lingkungan bangun anda dengan mengatur nilai-nilai bawaan sehingga penggunaan QMK menjadi tidak terlalu menjemukan.

Kebanyakan orang yang baru pertama kali menggunakan QMK cenderung hanya punya 1 papan ketik. Anda dapat mengatur papan ketik tersebut sebagai papan ketik bawaan dengan perintah `qmk config`. Sebagai contoh, untuk mengatur papan ketik bawaan anda menjadi `clueboard/66/rev4`, anda dapat memasukkan perintah berikut:

    qmk config user.keyboard=clueboard/66/rev4

Anda juga dapat mengatur nama tata letak papan tombol bawaan anda. Kebanyakan orang menggunakan nama pengguna GitHub mereka. Kami juga merekomendasikan hal yang sama.

    qmk config user.keymap=<nama_pengguna_github>

Setelah melakukan kedua hal tersebut, anda tinggal memasukkan perintah berikut:

    qmk compile

# Membuat Tata Letak Papan Ketik Anda

Sekarang anda siap untuk membuat tata letak papan ketik personal anda. Silakan buka [Membangun Perangkat Tegar Pertama Anda](id/newbs_building_firmware.md).
