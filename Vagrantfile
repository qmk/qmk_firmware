# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
  # define a name instead of just 'default'
  config.vm.define "qmk_firmware"

  # VMware/Virtualbox ( and also Hyperv/Parallels) 64 bit
  config.vm.box = "bento/ubuntu-16.04"

  # This section allows you to customize the Virtualbox VM
  # settings, ie showing the GUI or upping the memory
  # or cores if desired
  config.vm.provider "virtualbox" do |vb|
    # Hide the VirtualBox GUI when booting the machine
    vb.gui = false
    # Uncomment the below lines if you want to program
    # your Teensy via the VM rather than your host OS
    #vb.customize ['modifyvm', :id, '--usb', 'on']
    #vb.customize ['usbfilter', 'add', '0',
    #         '--target', :id,
    #         '--name', 'teensy',
    #         '--vendorid', '0x16c0',
    #         '--productid','0x0478'
    #        ]
    # Customize the amount of memory on the VM:
    vb.memory = "512"
    # Uncomment the below lines if you have time sync
    # issues with make and incremental builds
    #vb.customize [ "guestproperty", "set", :id, "/VirtualBox/GuestAdd/VBoxService/--timesync-set-threshold", 1000 ]
  end

  # This section allows you to customize the VMware VM
  # settings, ie showing the GUI or upping the memory
  # or cores if desired
  config.vm.provider "vmware_workstation" do |vmw|
    # Hide the VMware GUI when booting the machine
    vmw.gui = false

    # Customize the amount of memory on the VM:
    vmw.memory = "512"
  end

  config.vm.provider "vmware_fusion" do |vmf|
    # Hide the vmfare GUI when booting the machine
    vmf.gui = false

    # Customize the amount of memory on the VM:
    vmf.memory = "512"
  end

  # Docker provider pulls from hub.docker.com respecting docker.image if
  # config.vm.box is nil. Note that this bind-mounts from the current dir to
  # /vagrant in the guest, so unless your UID is 1000 to match vagrant in the
  # image, you'll need to: chmod -R a+rw .
  config.vm.provider "docker" do |docker, override|
    override.vm.box = nil
    docker.image = "jesselang/debian-vagrant:jessie"
    docker.has_ssh = true
  end

  # This script ensures the required packages for AVR programming are installed
  # It also ensures the system always gets the latest updates when powered on
  # If this causes issues you can run a 'vagrant destroy' and then
  # add a # before ,run: (or change "always" to "once") and run 'vagrant up' to get a working
  # non-updated box and then attempt to troubleshoot or open a Github issue
  config.vm.provision "shell", inline: "/bin/sh -c 'yes | /vagrant/util/qmk_install.sh'", run: "always"

  config.vm.post_up_message = <<-EOT

  Log into the VM using 'vagrant ssh'. QMK directory synchronized with host is
  located at /vagrant
  To compile the .hex files use make command inside this directory, e.g.
     cd /vagrant
     make <keyboard>:default

  Examples:
     make planck/rev4:default:dfu
     make planck:default

  EOT
end
