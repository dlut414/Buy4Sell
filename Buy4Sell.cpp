///main function for Buy4Sell
///author: HU FANGYUAN
///2017.11~
#include <iostream>
#include <vector>
#include "Market.h"
#include "Agent.h"
using namespace std;
int main(){
	typedef int Cmt;
	const vector<Cmt> vcmt;
	Market<Cmt> mkt;
	Agent<Market<Cmt>> agt(mkt, vcmt);
	return 0;
}