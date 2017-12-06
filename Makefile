# The compiler: gcc for C program, define as g++ for C++
CC = gcc

# Compiler flags:
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall

# The build target executable:
TARGET = mypass
TESTS = mypass_tests

all: $(TARGET)

test: $(TESTS)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

$(TEST): $(TEST).c
	$(CC) $(CFLAGS) -o $(TEST) $(TEST).c

clean:
	$(RM) $(TARGET)
	$(RM) $(TESTS)
	$(RM) .data.mypass
	$(RM) .enc_data.mypass