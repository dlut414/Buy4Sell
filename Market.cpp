///class header file for Market: handle market information
///author: HU FANGYUAN
///2017.11~
#include "Market.h"
#include "Agent.h"
using namespace std;
using boost::uuids::uuid;
using boost::uuids::random_generator;

Market::Market(){}
Market::~Market(){}
bool Market::doTransaction(){
	try{
		bool b = true, a = true;
		for(auto it=bidOrder.begin();it!=bidOrder.end();++it){
			if(!askOrder.count(it->first)) continue;
			auto& bidv = it->second;
			auto& askv = askOrder[it->first];
			if(bidv.empty() || askv.empty()) continue;
			sort(bidv.begin(), bidv.end(), [](auto& p, auto& q){ return get<3>(p) < get<3>(q); });
			sort(askv.begin(), askv.end(), [](auto& p, auto& q){ return get<3>(p) < get<3>(q); });
			auto i=bidv.rbegin();
			auto j=askv.begin();
			for(;i!=bidv.rend()&&j!=askv.end();++i,++j){
				if(get<3>(*i) < get<3>(*j)) break;
				auto& nbid = get<2>(*i);
				auto& nask = get<2>(*j);
				const int volume = min(nbid, nask);
				const int price = (get<3>(*i) + get<3>(*j)) / 2;
				b = b && get<1>(*i)->dealBid(get<0>(*i), volume, price);
				a = a && get<1>(*j)->dealAsk(get<0>(*j), volume, price);
				nbid -= volume;
				nask -= volume;
				if(nbid != 0) --i;
				if(nask != 0) --j;
			}
			for(size_t i=0;i<bidv.size();i++){
				if(get<2>(bidv[i]) == 0) {
					bidv.erase(bidv.begin() + i);
					i--;
				}
			}
			for(size_t i=0;i<askv.size();i++){
				if(get<2>(askv[i]) == 0) {
					askv.erase(askv.begin() + i);
					i--;
				}
			}
		}
		return a && b;
	}catch(...){
		return false;
	}
}
bool Market::setBidOrder(const int c, const Market::Order_t& order){
	try{
		bidOrder[c].push_back(order);
		return true;
	}catch(...){
		return false;
	}
}
bool Market::setAskOrder(const int c, const Market::Order_t& order){
	try{
		askOrder[c].push_back(order);
		return true;
	}catch(...){
		return false;
	}
}
bool Market::retrieveOrder(const int c, const uuid& id){
	try{
		auto& bidv = bidOrder[c];
		for(auto it=bidv.begin();it!=bidv.end();++it){
			if(get<0>(*it) == id){
				bidv.erase(it);
				return true;
			}
		}
		auto& askv = askOrder[c];
		for(auto it=askv.begin();it!=askv.end();++it){
			if(get<0>(*it) == id){
				askv.erase(it);
				return true;
			}
		}
		return false;
	}catch(...){
		return false;
	}
}
const Market::OrderBook_t& Market::getBidOrder()const{
	return bidOrder;
}
const Market::OrderBook_t& Market::getAskOrder()const{
	return askOrder;
}
void Market::showBidOrder()const{
	cout << setw(11) << "Commodity" << setw(7) << "Number" << setw(7) << "Price" << endl;
	for(auto it=bidOrder.begin();it!=bidOrder.end();++it){
		for(auto itv=it->second.begin();itv!=it->second.end();++itv){
			cout << setw(10) << it->first << " "
				<< setw(6) << get<2>(*itv) << " " << setw(6) << get<3>(*itv) << endl;
		}
	}
}
void Market::showAskOrder()const{
	cout << setw(11) << "Commodity" << setw(7) << "Number" << setw(7) << "Price" << endl;
	for(auto it=askOrder.begin();it!=askOrder.end();++it){
		for(auto itv=it->second.begin();itv!=it->second.end();++itv){
			cout << setw(10) << it->first << " "
				<< setw(6) << get<2>(*itv) << " " << setw(6) << get<3>(*itv) << endl;
		}
	}
}