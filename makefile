all: 
	gcc -o output.exe play.c

test:
	gcc -o test_output.exe connect4_tests.c
	./test_output.exe

clean:
	rm -f *.exe *.exe.stackdump
