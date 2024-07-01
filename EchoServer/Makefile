CC = gcc
CFLAGS = -Wall -Werror -fsanitize=address -fdiagnostics-color=auto

# Server sources and objects
SERVER_SRCS = server.c open_listenfd.c RIO.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

# Client sources and objects
CLIENT_SRCS = client.c open_clientfd.c RIO.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

# Common headers
HEADERS = ioheader.h

# Targets
all: server client

server: $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o server $(SERVER_OBJS)

client: $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o client $(CLIENT_OBJS)

# Compilation rules
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

# Clean
clean:
	rm -f server client $(SERVER_OBJS) $(CLIENT_OBJS)
