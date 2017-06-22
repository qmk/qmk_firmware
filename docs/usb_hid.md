# Getting Report Descriptor
```
  $ cd /sys/bus/usb/drivers/usbhid
  $ ls
  1-1.3.4:1.0  1-1.3.4:1.2  bind    new_id     uevent
  1-1.3.4:1.1  1-1.3.4:1.3  module  remove_id  unbind
  $ echo -n 1-1.4\:1.0 | sudo tee unbind
  $ sudo lsusb -vvv -d 046d:c01d
  $ echo -n 1-1.4\:1.0 | sudo tee bind
```

