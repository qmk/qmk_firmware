export SKIP_VERSION=yes
export SKIP_DEBUG_INFO=yes

function rename_hex() {
	 sed -e 's/helix_pico_sc_back/helix_pico_split_common/' \
	  -e 's/helix_rev2_oled_back/helix_rev2_back/' \
	   -e 's/helix_rev2_oled_under/helix_rev2_under/' \
	    -e 's/helix_rev2_oled/helix_rev2/' \
	     -e 's/helix_rev2_sc_oledback/helix_rev2_split_common/'
}

OLD_NAMES="helix/rev1
 helix/pico
 helix/pico/back
 helix/pico/under
 helix/pico/sc/back
 helix/rev2/oled
 helix/rev2/oled/back
 helix/rev2/oled/under
 helix/rev2/sc/oledback"

NEW_NAMES="helix/rev1
 helix/pico
 helix/pico/back
 helix/pico/under
 helix/pico/split_common
 helix/rev2
 helix/rev2/back
 helix/rev2/under
 helix/rev2/split_common"

 # === build on master ===
git checkout `git merge-base master reduce_helix_build_variation`
git log -1 --oneline --decorate > /tmp/master_md5.txt
for i in $OLD_NAMES
do
    make $i:all:clean
    make $i:all
    md5 .build/*.hex | rename_hex >> /tmp/master_md5.txt
    make $i:all:clean
done

 # === build on reduce_helix_build_variation ===
git checkout reduce_helix_build_variation
git log -4 --oneline --decorate > /tmp/branch_md5.txt
for i in $NEW_NAMES
do
    make $i:all:clean
    make $i:all
    md5 .build/*.hex >> /tmp/branch_md5.txt
    make $i:all:clean
done

 # ===
diff -u /tmp/master_md5.txt /tmp/branch_md5.txt
