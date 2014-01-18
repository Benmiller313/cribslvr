objects = card.o hand.o

cribslvr : $(objects)
	g++   test.cpp -lUnitTest++  -o tests $(objects)
	./tests

card.o : card.cpp card.h
	g++ card.cpp -c
hand.o : hand.cpp hand.h
	g++ hand.cpp -c

.PHONY : clean
clean:
	-rm $(objects) tests