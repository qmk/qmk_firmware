#!/bin/sh

wget https://bootstrap.pypa.io/get-pip.py
python3 get-pip.py
python3 -m pip install qmk
rm get-pip.py

./.devcontainer/setup-userspace.sh

qmk setup -y
