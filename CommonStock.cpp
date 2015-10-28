#include "CommonStock.h"

using namespace std;

double CommonStock::getPEratio(double marketPrice) const
{
	return Stock::getPEratio(marketPrice);
}
// Given market price, compute dividend yield
double CommonStock::getDividendYield(double marketPrice) const
{
	double small = 0.000001;

	// check if the marketPrice is zero
	if(marketPrice < small)
		throw Exception("Market price too small - Not allowed");

	double dividend = Stock::getLastDividend();
	double divYield = dividend/marketPrice;

	return divYield;
}
