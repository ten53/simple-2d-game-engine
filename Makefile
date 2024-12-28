build:
	g++ -Wall -std=c++17 src/*.cpp -I"./libs" -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -llua -o engine

run:
	./engine

clean:
	rm engine

