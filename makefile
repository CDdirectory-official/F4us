CC = gcc
CFLAGS = -O3 -Wall -Wextra -pthread
TARGET = zerovoid

all:
	$(CC) $(CFLAGS) src/core/analyzer.c src/core/entropy.c src/sandbox/jail.c src/daemon/monitor.c src/daemon/soldier.c src/daemon/backit.c -o $(TARGET) -lm

clean:
	rm -f $(TARGET)
