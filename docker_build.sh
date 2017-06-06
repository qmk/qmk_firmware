#docker run -e keymap=ijikeman-osx -e subproject=ez -e keyboard=ergodox --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware make TAP_DANCE_ENABLE=yes
docker run -e keyboard=ergodox -e subproject=ez -e keymap=ijikeman-osx --rm -v $('pwd'):/qmk:rw jackhumbert/qmk_firmware make TAP_DANCE_ENABLE=yes
