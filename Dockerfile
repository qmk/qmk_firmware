FROM debian:9

RUN apt-get update && apt-get install --no-install-recommends -y \
    avr-libc \
    avrdude \
    binutils-arm-none-eabi \
    binutils-avr \
    build-essential \
    dfu-programmer \
    dfu-util \
    gcc \
    gcc-arm-none-eabi \
    gcc-avr \
    git \
    libnewlib-arm-none-eabi \
    software-properties-common \
    unzip \
    wget \
    zip \
    && rm -rf /var/lib/apt/lists/*

ENV KEYBOARD=ergodox_ez
ENV KEYMAP=default

VOLUME /qmk_firmware
WORKDIR /qmk_firmware
COPY . .

CMD make $KEYBOARD:$KEYMAP
