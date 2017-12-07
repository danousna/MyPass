# The compiler: gcc for C program, define as g++ for C++
CC = gcc

# Compiler flags:
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall

# The build target executable:
TARGET = mypass
BUILD = build

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(BUILD)/$(TARGET) $(TARGET).c

clean:
	$(RM) $(BUILD)/$(TARGET)
	$(RM) $(BUILD)/.data.mypass
	$(RM) $(BUILD)/.enc_data.mypass
