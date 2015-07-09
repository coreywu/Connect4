all: 
	gcc -o output.exe connect4.c

test:
	gcc -o test_output.exe connect4_tests.c
	./test_output.exe

clean:
	rm *.exe *.exe.stackdump
