all: *.cpp
	g++ *.cpp -g -o Zork

test: all
	./Zork samples/sample.txt.xml

clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda
	/bin/rm -f *.gcno
	/bin/rm -f *.gcov
	/bin/rm -f a.out
	/bin/rm -f Zork
