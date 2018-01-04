OBJS=Agent.o Market.o Buy4Sell.o Strategy.o
CC=g++
DEBUG=-g
CFLAGS=-c -Wall -std=c++14 $(DEBUG)
LFLAGS=-Wall $(DEBUG)
INC=-isystem ../extern/boost_1_65_1

Buy4Sell.exe: $(OBJS)
	$(CC) $(LFLAGS) $? -o $@
	
Buy4Sell.o: Buy4Sell.cpp Agent.h Market.h Strategy.h
	$(CC) $(CFLAGS) $(INC) $<

Market.o: Market.cpp Market.h common.hpp Log.h
	$(CC) $(CFLAGS) $(INC) $<

Agent.o: Agent.cpp Agent.h Strategy.h common.hpp Log.h
	$(CC) $(CFLAGS) $(INC) $<

Strategy.o: Strategy.cpp Strategy.h common.hpp Log.h
	$(CC) $(CFLAGS) $(INC) $<

clean:
	rm *.o *.exe
