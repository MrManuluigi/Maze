CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic
RM = rm -rf

SRC_PATH = ./src/
INC_PATH = ./include/
OBJ_PATH = ./obj/
BIN_PATH = ./bin/
SCORE = ./score/
PLANS = ./plan/

all : lab

lab : $(OBJ_PATH)main.o $(OBJ_PATH)maze.o
	$(CC) -o $(BIN_PATH)$@ $^

$(OBJ_PATH)main.o : $(SRC_PATH)main.c
	$(CC) $(CFLAGS) $^ -I$(INC_PATH) -c -o $@

$(OBJ_PATH)maze.o : $(SRC_PATH)maze.c
	$(CC) $(CFLAGS) $^ -I$(INC_PATH) -c -o $@

clean :
	rm -f *.o

distclean:
	$(RM) $(OBJ_PATH)*.o
	$(RM) $(BIN_PATH)*
	$(RM) $(SCORE)*.score
	$(RM) $(PLANS)*.cfg

.PHONY : clean all distclean
