
CUR_DIR=$(basename $PWD)

CONTROL_TYPE="type_f"

#LAST_DIR="wcass"
#LAST_DIR="xwhatsit"
#LAST_DIR="wcass_locklights"
LAST_DIR="xwhatsit_locklights"

for KB in $(ls -l | grep -v .sh | awk '{print $9}')
do
  echo $KB

  #sed -i 's/brand_new_model_f/type_f\/model_f_labs/g' $KB/readme.md
 
  #sed -i 's/brand_new_model_f/type_f\/model_f_labs/g' $KB/rules.mk


  sed -i 's/..\/..\/..\/post_config.h/keyboards\/xwhatsit\/post_config.h/g' $KB/$LAST_DIR/config.h 

  sed -i 's/\/matrix.c/\/capsense_matrix.c/g' $KB/$LAST_DIR/rules.mk

  #sed -i "s/$CUR_DIR\/$KB\/$LAST_DIR/$CONTROL_TYPE\/$CUR_DIR\/$KB/\$LAST_DIR/g" $KB/$LAST/readme.md
  #sed -i "s/brand_new_model_f/$CONTROL_TYPE\/$CUR_DIR/g" $KB/$LAST_DIR/readme.md  
  #sed -i "s/$CUR_DIR/$CONTROL_TYPE\/$CUR_DIR/g" $KB/readme.md 
  sed -i "s/$CUR_DIR/$CONTROL_TYPE\/$CUR_DIR/g"  $KB/$LAST_DIR/readme.md

#make xwhatsit/ibm/f62/wcass:default

# make xwhatsit/ibm/fssk/wcass:default
 
done
