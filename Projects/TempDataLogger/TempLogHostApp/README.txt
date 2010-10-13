This library has been tested on Windows Vista 32bit, Windows Vista 64bit,
Windows XP 32bit and Debian (Lenny) AMD64 but should work on any version of
Windows that can run the .NET framework 2.0 and any other operating system
that has both hiddev and Mono.

Any additions must be tested and work on Windows and Linux, on both 32 and
64 bit. Windows 64 bit testing is particularly important as it is often
neglected.


Hid.Linux.dll was compiled under Linux with Mono (mcs) and uses no generics.

Hid.Win32.dll and Hid.Net.dll were compiled under Windows with the .NET
Framework v2.0.50727 but are also tested to compile with Mono (gmcs).


A good starting point when using this library is Hid.DeviceFactory's Enumerate
methods.

LogitechMX5000.cs is a simple example of how the library can be used. Other
examples on common devices are welcomed.

