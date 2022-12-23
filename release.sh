#!/bin/sh

version=0_11_3

for keyboard in ble_micro_pro kugel toybox/bmp crkbd_ecwl/bmp keyboard_quantizer/kqb
    do
        make $keyboard:default:uf2 -j8
        make $keyboard:default:zip -j8
        make $keyboard:no_msc:zip -j8
        keyboard=${keyboard//\//_}
        mv ${keyboard}_default.uf2 ${keyboard}_default_${version}.uf2
        mv ${keyboard}_default.zip ${keyboard}_default_${version}.zip
        mv ${keyboard}_no_msc.zip ${keyboard}_no_msc_${version}.zip
        unzip -o ${keyboard}_default_${version}.zip
        mv ${keyboard}_default.bin firmware/${keyboard}_default_${version}.bin
        mv ${keyboard}_default.dat firmware/${keyboard}_default_${version}.dat
        unzip -o ${keyboard}_no_msc_${version}.zip
        mv ${keyboard}_no_msc.bin firmware/${keyboard}_no_msc_${version}.bin
        mv ${keyboard}_no_msc.dat firmware/${keyboard}_no_msc_${version}.dat
    done

