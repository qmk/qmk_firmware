#!/bin/sh

make ble_micro_pro:default:uf2 -j8
make ble_micro_pro:default:zip -j8
make ble_micro_pro:no_msc:zip -j8
make kugel:default:uf2 -j8
make kugel:default:zip -j8

version=0_5_0

mv ble_micro_pro_default.uf2 ble_micro_pro_default_${version}.uf2
mv ble_micro_pro_default.zip ble_micro_pro_default_${version}.zip
mv ble_micro_pro_default.zip ble_micro_pro_no_msc_${version}.zip
mv kugel_default.uf2 kugel_default_${version}.uf2
mv kugel_default.zip kugel_default_${version}.zip


