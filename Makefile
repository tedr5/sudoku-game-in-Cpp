build:
	g++ -g -Wall \
	./*.cpp \
	-I"C:\libsdl\include" \
	-L"C:\libsdl\lib" \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_ttf \

clean:
	rm a.exe
