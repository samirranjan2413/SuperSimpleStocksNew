#ifndef PREFERREDCOMMONSTOCK_H
#define PREFERREDCOMMONSTOCK_H

#include "Stock.h"

class PreferredStock : public Stock
{
private:
	double fixedDividend;

	void is_fixedDividend_ok(double fixedDiv) const;
	
public:
	PreferredStock(const char *sym, double parVal, double lastDiv, double fixedDiv) : Stock(sym, parVal, lastDiv), fixedDividend(fixedDiv)
	{
		is_fixedDividend_ok(fixedDividend);
	}

	double get_fixedDividend() const;
	void set_fixedDividend(double fixedDiv);

	// Given market price, compute dividend yield
    double getDividendYield(double marketPrice) const;

	// Given market price, compute P/E ratio
	double getPEratio(double marketPrice) const;

	virtual ~PreferredStock()
	{}
};

inline void PreferredStock::is_fixedDividend_ok(double fixedDiv) const
{
	if(fixedDiv < 0 || fixedDiv > 1)
		throw Exception("Fixed dividend cannot be below zero or greater than 100%");
	return;
}

inline double PreferredStock::get_fixedDividend() const
{
	return(fixedDividend);
}

inline void PreferredStock::set_fixedDividend(double fixedDiv)
{
	fixedDividend = fixedDiv;
	return;
}


#endif



