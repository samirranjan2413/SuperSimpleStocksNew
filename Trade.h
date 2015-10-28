#ifndef TRADE_H
#define TRADE_H

#include "CommonStock.h"
#include "PreferredStock.h"
#include "time.h"

class Trade
{
private:
	Stock *pStock;
	time_t timeStamp;
	int numShares;
	int buyOrSell;    // 1 for buy, 0 for sell
	double tradePrice;
	
	void is_timeStamp_ok(time_t ts) const;
	void is_numShares_ok(int nS) const;
	void is_buyOrsell_ok(int boS) const;
	void is_tradePrice_ok(double tP) const;
	void is_Input_ok(time_t ts, int nS, int boS, double tP) const;

public:
	Trade(Stock* pSt, time_t givenTimeStamp, int qty, int buySell, double price): pStock(pSt), timeStamp(givenTimeStamp), numShares(qty),
		                                                             buyOrSell(buySell), tradePrice(price) 
	{
		is_Input_ok(timeStamp, numShares, buyOrSell, tradePrice);
	}

	void getTimeStampMDY(int *sec, int *min, int *hour, int *day, int *month, int *year, int *dow) const;

	int get_numShares() const;
	void set_numShares(int);

	int get_buyOrSell() const;
	void set_buyOrSell(int buySell);

	double get_tradePrice() const;
	void set_TradePrice(double price);

	time_t getTimeStampAsCalendarTime() const;

	double getStockLastDiv() const;
	double getStockFixedDiv() const;
	double getStockParValue() const;
	void get_stockSymbol(char *stSymbol) const;

	double getPEratio() const;
	double getDividendYield() const;
	
	virtual ~Trade()
	{}

}; // END class Trade

inline double Trade::getStockParValue() const
{
	return pStock->getParValue();
}
inline void Trade::get_stockSymbol(char *stSymbol) const
{
	pStock->get_stockSymbol(stSymbol);
}
inline double Trade::getStockLastDiv() const
{
	return pStock->getLastDividend();
}
inline time_t Trade::getTimeStampAsCalendarTime() const
{
	return timeStamp;
}

inline double Trade::getStockFixedDiv() const
{
	return pStock->get_fixedDividend();
}
inline void Trade::is_Input_ok(time_t ts, int nS, int boS, double tP) const
{
	is_timeStamp_ok(ts);
	is_numShares_ok(nS);
	is_buyOrsell_ok(boS);
	is_tradePrice_ok(tP);

	return;
}

inline void Trade::is_timeStamp_ok(time_t tS) const
{
		if(tS < 0)
			throw Exception("Illegal value of time or date given for timeStamp");

		return;
}
inline void Trade::is_numShares_ok(int nS) const
{
	if(nS < 0)
		throw Exception("Illegal number of shares. Number of shares cannot be negative");

	return;
}

inline void Trade::is_buyOrsell_ok(int boS) const
{
	if(boS < 0 || boS > 1)
		throw Exception("Illegal buy/sell directive. Must be 0 (for sell) or 1 (for buy)");

	return;
}

inline void Trade::is_tradePrice_ok(double tP) const
{
	if(tP < 0)
		throw Exception("Illegal trade price. Must be greater than or equal to zero.)");

	return;
}

inline int Trade::get_numShares() const
{
	return numShares;
}

inline void Trade::set_numShares(int qty)
{
	is_numShares_ok(qty);
	numShares = qty;
	return;
}

inline int Trade::get_buyOrSell() const
{
	return buyOrSell;
}

inline void Trade::set_buyOrSell(int buySell)
{
	is_buyOrsell_ok(buySell);
	buyOrSell = buySell;
	return;
}

inline double Trade::get_tradePrice() const
{
	return tradePrice;
}
inline void Trade::set_TradePrice(double price)
{
	is_tradePrice_ok(price);
	tradePrice = price;
	return;
}

#endif