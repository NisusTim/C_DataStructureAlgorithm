INC_DIR = /usr/local/include
#SRC_DIR = /usr/local/src
OBJ_DIR = /usr/local/obj
CC = g++
#EXE = 
#SRC = $(wildcard $(SRC_DIR)/*.c)
#OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#OBJ = $(OBJ_DIR)/catch_main.o
CPPFLAGS += -Iinclude
#CFLAGS += -Wall -g
LDFLAGS += -Llib
LDLIBS += -lm

.PHONY: all clean

all: $(EXE)
run: $(EXE)
	./$(EXE)

test_LinkedQueue: $(OBJ_DIR)/catch_main.o test_LinkedQueue.o LinkedQueue.o
	$(CC) -o $@ $^

catch_main.o: catch_main.cpp $(INC_DIR)/catch.hpp
	sudo $(CC) -c $< -o $(OBJ_DIR)/$@
test_LinkedQueue.o: test_LinkedQueue.cpp LinkedQueue.h $(INC_DIR)/catch.hpp
	$(CC) -c $<
LinkedQueue.o: LinkedQueue.c LinkedQueue.h
	$(CC) -c $<

clean:
	$(RM) $(filter-out catch_main.o $OBJ)
