@echo off
setx /M test test > nul 2>&1
if NOT ["%errorlevel%"]==["0"] (
	echo FAILED. Rerun with administrator privileges.
	pause
	exit
) 

mingw-get install mingw32-make-bin mingw32-gcc-bin msys-wget-bin msys-unzip-bin
cd \MinGW\bin

REM It would be somewhat better to use symlinks, but then it wouldn't work in XP or Vista.
copy mingw32-make.exe make.exe

mkdir temp
cd temp 
wget http://iweb.dl.sourceforge.net/project/dfu-programmer/dfu-programmer/0.7.2/dfu-programmer-win-0.7.2.zip
unzip dfu-programmer-win-0.7.2.zip
copy dfu-programmer.exe ..

wget http://iweb.dl.sourceforge.net/project/libusb-win32/libusb-win32-releases/1.2.6.0/libusb-win32-bin-1.2.6.0.zip
unzip libusb-win32-bin-1.2.6.0.zip
cp libusb-win32-bin-1.2.6.0\bin\x86\libusb0_x86.dll ../libusb0.dll

pnputil -i -a dfu-prog-usb-1.2.2\atmel_usb_dfu.inf

cd ..
rm -rf temp