OBJS = src/*.cc src/*.h

CC = ccache g++

# -w suppresses all warnings
COMPILER_FLAGS = -std=c++11

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = bin/Main

build: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	@echo compiling completed
	@echo ...
	@echo copying resources
	cp res/* bin
	@echo ...
	@echo copying finished

run:
	@echo start prog
	./$(OBJ_NAME)

build&run: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	@echo compiling completed
	@echo ...
	@echo copying resources
	cp res/* bin
	@echo ...
	@echo copying finished
	@echo ...
	@echo start prog
	./$(OBJ_NAME)

clean:
	rm bin/*
