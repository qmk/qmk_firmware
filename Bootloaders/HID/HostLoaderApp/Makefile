OS ?= LINUX
#OS ?= WINDOWS
#OS ?= MACOSX
#OS ?= BSD

ifeq ($(OS), LINUX)  # also works on FreeBSD
CC ?= gcc
CFLAGS ?= -O2 -Wall
teensy_loader_cli: teensy_loader_cli.c
	$(CC) $(CFLAGS) -s -DUSE_LIBUSB -o teensy_loader_cli teensy_loader_cli.c -lusb


else ifeq ($(OS), WINDOWS)
CC = i586-mingw32msvc-gcc
CFLAGS ?= -O2 -Wall
teensy_loader_cli.exe: teensy_loader_cli.c
	$(CC) $(CFLAGS) -s -DUSE_WIN32 -o teensy_loader_cli.exe teensy_loader_cli.c -lhid -lsetupapi


else ifeq ($(OS), MACOSX)
CC ?= gcc
SDK ?= /Developer/SDKs/MacOSX10.5.sdk
CFLAGS ?= -O2 -Wall
teensy_loader_cli: teensy_loader_cli.c
	$(CC) $(CFLAGS) -DUSE_APPLE_IOKIT -isysroot $(SDK) -o teensy_loader_cli teensy_loader_cli.c -Wl,-syslibroot,$(SDK) -framework IOKit -framework CoreFoundation


else ifeq ($(OS), BSD)  # works on NetBSD and OpenBSD
CC ?= gcc
CFLAGS ?= -O2 -Wall
teensy_loader_cli: teensy_loader_cli.c
	$(CC) $(CFLAGS) -s -DUSE_UHID -o teensy_loader_cli teensy_loader_cli.c


endif


clean:
	rm -f teensy_loader_cli teensy_loader_cli.exe
