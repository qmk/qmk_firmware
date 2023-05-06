sudo ./hid_listen | egrep --line-buffered "(0x[A-F0-9]+,)?(NA|[0-9]+),(NA|[0-9]+),[0-9]{1,2}" | tee -a keylog.csv
