#!/bin/sh

version=0_5_2

for keyboard in ble_micro_pro kugel
    do
        make $keyboard:default:uf2 -j8
        make $keyboard:default:zip -j8
        make $keyboard:no_msc:zip -j8
        mv ${keyboard}_default.uf2 ${keyboard}_default_${version}.uf2
        mv ${keyboard}_default.zip ${keyboard}_default_${version}.zip
        mv ${keyboard}_no_msc.zip ${keyboard}_no_msc_${version}.zip
        unzip -o ${keyboard}_default_${version}.zip
        mv ${keyboard}_default.bin ${keyboard}_default_${version}.bin
        mv ${keyboard}_default.dat ${keyboard}_default_${version}.dat
        unzip -o ${keyboard}_no_msc_${version}.zip
        mv ${keyboard}_no_msc.bin ${keyboard}_no_msc_${version}.bin
        mv ${keyboard}_no_msc.dat ${keyboard}_no_msc_${version}.dat
    done

