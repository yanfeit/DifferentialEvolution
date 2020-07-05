CC=gcc-9
# CFLAGS = -Wall -g
# LIBS=-lm
INC=-I../../
target = test
obj = test_de_convergence_seed.o de_test_func.o de.o mtwister.o

$(target) : $(obj)
	$(CC) $(obj) -o $(target)

test_de_convergence_seed.o : test_de_convergence_seed.c
	$(CC) $(INC) -c $< -o $@

%.o : ../../%.c
	$(CC) $(INC) -c $< -o $@

.PHONY : clean
clean:
	rm -rf $(obj) $(target)