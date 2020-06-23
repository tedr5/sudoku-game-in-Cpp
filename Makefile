#build:
	#windows compile lines
	#g++ -g -Wall \
	#./*.cpp \
	#-I"C:\libsdl\include" \
	#-L"C:\libsdl\lib" \
	#-lmingw32 \
	#-lSDL2main \
	#-lSDL2 \
	#-lSDL2_ttf \
#linux compile lines
#OBJS specifies which files to compile as part of the project
OBJS = main.cpp sudoku.cpp view.cpp read_write.cpp

#CC specifies which compiler we're using
CC = g++-9 -std=c++17

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = sudoku

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

exe:
	./sudoku PLAY1.sudoku
clean:
	rm sudoku
