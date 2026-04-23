OBJ := $(patsubst %.c, %.o, $(wildcard *.c))

a.out: $(OBJ)
	gcc -o $@ $^

%.o: %.c
	gcc -c $<

clean:
	rm -f *.o *.exe a.out