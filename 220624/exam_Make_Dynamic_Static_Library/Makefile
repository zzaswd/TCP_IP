TARGET = op_normal op_static op_dynamic
OBJS_N = main.o calculate.o error_handling.o
OBJS_S = calculate.o error_handling.o
OBJS_D = calculate_d.o error_handling_d.o
cc = gcc

CFLAGS = -g
LFLAGS = -L./
IFLAGS = -I./

all : $(TARGET)

op_normal : $(OBJS_N) input.o
	$(cc) $(CFLAGS) -o $@ $(OBJS_N) $(IFLAGS)
	$(cc) $(CFLAGS) -o input input.o
op_static : $(OBJS_S) main.o
	ar rscv libksh.a $(OBJS_S) 
	$(cc) $(CFLAGS) -o $@ main.o $(LFLAGS) -lksh $(IFLAGS)

op_dynamic : $(OBJS_D) main.o
	$(cc) -shared -o libksh.so $(OBJS_D)
	$(cc) $(CFLAGS) -o $@ main.o $(LFLAGS) -lksh $(IFLAGS)

calculate.o : calculate.c
	$(cc) $(CFLAGS) -c calculate.c

error_handling.o : error_handling.c
	$(cc) $(CFLAGS) -c error_handling.c


calculate_d.o : calculate.c
	$(cc) -fPIC $(CFLAGS) -c -o calculate_d.o calculate.c

error_handling_d.o : error_handling.c
	$(cc) -fPIC $(CFLAGS) -c -o error_handling_d.o error_handling.c


main.o : main.c
	$(cc) -g -c main.c
input.o : input.c
	$(cc) -g -c input.c

clean:
	rm -r *.o $(TARGET) *.so *.a input
	
