CC = g++

CFLAGS= -g -std=c++14 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlarger-than=8192 -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs
BuildF = obj/
all: main.exe


main.exe :   $(BuildF)main.o $(BuildF)akinator.o $(BuildF)stack.o $(BuildF)open.o $(BuildF)dump_graph.o $(BuildF)get_characterist.o
	$(CC) -g $(BuildF)main.o $(BuildF)akinator.o $(BuildF)stack.o $(BuildF)open.o $(BuildF)dump_graph.o $(BuildF)get_characterist.o -o main.exe

play.exe : $(BuildF)akinator.o

$(BuildF)main.o : main.cpp | obj
	$(CC) -c $(CFLAGS) $< -o $(BuildF)main.o

$(BuildF)akinator.o : akinator.cpp | obj
	$(CC) -c $(CFLAGS) akinator.cpp -o $(BuildF)akinator.o

$(BuildF)stack.o : stack.cpp | obj
	$(CC) -c $(CFLAGS) stack.cpp -o $(BuildF)stack.o

$(BuildF)open.o : open.cpp | obj
	$(CC) -c $(CFLAGS) open.cpp -o $(BuildF)open.o

$(BuildF)dump_graph.o: dump_graph.cpp
	$(CC) -c $(CFLAGS) dump_graph.cpp -o $(BuildF)dump_graph.o

$(BuildF)get_characterist.o: get_characterist.cpp
	$(CC) -c $(CFLAGS) get_characterist.cpp -o $(BuildF)get_characterist.o

obj:
	mkdir $@

clean:
	del /q /s obj