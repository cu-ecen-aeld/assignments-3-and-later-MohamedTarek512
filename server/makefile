CC = aarch64-none-linux-gnu-gcc
CFLAGS = -Wall -Werror
TARGET = aesdsocket
SRCS = aesdsocket.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)


