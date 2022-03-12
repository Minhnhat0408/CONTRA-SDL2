all:
	g++ -Isrc/include -I E:/Minhnhat/Gaming_stuff/Header -Lsrc/lib -o main Code/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image 