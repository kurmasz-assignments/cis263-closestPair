CPPFLAGS = -g -Wall -std=c++17

all: studentTest

testMain.o: testMain.cpp
	g++ -c $(CPPFLAGS) $< -o $@

ClosestPairs.o: ClosestPairs.cpp ClosestPairs.h
	g++ -c $(CPPFLAGS) $< -o $@

closestPairsTest.o: closestPairsTest.cpp ClosestPairs.h
	g++ -c $(CPPFLAGS) $< -o $@

studentTest: closestPairsTest.o ClosestPairs.o testMain.o
	g++ $(CPPFLAGS) $^ -o $@

test:
	./studentTest

valgrind:
	valgrind --leak-check=full --error-exitcode=7 ./studentTest ~huge


