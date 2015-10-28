#include "Stock.h"

using namespace std;

// Given market price, compute P/E ratio
double Stock::getPEratio(double marketPrice) const
{
	double small = 0.000001;

	// check if the marketPrice is zero
	if(marketPrice < small)
		throw Exception("Market price too small - Not allowed");

	if(lastDividend < small)
		throw Exception("Last dividend too small to caculate P/E ratio");

	double PEratio = marketPrice/lastDividend;

	return PEratio;
}

void Stock::is_input_ok(double lastDividend) const
{
	is_parValue_ok();
	is_lastDividend_ok(lastDividend);

	return;
}
