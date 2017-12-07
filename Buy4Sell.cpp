///main function for Buy4Sell
///author: HU FANGYUAN
///2017.11~
#include <iostream>
#include <vector>
#define DEBUG
#include "Market.h"
#include "Agent.h"
using namespace std;
typedef int Cmt;
typedef Market<Cmt> Mkt;
int main(){
	Mkt mkt;
	Agent<Mkt> agt1(mkt, vector<Cmt>{1, 3}, vector<Cmt>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5});
	Agent<Mkt> agt2(mkt, vector<Cmt>{3, 4}, vector<Cmt>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5});
	agt1.ask(4, 2, 10);
	agt2.bid(4, 1, 16);
	cout << "do transaction: " << mkt.doTransaction() << endl;
	return 0;
}