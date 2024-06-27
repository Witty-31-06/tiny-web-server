CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Werror -fsanitize=address -fdiagnostics-color -std=c99
TARGET = nslookup_clone

all: $(TARGET)

$(TARGET): nslookup_clone.c
	$(CC) $(CFLAGS) -o $(TARGET) nslookup_clone.c

clean:
	rm -f $(TARGET)
