# encoder test on Helix/rev3_5rows:five_rows

## Detects sample leaks due to premature rotation of the encoder.

* `make USROPT=mdelay_type=no,mdelay=30,enc,enc-over helix/rev3_5rows:five_rows`
* `make USROPT=mdelay_type=no,mdelay=300,enc,enc-over helix/rev3_5rows:five_rows`
* `make USROPT=mdelay_type=no,mdelay=800,enc,enc-over helix/rev3_5rows:five_rows`
* `make USROPT=mdelay_type=no,mdelay=1000,enc,enc-over helix/rev3_5rows:five_rows`

## Detects sample leakage from the slave encoder.

* `make USROPT=mdelay_type=no,mdelay=30,enc,enc-slave helix/rev3_5rows:five_rows`
