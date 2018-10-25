FROM debian

RUN apt-get update && apt-get install --no-install-recommends -y \
    build-essential \
    gcc \
    unzip \
    wget \
    zip \
    gcc-avr \
    binutils-avr \
    avr-libc \
    dfu-programmer \
    dfu-util \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    libnewlib-arm-none-eabi \
    git \
    software-properties-common \
    avrdude \
    && rm -rf /var/lib/apt/lists/*

ENV KEYBOARD=ergodox_ez
ENV KEYMAP=default

VOLUME /qmk_firmware
WORKDIR /qmk_firmware
COPY . .

CMD make $KEYBOARD:$KEYMAP
