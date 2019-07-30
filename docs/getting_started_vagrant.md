# Vagrant Quick Start

This project includes a `Vagrantfile` that will allow you to build a new firmware for your keyboard very easily without major changes to your primary operating system. This also ensures that when you clone the project and perform a build, you have the exact same environment as anyone else using the Vagrantfile to build. This makes it much easier for people to help you troubleshoot any issues you encounter.

## Requirements

Using the `Vagrantfile` in this repository requires you have [Vagrant](http://www.vagrantup.com/) as well as a supported provider installed:

* [VirtualBox](https://www.virtualbox.org/) (Version at least 5.0.12)
  * Sold as 'the most accessible platform to use Vagrant'
* [VMware Workstation](https://www.vmware.com/products/workstation) and [Vagrant VMware plugin](http://www.vagrantup.com/vmware)
  * The (paid) VMware plugin requires a licensed copy of VMware Workstation/Fusion
* [Docker](https://www.docker.com/)

Other than having Vagrant, a suitable provider installed and possibly a restart of your computer afterwards, you can simple run a 'vagrant up' anywhere inside the folder where you checked out this project and it will start an environment (either a virtual machine or container) that contains all the tools required to build this project. There is a post Vagrant startup hint that will get you off on the right foot, otherwise you can also reference the build documentation below.

## Flashing the Firmware

The "easy" way to flash the firmware is using a tool from your host OS:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox) (recommended)
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)
* [Atmel FLIP](http://www.atmel.com/tools/flip.aspx)

If you want to program via the command line you can uncomment the ['modifyvm'] lines in the Vagrantfile to enable the USB passthrough into Linux and then program using the command line tools like dfu-util/dfu-programmer or you can install the Teensy CLI version.

## Vagrantfile Overview
The development environment is configured to run the QMK Docker image, `qmkfm/base_container`. This not only ensures predictability between systems, it also mirrors the CI environment.

## FAQ

### Why am I seeing issues under Virtualbox?
Certain versions of Virtualbox 5 appear to have an incompatibility with the Virtualbox extensions installed in the boxes in this Vagrantfile. If you encounter any issues with the /vagrant mount not succeeding, please upgrade your version of Virtualbox to at least 5.0.12. **Alternately, you can try running the following command:**

```console
vagrant plugin install vagrant-vbguest
```

### How do I remove an existing environment?
Finished with your environment? From anywhere inside the folder where you checked out this project, Execute:

```console
vagrant destory
```

### What if I want to use Docker directly?
Want to benefit from the Vagrant workflow without a virtual machine? The Vagrantfile is configured to bypass running a virtual machine, and run the container directly. Execute the following when bringing up the environment to force the use of Docker:
```console
vagrant up --provider=docker
```

### How do I access the virtual machine instead of the Docker container?
Execute the following to bypass the `vagrant` user booting directly to the official qmk builder image:

```console
vagrant ssh -c 'sudo -i'
```