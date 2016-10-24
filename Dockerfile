FROM debian:jessie
MAINTAINER Erik Dasque <erik@frenchguys.com>

RUN apt-get update
RUN apt-get install --no-install-recommends -y build-essential \
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
    git

RUN apt-get clean
RUN rm -rf /var/lib/apt/lists/*

ENV keyboard=ergodox
ENV subproject=ez
ENV keymap=default

VOLUME /qmk
WORKDIR /qmk
CMD make clean ; make keyboard=${keyboard} subproject=${subproject} keymap=${keymap}
