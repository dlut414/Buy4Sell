OBJS=Agent.o Market.o Buy4Sell.o Strategy.o
CC=g++
DEBUG=-g
CFLAGS=-c -Wall -std=c++14 $(DEBUG)
LFLAGS=-Wall $(DEBUG)
INC=-isystem ../extern/boost_1_65_1

Buy4Sell.exe: $(OBJS)
	$(CC) $(LFLAGS) $? -o $@
	
Buy4Sell.o: Buy4Sell.cpp Agent.hpp Market.hpp Strategy.hpp
	$(CC) $(CFLAGS) $(INC) $<

Market.o: Market.cpp Market.hpp common.hpp Log.hpp
	$(CC) $(CFLAGS) $(INC) $<

Agent.o: Agent.cpp Agent.hpp Strategy.hpp common.hpp Log.hpp
	$(CC) $(CFLAGS) $(INC) $<

Strategy.o: Strategy.cpp Strategy.hpp common.hpp Log.hpp
	$(CC) $(CFLAGS) $(INC) $<

clean:
	rm *.o *.exe
