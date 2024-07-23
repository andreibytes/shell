CC = gcc
CFLAGS= -c -Wall -I ./includes -g
EXECUTABLE = Shell
OBJECTS = main.o shell_builtins.o command.o helpers.o environment.o
SRC=./src
HEADERS=./includes

.PHONY: clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@


main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) $< -o $@


shell_builtins.o: $(SRC)/shell_builtins.c $(HEADERS)/shell_builtins.h
	$(CC) $(CFLAGS) $< -o $@

command.o: $(SRC)/command.c $(HEADERS)/command.h
	$(CC) $(CFLAGS) $< -o $@

helpers.o: $(SRC)/helpers.c $(HEADERS)/helpers.h
	$(CC) $(CFLAGS) $< -o $@

environment.o: $(SRC)/environment.c $(HEADERS)/environment.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE)
	rm $(OBJECTS)
