# GNU makefile for wmain

CC = gcc
CFLAGS = -std=gnu99 -Werror -Wall
#CFLAGS = -std=gnu99 -Werror -Wall -Wextra

TARGET = main.out
OBJS=

all: $(TARGET)

$(TARGET): $(OBJS) main.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

###

SAMPLE = Hello Olá 您好 こんにちは привет "Hello World"
# LC_UTF8 
#   Specify locale ID that can handle utf-8.
#   This file is encoded with utf-8,
#   so $(SAMPLE) is passed in the form of it.
LC_UTF8 = en_US.UTF-8
#LC_UTF8 = C.UTF-8
run_test: $(TARGET)
	./$(TARGET) -L $(LC_UTF8) $(SAMPLE)

clean:
	$(RM) *.o
	$(RM) $(TARGET)
