p7.out : editor.o 	
	g++ -ansi -Wall -g -o p7.out editor.o
editor.o : editor.cpp
	g++ -ansi -Wall -g -c editor.cpp
clean : 
	rm -f p7.out editor.o
