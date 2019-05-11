RYS_STOKEN1 = "$(shell security find-generic-password -a qmk -s wt8a-1 -w)"
RYS_STOKEN2 = "$(shell security find-generic-password -a qmk -s wt8a-2 -w)"
RYS_STOKEN3 = "$(shell security find-generic-password -a qmk -s wt8a-3 -w)"
RYS_STOKEN4 = "$(shell security find-generic-password -a qmk -s wt8a-4 -w)"

CFLAGS += -DRYS_STOKEN1=\"$(RYS_STOKEN1)\"
CFLAGS += -DRYS_STOKEN2=\"$(RYS_STOKEN2)\"
CFLAGS += -DRYS_STOKEN3=\"$(RYS_STOKEN3)\"
CFLAGS += -DRYS_STOKEN4=\"$(RYS_STOKEN4)\"
