FROM qmkfm/base_container

VOLUME /qmk_firmware
WORKDIR /qmk_firmware
COPY . .

CMD make all:default
