CC=g++
CFLAGS=-c -Wall -std=c++14
INC=-isystem ../extern/boost_1_65_1

#Buy4Sell.exe: Buy4Sell.o Agent.o Market.o
#	$(CC) $? -o $@

Market.o: Market.h Market.cpp common.hpp Log.h
	$(CC) $(CFLAGS) $(INC) $< -o $@
	
Agent.o: Agent.h Agent.cpp common.hpp Log.h Strategy.h
	$(CC) $(CFLAGS) $(INC) $< -o $@
	
clean:
	rm *.o *.exe
