CC = g++

CFLAGS= -g -std=c++14 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlarger-than=8192 -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs
BuildF = obj/
all: play.exe find_object.exe compare_objects.exe

play.exe :	 $(BuildF)play.o $(BuildF)akinator.o $(BuildF)stack.o $(BuildF)open.o $(BuildF)save_graph.o $(BuildF)default_values.o 
	$(CC) -g $(BuildF)play.o $(BuildF)akinator.o $(BuildF)stack.o $(BuildF)open.o $(BuildF)save_graph.o $(BuildF)default_values.o -o play.exe

find_object.exe : $(BuildF)find_object.o $(BuildF)akinator.o $(BuildF)stack.o $(BuildF)open.o $(BuildF)save_graph.o $(BuildF)get_characterist.o $(BuildF)default_values.o 
	$(CC) -g      $(BuildF)find_object.o $(BuildF)akinator.o $(BuildF)stack.o $(BuildF)open.o $(BuildF)save_graph.o $(BuildF)get_characterist.o $(BuildF)default_values.o -o find_object.exe

compare_objects.exe : $(BuildF)compare_objects.o $(BuildF)akinator.o $(BuildF)stack.o $(BuildF)open.o $(BuildF)save_graph.o $(BuildF)get_characterist.o $(BuildF)default_values.o 
	$(CC) -g      	  $(BuildF)compare_objects.o $(BuildF)akinator.o $(BuildF)stack.o $(BuildF)open.o $(BuildF)save_graph.o $(BuildF)get_characterist.o $(BuildF)default_values.o -o compare_objects.exe

$(BuildF)compare_objects.o : compare_objects.cpp | obj
	$(CC) -c $(CFLAGS) compare_objects.cpp -o $(BuildF)compare_objects.o

$(BuildF)find_object.o: find_object.cpp | obj
	$(CC) -c $(CFLAGS) find_object.cpp -o $(BuildF)find_object.o

$(BuildF)default_values.o: default_values.cpp | obj
	$(CC) -c $(CFLAGS) default_values.cpp -o $(BuildF)default_values.o

$(BuildF)play.o: play.cpp | obj
	$(CC) -c $(CFLAGS) play.cpp -o $(BuildF)play.o

$(BuildF)akinator.o : akinator.cpp | obj
	$(CC) -c $(CFLAGS) akinator.cpp -o $(BuildF)akinator.o

$(BuildF)stack.o : stack.cpp | obj
	$(CC) -c $(CFLAGS) stack.cpp -o $(BuildF)stack.o

$(BuildF)open.o : open.cpp | obj
	$(CC) -c $(CFLAGS) open.cpp -o $(BuildF)open.o

$(BuildF)save_graph.o: save_graph.cpp | obj
	$(CC) -c $(CFLAGS) save_graph.cpp -o $(BuildF)save_graph.o

$(BuildF)get_characterist.o: get_characterist.cpp | obj
	$(CC) -c $(CFLAGS) get_characterist.cpp -o $(BuildF)get_characterist.o

obj:
	mkdir $@

clean:
	del /q /s obj