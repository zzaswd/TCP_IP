OBJS = main.o print.o input.o
TARGET = test
cc = gcc
CFLAGS = -g
LDFLAGS = -lmade_lib

$(TARGET) : $(OBJS)
	$(cc) -o $@ $^ $(CFLAGS) -L. $(LDFLAGS)
.c.o:
	$(cc) -c -o $@ $<

clean :
	rm -f *.o test

