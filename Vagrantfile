# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
  # define a name instead of just 'default'
  config.vm.define "qmk_firmware"

  # VMware/Virtualbox ( and also Hyperv/Parallels) 64 bit
  config.vm.box = "generic/debian9"

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
  # config.vm.box is nil. In this case, we adhoc build util/vagrant/Dockerfile.
  # Note that this bind-mounts from the current dir to
  # /vagrant in the guest, so unless your UID is 1000 to match vagrant in the
  # image, you'll need to: chmod -R a+rw .
  config.vm.provider "docker" do |docker, override|
    override.vm.box = nil
    docker.build_dir = "util/vagrant"
    docker.has_ssh = true
  end

  # Unless we are running the docker container directly
  #   1. run container detached on vm
  #   2. attach on 'vagrant ssh'
  ["virtualbox", "vmware_workstation", "vmware_fusion"].each do |type|
    config.vm.provider type do |virt, override|
      override.vm.provision "docker" do |d|
        d.run "qmkfm/base_container",
          cmd: "tail -f /dev/null",
          args: "--privileged -v /dev:/dev -v '/vagrant:/vagrant'"
      end

      override.vm.provision "shell", inline: <<-SHELL
        echo 'docker restart qmkfm-base_container && exec docker exec -it qmkfm-base_container /bin/bash -l' >> ~vagrant/.bashrc
      SHELL
    end
  end

  config.vm.post_up_message = <<-EOT

  Log into the environment using 'vagrant ssh'. QMK directory synchronized with
  host is located at /vagrant
  To compile the .hex files use make command inside this directory, e.g.
     cd /vagrant
     make <keyboard>:default

  Examples:
     make planck/ez:default:flash
     make planck/ez:default

  EOT
end
