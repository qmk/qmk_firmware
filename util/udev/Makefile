# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -Wextra -Wpedantic -std=c11

# the build target executable:
TARGET = qmk_id
TARGET_TEST = qmk_id_test

all: $(TARGET)

test: $(TARGET_TEST)
	./$(TARGET_TEST)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)

.PHONY: all clean test
