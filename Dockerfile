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
    gcc-avr \
    git \
    libnewlib-arm-none-eabi \
    software-properties-common \
    unzip \
    wget \
    zip \
    && rm -rf /var/lib/apt/lists/*

# upgrade gcc-arm-none-eabi from the default 5.4.1 to 6.3.1 due to ARM runtime issues
RUN wget -q https://developer.arm.com/-/media/Files/downloads/gnu-rm/6-2017q2/gcc-arm-none-eabi-6-2017-q2-update-linux.tar.bz2 -O - | \
    tar xj --strip-components=1 -C /

VOLUME /qmk_firmware
WORKDIR /qmk_firmware
COPY . .

CMD make all:default
