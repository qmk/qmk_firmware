SRC += kageurufu.c \
       process_records.c \
       custom_rgb.c

# Link time optimization, should save on firmware size
EXTRAFLAGS += -flto
