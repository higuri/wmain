# GNU makefile for wmain

CC = gcc
CFLAGS = -std=gnu99 -Werror -Wall
#CFLAGS = -std=gnu99 -Werror -Wall -Wextra

TARGET = wmain.out
OBJS = main.o wmain.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) *.o
	$(RM) $(TARGET)

###

# SAMPLE_TEXT
SAMPLE_TEXT = Hello Olá 您好 こんにちは привет "Hello World"

# LC_UTF8 
#   Specify a valid locale ID that can handle utf-8.
#   Because this file is encoded with utf-8,
#   $(SAMPLE_TEXT) is passed in the form of utf-8.
LC_UTF8 = en_US.UTF-8
#LC_UTF8 = C.UTF-8

run_test: $(TARGET)
	./$(TARGET) -L $(LC_UTF8) $(SAMPLE_TEXT)
