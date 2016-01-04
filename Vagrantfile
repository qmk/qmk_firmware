# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
  config.vm.box = "dragon788/arch-ala-elasticdog"

  # This section allows you to customize the Virtualbox VM
  # settings, ie showing the GUI or upping the memory
  # or cores if desired
  config.vm.provider "virtualbox" do |vb|
    # Hide the VirtualBox GUI when booting the machine
    vb.gui = false
  
    # Customize the amount of memory on the VM:
    vb.memory = "512"
  end

  # This section allows you to customize the VMware VM
  # settings, ie showing the GUI or upping the memory
  # or cores if desired
  config.vm.provider "vmware" do |vmw|
    # Hide the VMware GUI when booting the machine
    vmw.gui = false
  
    # Customize the amount of memory on the VM:
    vmw.memory = "512"
  end

  # This ensures the system always gets the latest updates when powered on
  # If this causes issues you can run a 'vagrant destroy' and then
  # comment out these three lines and run 'vagrant up' to get a working
  # non-updated box and then attempt to troubleshoot after it has started
  #
  config.vm.provision "shell", run: "always", inline: <<-SHELL
    sudo pacman -Syu --needed --noconfirm
  SHELL
  
  # Allow user to speed up package installs using powerpill/wget tweaks
  # Always run the pacman mirror update script if possible when vagrant comes up
  # This will ensure that users never get stalled on a horribly slow mirror

  config.vm.provision "shell", path: "avr_setup.sh"

  config.vm.post_up_message = """Change directory to the keyboard you wish to program and modify your layout, then run 'make clean' and 'make' to compile the .eep and .hex files."""
end
