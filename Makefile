all: test.cpp shipwreck.hh
	g++ -Wall -std=c++11 -o runme test.cpp

dist:
	mkdir -p private;
	mv README.md test.cpp private

dev:
	mv private/* .
	rmdir private


clean:
	rm *.*~ runme *~

