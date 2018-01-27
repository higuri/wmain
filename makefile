# GNU makefile for C

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

clean:
	$(RM) *.o
	$(RM) $(TARGET)

SAMPLE = Hello Olá 您好 こんにちは привет "Hello World"
run: $(TARGET)
	./$(TARGET) $(SAMPLE)
