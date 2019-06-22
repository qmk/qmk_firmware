SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
cd $SCRIPTPATH/../../lib/chibios
git apply $SCRIPTPATH/chibios_stm32l151.patch
