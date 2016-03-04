#Planck Advanced (but not too advanced) `cygwin` Users Guide
If you are a user of the [cygwin environment](https://cygwin.com) in Windows and want the freedom to use the latest tools available, then this is the guide for you. If compiling your own copy of the latest and greatest Gnu C Compiler makes you super happy, then this is the guide for you. If the command line make you smile, then this is the guide for you.


This guide was written step by step as I went through the process on a `Windows 10` `x86_64` based system.  This should be generally applicable to to any `Windows` environment with `cygwin`.


#####Do not skip steps. Do not move past a step until the previous step finishes successfully.



Based on [avr-libc installation guide](http://www.nongnu.org/avr-libc/user-manual/install_tools.html)


##Get the Required Packages
Download the `cygwin` setup ([x86_64](https://cygwin.com/setup-x86_64.exe)) and install the default system plus the following if they are not already selected:
- devel/gcc-core
- devel/gcc-g++
- devel/flex
- devel/git
- libs/libglib2.0_0
- libs/libgcc1
- interpreters/m4
- web/wget

The following sources will be required:
- [gmp](https://gmplib.org/) (6.1.0)
- [mpfr](http://www.mpfr.org/) (3.1.3)
- [mpc](http://www.multiprecision.org/) (1.0.3) 
- [binutils](https://www.sourceware.org/binutils/) (2.26)
- [gcc](https://gcc.gnu.org/) (5.3.0)
- [avr-libc](http://www.nongnu.org/avr-libc/) (2.0.0)

The `dfu-programmer` will be required to flash the new firmware 
- [dfu-programmer](https://dfu-programmer.github.io/) (0.7.2)


The set of commands below will create a directory (`~/local/avr`) for the sources you compile to be installed on the machine and a directory (`~/src`) for these source files to be stored. The commands then download the sources of the needed packages and unpack them. Note: the expand commands are different depending on if the packages are offered as a `bz2` or `gz` archive

```
$ mkdir ~/local/avr
$ mkdir ~/src
$ cd ~/src
$ wget https://gmplib.org/download/gmp/gmp-6.1.0.tar.bz2
$ wget http://www.mpfr.org/mpfr-current/mpfr-3.1.3.tar.bz2
$ wget ftp://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz
$ wget http://ftp.gnu.org/gnu/binutils/binutils-2.26.tar.gz
$ wget http://mirror0.babylon.network/gcc/releases/gcc-5.3.0/gcc-5.3.0.tar.gz
$ wget http://download.savannah.gnu.org/releases/avr-libc/avr-libc-2.0.0.tar.bz2
$ tar -xjf gmp-6.1.0.tar.bz2
$ tar -xjf mpfr-3.1.3.tar.bz2
$ tar -zxf mpc-1.0.3.tar.gz
$ tar -zxf binutils-2.26.tar.gz
$ tar -zxf gcc-5.3.0.tar.gz
$ tar -xjf avr-libc-2.0.0.tar.bz2 
```

##Setup the Build Environment
These commands will set up the install directory and the `PATH` variable, which will allow you to access your installed packages.  Note: if you close the `cygwin` terminal window, you will need to rerun these commands, they are not permanent.
```
$ PREFIX=$HOME/local/avr
$ export PREFIX
$ PATH=/usr/local/bin:/usr/local/lib:/usr/local/include:/bin:/lib:/cygdrive/c/WINDOWS/system32:/cygdrive/c/WINDOWS
$ PATH=$PATH:$PREFIX/bin
$ export PATH
```

##The `gcc` Required Math Library Packages
The following packages are required to be complied and installed in order to compile `gcc`.  They are not available through the `cygwin` package system, so we have to make them ourselves.  They must be complied in this order because each one depends on the previous.

###Build and Install `gmp`
```
$ cd ~/src/gmp-6.1.0
$ ./configure --enable-static --disable-shared
$ make
$ make check
$ make install
```

###Build and Install `mpfr`
```
$ cd ~/src/mpfr-3.1.3
$ ./configure --with-gmp-build=../gmp-6.1.0 --enable-static --disable-shared
$ make
$ make check
$ make install
```

###Build and Install `mpc`
```
$ cd ~/src/mpc-1.0.3
$ ./configure --with-gmp=/usr/local --with-mpfr=/usr/local --enable-static --disable-shared
$ make
$ make check
$ make install
```

##OPTIONAL Part
You can build and install a brand new `gcc` or you can use the one supplied by `cygwin`.  This will take about 4-5 hours to compile (It is a "native build", so it does the entire build **3 times**. This takes a long while). I would skip it.
###Build and Install `gcc` on your Machine  
```
$ cd ~/src/gcc-5.3.0
$ mkdir obj-local
$ cd obj-local
$ ../configure --enable-languages=c,c++ --with-gmp=/usr/local --with-mpfr=/usr/local --with-mpc=/usr/local --enable-static --disable-shared
$ make
$ make install
```

###Build and Install `binutils` on your Machine
```
$ cd ~/src/binutils-2.26
$ mkdir obj-local
$ cd obj-local
$ ../configure
$ make
$ make install
```
##End OPTIONAL Part

##Buliding `binutils`, `gcc`, and `avr-libc` for the AVR system
Now we can make the critical stuff for compiling our firmware: `binutils`, `gcc`, and `avr-libc` for the AVR architecture.  These allow us to build and manipulate the firmware for the keyboard.

###Build `binutils` for AVR
```
$ cd ~/src/binutils-2.26
$ mkdir obj-avr
$ cd obj-avr
$ ../configure --prefix=$PREFIX --target=avr --disable-nls
$ make
$ make install
```

###Build `gcc` for AVR
```
$ cd ~/src/gcc-5.3.0
$ mkdir obj-avr
$ cd obj-avr
$ ../configure --prefix=$PREFIX --target=avr --enable-languages=c,c++ --with-gmp=/usr/local --with-mpfr=/usr/local --with-mpc=/usr/local --enable-static --disable-shared --disable-nls --disable-libssp --with-dwarf2
$ make
$ make install
```

For building the `avr-libc`, we have to specify the host build system.  in my case it is `x86_64-unknown-cygwin`. You can look for build system type in the `gcc` configure notes for the proper `--build` specification to pass when you configure `avr-libc`.

###Build `avr-libc` for AVR
```
$ cd ~/src/avr-libc-2.0.0
$ ./configure --prefix=$PREFIX --build=x86_64-unknown-cygwin --host=avr
$ make
$ make install
```

##Install `dfu-programmer`
To install the `dfu-programmer`, we must get if from [their website](https://dfu-programmer.github.io/) (no fancy command line tricks here, but [this](http://iweb.dl.sourceforge.net/project/dfu-programmer/dfu-programmer/0.7.2/dfu-programmer-win-0.7.2.zip) might work).
Copy this file into your `cygwin` home directory.  (For me, it is `C:\cygwin64\home\Kevin`), extract the files, move `dfu-programmer.exe` to `~/local/avr/bin`. Most obnoxiously, the `libusb0_x86.dll` and `libusb0.sys` need to be moved from  `dfu/dfu-prog-usb-1.2.2/x86/` to a directory in the `Windows` `PATH` and the `cygwin` `PATH`. I achieved this by moving the files with Windows Explorer (you know, click and drag...) to  `C:\cygwin64\home\Kevin\local\avr\bin` Then, in a `WINDOWS` command prompt running:
```
C:\> set PATH=%PATH%;C:\cygwin64\home\Kevin\local\avr\bin
```
Adjust your path (for username) as needed. Also, `libusb0_x86.dll` needs to be renamed to `libusb0.dll`.  Why must this be so hard? You can tell that you were successful this way:
```
$ which dfu-programmer
/home/Kevin/local/avr/bin/dfu-programmer

$ dfu-programmer
dfu-programmer 0.7.2
https://github.com/dfu-programmer/dfu-programmer
Type 'dfu-programmer --help'    for a list of commands
     'dfu-programmer --targets' to list supported target devices
```
If you are not getting the above result, you will not be able to flash the firmware! 
- Try making sure your `PATH` variables are set correctly for both `Windows` and `cygwin`. 
- Do not extract it with `cygwin`'s `unzip` as it does not set the executable permissions correctly. If you did it anyway, do `chmod 755 dfu-programmer.exe`

####Install the USB drivers
These drivers are included in the `dfu-programmer` 0.7.2 (but you can get newer ones [here](http://iweb.dl.sourceforge.net/project/libusb-win32/libusb-win32-releases/1.2.6.0/libusb-win32-bin-1.2.6.0.zip)) and allow the `dfu-programmer` to program the firmware. From an **administrator-privileged** `Windows` terminal, run the following command (adjust the path as necessary) and accept the prompt that pops up:
```
C:\> pnputil -i -a C:\cygwin64\home\Kevin\dfu-prog-usb-1.2.2\atmel_usb_dfu.inf
```
This should be the result:
```
Microsoft PnP Utility

Processing inf :            atmel_usb_dfu.inf
Successfully installed the driver on a device on the system.
Driver package added successfully.
Published name :            oem104.inf


Total attempted:              1
Number successfully imported: 1
```

##Building and Flashing the Planck firmware!

If you did everything else right. This part should be a snap! Grab the latest sources from `github`, make the Plank firmware, then flash it.

###Build Planck and Load the Firmware
```
$ cd ~/src
$ git clone https://github.com/jackhumbert/qmk_firmware.git
$ cd qmk_firmware/keyboard/planck
$ make
```
Make sure there are no errors.  You should end up with this or something similar:

```
Creating load file for Flash: planck.hex
avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature planck.elf planck.hex

Creating load file for EEPROM: planck.eep
avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" \
--change-section-lma .eeprom=0 --no-change-warnings -O ihex planck.elf planck.eep || exit 0

Creating Extended Listing: planck.lss
avr-objdump -h -S -z planck.elf > planck.lss

Creating Symbol Table: planck.sym
avr-nm -n planck.elf > planck.sym

Size after:
   text    data     bss     dec     hex filename
  18602      82     155   18839    4997 planck.elf

-------- end --------
```

If you do not get the above, you **did not** build the firmware, and you will have nothing to flash.  If you have the fresh clone from github, it was probably something gone wrong in this install process, go check and see what didn't work and threw errors or what steps you might have missed.

But if everything went OK, you are ready to flash! Press the reset button on the bottom of the Planck, wait two seconds, then:
```
$ make dfu
```
.
.
.
profit!!!
