CC=g++
CFLAGS=-c -Wall -std=c++11
INC=-I ../extern/boost_1_65_1

Buy4Sell.exe: Buy4Sell.o
	$(CC) $? -o $@

Buy4Sell.o: Buy4Sell.cpp Agent.h Market.h Strategy.h Log.h
	$(CC) $(CFLAGS) $(INC) Buy4Sell.cpp

clean:
	rm *.o *.exe
