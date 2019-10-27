FROM qmkfm/base_container
//Dockerfile
VOLUME /qmk_firmware
WORKDIR /qmk_firmware
COPY . .
CMD make all:default
