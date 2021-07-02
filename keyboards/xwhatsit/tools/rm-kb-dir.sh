
CUR_DIR=$(basename $PWD)

CONTROL_TYPE="displaywriter"
LAST_DIR="xwhatsit"

for KB in $(ls -l | grep -v .sh | awk '{print $9}')
do
  echo $KB

  mv $KB/$LAST_DIR/* $KB

  sed -i 's/..\/..\/..\/post_config.h/keyboards\/xwhatsit\/post_config.h/g' $KB/config.h 

  mv $KB/$LAST_DIR.c $KB/$KB.c 
  mv $KB/$LAST_DIR.h $KB/$KB.h
  sed -i "s/$LAST_DIR.h/$KB.h/g" $KB/$KB.c

  sed -i "s/$CUR_DIR\/$KB\/$LAST_DIR/$CONTROL_TYPE\/$CUR_DIR\/$KB/g" $KB/readme.md
 
  rmdir $KB/$LAST_DIR
done
