# GNU makefile for wmain

CC = gcc
CFLAGS = -Werror -Wall
#CFLAGS = -Werror -Wall -Wextra

TARGET = main.out

OBJS=

all: $(TARGET)

$(TARGET): $(OBJS) main.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

###

SAMPLE = Hello Olá 您好 こんにちは привет "Hello World"
run: $(TARGET)
	LC_CTYPE=en_US.UTF-8 ./$(TARGET) $(SAMPLE)

clean:
	$(RM) *.o
	$(RM) $(TARGET)
