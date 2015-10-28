#ifndef COMMONSTOCK_H
#define COMMONSTOCK_H

#include "Stock.h"

class CommonStock : public Stock
{
public:
	CommonStock(const char *sym, double parVal, double lastDiv) : Stock(sym, parVal, lastDiv)
	{}

	// Given market price, compute dividend yield
	double getDividendYield(double marketPrice) const;

	// Given market price, compute P/E ratio
	double getPEratio(double marketPrice) const;
	
	virtual ~CommonStock()
	{}
};

#endif



