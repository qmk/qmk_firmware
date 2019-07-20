# QMK Vagrant Utilities

## Dockerfile
Vagrant-friendly `qmkfm/base_container`.

In order for the Docker provider and `vagrant ssh` to function the container has a few extra requirements.

* vagrant user
* ssh server
  * configured with expected public key
* sudo
  * passwordless for vagrant user
