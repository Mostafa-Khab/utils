all: src
	g++ idump.cpp -o build/idump -Ideps

src: src/build.sh
	./src/build.sh

clean:
	rm -r build/*


