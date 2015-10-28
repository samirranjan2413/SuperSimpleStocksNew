#ifndef STOCK_H
#define STOCK_H

#include "Exception.h"

class Stock
{
private:
	char symbol[4];
	double parValue;
	double lastDividend;

	void is_parValue_ok() const;
	void is_lastDividend_ok(double lastDiv) const;
	void is_input_ok(double lastDiv) const;
	
public:
	Stock(const char *sym, double parVal, double lastDiv): parValue(parVal), lastDividend(lastDiv)
	{
		is_input_ok(lastDividend);

		symbol[0] = '\0';
		strcpy(symbol, sym);
	}

	// Given market price, compute dividend yield
	virtual double getDividendYield(double marketPrice) const = 0;

	// Given market price, compute P/E ratio
	virtual double getPEratio(double marketPrice) const;

	void setLastDividend(int lastDiv);
	double getLastDividend() const;
	double getParValue() const;

	virtual double get_fixedDividend() const;
	virtual void get_stockSymbol(char *stSymbol) const;

	virtual ~Stock()
	{}

}; // END class Stock

inline void Stock::get_stockSymbol(char *stSymbol) const
{
	strcpy(stSymbol, symbol);
}

inline double Stock::get_fixedDividend() const
{
	return -1;
}

inline void Stock::setLastDividend(int lastDiv)
{
	is_lastDividend_ok(lastDiv);

	lastDividend = lastDiv;

	return;
}

inline double Stock::getLastDividend() const
{
	return lastDividend;
}

inline double Stock::getParValue() const
{
	return parValue;
}

inline void Stock::is_parValue_ok() const
{
	if(parValue < 0)
		throw Exception("Par Value cannot be negative");

	return;
}

inline void Stock::is_lastDividend_ok(double lastDiv) const
{
	if(lastDiv < 0)
		throw Exception("Last Dividend cannot be negative");

	return;
}

#endif