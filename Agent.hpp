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
#include <boost/functional/hash.hpp>
#ifdef DEBUG
	#include <boost/uuid/uuid_io.hpp>
#endif
#include "common.hpp"
#include "Log.hpp"
#include "Strategy.hpp"
using boost::uuids::uuid;
using boost::uuids::random_generator;
typedef boost::hash<uuid> uuid_hash;

class Agent : public Log{
public:
	typedef Market Mkt;
	typedef std::tuple<int,int,int> Order_t; //commodity, number, price
	explicit Agent(Mkt& m, const std::vector<int>& nec, const std::vector<int>& holds, StrategyBase* stg_ptr,
					const uuid& _uid = random_generator()(), int _money = 100, int _life = 100);
	~Agent();
	
	bool bid(const int c, int num, int price);
	bool ask(const int c, int num, int price);
	bool retrieveOrder(const uuid& id);
	bool dealBid(const uuid& id, int volume, int price);
	bool dealAsk(const uuid& id, int volume, int price);
	bool act();
	
private:
	Mkt& mkt;
	const std::vector<int> necessities;
	std::unordered_map<int,int> holdings;
	const uuid uid;
	int money;
	int life;
	std::unordered_map<uuid,Order_t,uuid_hash> bidOrder;
	std::unordered_map<uuid,Order_t,uuid_hash> askOrder;
	random_generator gen;
	StrategyBase* stg;
};