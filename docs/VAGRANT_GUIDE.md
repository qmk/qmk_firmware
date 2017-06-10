# Quick Start Directions

This project includes a Vagrantfile that will allow you to build a new firmware for your keyboard very easily without major changes to your primary operating system. This also ensures that when you clone the project and perform a build, you have the exact same environment as anyone else using the Vagrantfile to build. This makes it much easier for people to help you troubleshoot any issues you encounter.

## Requirements

Using the `/Vagrantfile` in this repository requires you have [Vagrant](http://www.vagrantup.com/) as well as [VirtualBox](https://www.virtualbox.org/) (or [VMware Workstation](https://www.vmware.com/products/workstation) and [Vagrant VMware plugin](http://www.vagrantup.com/vmware) but the (paid) VMware plugin requires a licensed copy of VMware Workstation/Fusion).

*COMPATIBILITY NOTICE* Certain versions of Virtualbox 5 appear to have an incompatibility with the Virtualbox extensions installed in the boxes in this Vagrantfile. If you encounter any issues with the /vagrant mount not succeeding, please upgrade your version of Virtualbox to at least 5.0.12. **Alternately, you can try running the following command:** `vagrant plugin install vagrant-vbguest`


Other than having Vagrant and Virtualbox installed and possibly a restart of your computer afterwards, you can simple run a 'vagrant up' anywhere inside the folder where you checked out this project and it will start a Linux virtual machine that contains all the tools required to build this project. There is a post Vagrant startup hint that will get you off on the right foot, otherwise you can also reference the build documentation below.

Build Firmware and Program Controller
-------------------------------------
See [build_guide.md](build_guide.md), or the readme in the particular keyboards/* folder.

Change your keymap
------------------
See [keymap.md](keymap.md).

## Flashing the firmware

The "easy" way to flash the firmware is using a tool from your host OS like the Teensy programming app. [ErgoDox EZ](/keyboards/ergodox/readme.md) gives a great example.

If you want to program via the command line you can uncomment the ['modifyvm'] lines in the Vagrantfile to enable the USB passthrough into Linux and then program using the command line tools like dfu-util/dfu-programmer or you can install the Teensy CLI version.
	
