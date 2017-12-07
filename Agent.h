///class header file for Agent
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <unordered_map>
#include <utility>
#include <tuple>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#ifdef DEBUG
	#include <boost/uuid/uuid_io.hpp>
#endif
#include <boost/functional/hash.hpp>
#include "Log.h"
using boost::uuids::uuid;
using boost::uuids::random_generator;
typedef boost::hash<uuid> uuid_hash;

template <typename Mkt>
class Agent : public Log{
public:
	typedef typename Mkt::Cmt Cmt;
	typedef std::tuple<Cmt,int,int> Order_t; //commodity, number, price
	explicit Agent(Mkt& m, const std::vector<Cmt>& nec, const std::vector<Cmt>& holds, const uuid& _uid = random_generator()(), int _money = 100, int _life = 100) 
	: mkt(m), necessities(nec), uid(_uid), money(_money), life(_life){
		for(auto& i:holds) holdings[i]++;
	}
	~Agent(){}
	
	bool bid(const Cmt c, int num, int price){
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
	bool ask(const Cmt c, int num, int price){
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
	bool retrieveOrder(const uuid& id){
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
	void update(){
		
	}
	bool dealBid(const uuid& id, int volume, int price){
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
	bool dealAsk(const uuid& id, int volume, int price){
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
	
private:
	Mkt& mkt;
	const std::vector<Cmt> necessities;
	std::unordered_map<Cmt,int> holdings;
	const uuid uid;
	int money;
	int life;
	std::unordered_map<uuid,Order_t,uuid_hash> bidOrder;
	std::unordered_map<uuid,Order_t,uuid_hash> askOrder;
	random_generator gen;
};