# GNU makefile for wmain

CC = gcc
CFLAGS = -std=c99 -Werror -Wall
#CFLAGS = -std=c99 -Werror -Wall -Wextra

TARGET = main.out

OBJS=

all: $(TARGET)

$(TARGET): $(OBJS) main.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

###

SAMPLE = Hello Olá 您好 こんにちは привет "Hello World"
LC_UTF8=C.UTF-8
#LC_UTF8=en_US.UTF-8
run: $(TARGET)
	LC_ALL=$(LC_UTF8) ./$(TARGET) $(SAMPLE)

clean:
	$(RM) *.o
	$(RM) $(TARGET)
