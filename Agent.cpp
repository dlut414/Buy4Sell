///class header file for Agent
///author: HU FANGYUAN
///2017.11~
#include "Agent.h"
using boost::uuids::uuid;
using boost::uuids::random_generator;
typedef boost::hash<uuid> uuid_hash;

typedef Market Mkt;
typedef std::tuple<int,int,int> Order_t; //commodity, number, price
explicit Agent::Agent(Mkt& m, const std::vector<int>& nec, const std::vector<int>& holds, StrategyBase* stg_ptr,
				const uuid& _uid = random_generator()(), int _money = 100, int _life = 100) 
: mkt(m), necessities(nec), uid(_uid), money(_money), life(_life), stg(stg_ptr){
	for(auto& i:holds) holdings[i]++;
}
Agent::~Agent(){}

bool Agent::bid(const int c, int num, int price){
	try{
		const int total = num* price;
		if(money < total) return false;
		const uuid id = gen();
		if( mkt.setBidOrder(c, std::make_tuple(id, this, num, price)) ) {
			bidOrder[id] = Order_t(c, num, price);
			money -= total;
			return true;
		}
		else return false;
	}catch(...){
		return false;
	}
}
bool Agent::ask(const int c, int num, int price){
	try{
		if(!holdings.count(c) || holdings[c] < num) return false;
		const uuid id = gen();
		if( mkt.setAskOrder(c, std::make_tuple(id, this, num, price)) ){
			askOrder[id] = Order_t(c, num, price);
			holdings[c] -= num;
			return true;
		}
		else return false;
	}catch(...){
		return false;
	}
}
bool Agent::retrieveOrder(const uuid& id){
	try{
		bool ret = true;
		if(bidOrder.count(id)) {
			const auto& t = bidOrder[id];
			money += std::get<1>(t) * std::get<2>(t);
			ret = mkt.retrieveOrder(std::get<0>(bidOrder[id]), id);
			ret = ret && bidOrder.erase(id);
		}
		else if(askOrder.count(id)) {
			const auto& t = askOrder[id];
			holdings[std::get<0>(t)] += std::get<1>(t);
			ret = mkt.retrieveOrder(std::get<0>(askOrder[id]), id);
			ret = ret && askOrder.erase(id);
		}
		return ret;
	}catch(...){
		return false;
	}
}
bool Agent::dealBid(const uuid& id, int volume, int price){
	try{
		if(!bidOrder.count(id)) return false;
		auto& t = bidOrder[id];
		holdings[std::get<0>(t)] += volume;
		money += (std::get<2>(t) - price)* volume;
		std::get<1>(t) -= volume;
		if(std::get<1>(t) == 0) bidOrder.erase(id);
		return true;
	}catch(...){
		return false;
	}
}
bool Agent::dealAsk(const uuid& id, int volume, int price){
	try{
		if(!askOrder.count(id)) return false;
		auto& t = askOrder[id];
		money += volume * price;
		std::get<1>(t) -= volume;
		if(std::get<1>(t) == 0) askOrder.erase(id);
		return true;
	}catch(...){
		return false;
	}
}
bool Agent::act(){
	try{
		stg->act(this, &mkt);
		return true;
	}catch(...){
		return false;
	}
}