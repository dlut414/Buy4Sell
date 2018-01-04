///main function for Buy4Sell
///author: HU FANGYUAN
///2017.11~
#include <iostream>
#include <vector>
#define DEBUG
#include "Strategy.hpp"
#include "Market.hpp"
#include "Agent.hpp"
using namespace std;
typedef int Cmt;
typedef Market Mkt;
typedef Agent Agt;
int main(){
	Mkt mkt;
	Agt agt1(mkt, vector<Cmt>{1, 3}, vector<Cmt>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, new Strategy_);
	Agt agt2(mkt, vector<Cmt>{3, 4}, vector<Cmt>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, new Strategy_);
	cout << (agt1.ask(4, 2, 10) ? " Ask succeeds " : " Ask fails ") << endl;
	cout << (agt2.bid(4, 1, 16) ? " Bid succeeds " : " Bid fails ") << endl;
	mkt.showBidOrder();
	mkt.showAskOrder();
	cout << " Do transaction: " << (mkt.doTransaction() ? "Success" : "Fail") << endl;
	mkt.showBidOrder();
	mkt.showAskOrder();
	agt1.act();
	return 0;
}
