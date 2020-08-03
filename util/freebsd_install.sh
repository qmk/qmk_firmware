#!/bin/sh
packages=$(cat <<EOF
	git \
	wget \
	gmake \
	gcc \
	zip \
	unzip \
	avr-binutils \
	avr-gcc \
	avr-libc \
	dfu-programmer \
	dfu-util \
	avrdude \
	arm-none-eabi-gcc \
	arm-none-eabi-binutils \
	arm-none-eabi-newlib \
	diffutils \
	python3
EOF
)
util_dir=$(dirname "$0")
if [ $(id -u) = 0 ]; then
	pkg update
	pkg install -y ${packages}
	echo ""
	echo "Re-run the setup as your normal user to install the qmk python dependencies"
	exit 1
else
	if command -v sudo > /dev/null 2>&1; then
		sudo pkg update
		sudo pkg install -y ${packages}
	else
		echo "Make sure you run setup as root first to install base OS dependencies..."
		echo ""
	fi

	python3 -m pip install --user -r ${util_dir}/../requirements.txt
fi
