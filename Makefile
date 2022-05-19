all:
	g++ -Isrc/include -IHeader -Lsrc/lib/x86 -Lsrc/lib -o main Code/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf