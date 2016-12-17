# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
  # You can only have one config.vm.box uncommented at a time

  # Comment this and uncomment another if you don't want to use the minimal Arch box
  #config.vm.box = "dragon788/arch-ala-elasticdog"

  # VMware/Virtualbox 64 bit
  config.vm.box = "phusion/ubuntu-14.04-amd64"
  #
  # VMware/Virtualbox 64 bit
  #config.vm.box = "puphpet/centos65-x64"
  #
  # The opensuse boxes don't have dfu-util in their default repositories
  #
  # The virtualbox version has tools issues
  # VMware/Virtualbox 64 bit
  #config.vm.box = "bento/opensuse-13.2-x86_64"
  #
  # Virtualbox only
  #config.vm.box = "bento/opensuse-13.2-i386"
  # config.vm.box = ""
  # config.vm.box = ""

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
    #    	  '--target', :id,
    #    	  '--name', 'teensy',
    #    	  '--vendorid', '0x16c0',
    #    	  '--productid','0x0478'
    #		 ]
    # Customize the amount of memory on the VM:
    vb.memory = "512"
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
  # add a # before ,args: and run 'vagrant up' to get a working
  # non-updated box and then attempt to troubleshoot or open a Github issue

  config.vm.provision "shell", run: "always", path: "./util/install_dependencies.sh", args: "-update"

  config.vm.post_up_message = <<-EOT
  Log into the VM using 'vagrant ssh' on OSX or from Git Bash (Win)
  or 'vagrant ssh-config' and Putty or Bitvise SSH or another SSH tool

  Change directory (cd) to the keyboard you wish to program
  (Optionally) modify your layout,
  then run 'make clean'
  and then 'make' to compile the .eep and .hex files.

  Or you can copy and paste the example line below.

  cd /vagrant; cd keyboards; cd ergodox; make clean; make


  EOT
end
