#include "PreferredStock.h"

using namespace std;

double PreferredStock::getPEratio(double marketPrice) const
{
	return Stock::getPEratio(marketPrice);
}

// Given market price, compute dividend yield
double PreferredStock::getDividendYield(double marketPrice) const
{
	double small = 0.000001;

	// check if the marketPrice is zero
	if(marketPrice < small)
		throw Exception("Market price too small - Not allowed");

	double parValue = Stock::getParValue();
	
	double divYield = fixedDividend*parValue/marketPrice;

	return divYield;
}
