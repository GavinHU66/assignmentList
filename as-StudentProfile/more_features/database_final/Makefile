database:database_main.o database.o database.h
	g++ database.o database_main.o -o database
database.o:database.cpp database.h
	g++ -c database.cpp 
database_main.o:database_main.cpp database.h
	g++ -c database_main.cpp
run:
	./database