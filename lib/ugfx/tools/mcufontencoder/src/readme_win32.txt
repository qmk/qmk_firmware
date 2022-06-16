How to build on Windows using Visual Studio 2015

* Download freetype-2.7 and extract to mcufont dir. result will contain freetype-2.7\src, freetype-2.7\include, etc.
* Go to freetype-2.7\builds\windows\vc2010 and open freetype.sln
* Select "Debug Multithreaded" and build. Select "Release Multithreaded" and build. Close Visual Studio.
* Open mcufont.sln
* Select Debug or Release, and build
* Resulting mcufont.exe is in Release\ or Debug\ folder and needs no further dependencies.

