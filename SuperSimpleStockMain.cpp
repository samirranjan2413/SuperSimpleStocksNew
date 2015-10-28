#include <fstream>
#include <iostream> 
#include <vector>

#include "Trade.h"

using namespace std;

time_t getCurrentTime()
{
	time_t t;
    time(&t);

	return t;
}

time_t MDY_2_calenderTime(int sec /* 0 to 61 */, int min /* 0 to 59 */, int hour /* 0 to 23 */,
	                      int day /* 1 t0 31 */, int month /* 0 to 11 */, int year /* years since 1900 */,
						  int dow /* days since Sunday - 0 to 6 */, int yday /* days since January 1 - 0 to 365 */,
						  int isdst /* Daylight savings time flag */)
{
	struct tm thisTime = {sec, min, hour, day, month, year, dow, yday, isdst};

	time_t t = mktime(&thisTime);

	return t;
}

// The following funtion returns a random number between 0 and 1
double generateRandomNumber()
{
	return (double)rand()/(double)RAND_MAX;
}

int main()
{
	double small = 0.000001;
	time_t t = time(NULL);
	time_t timeStamp; 
	int numShares; 
	int buyOrSell;    // 1 for buy, 0 for sell
	double tradePrice;

	double fixedDividend;
	double parValue;
	double lastDividend;

	double VWSP;
	double GBCE_Index;
	
	const int nTrades = 1000; 
	vector<Trade> vTrade;

	Stock *pSt[nTrades];

	CommonStock *pCSt;
	PreferredStock *pPSt;

	const char commonStockSymbol[] = "CCC";  // same for all common stocks for simplicity
	const char prefStockSymbol[] = "PPP";  // same for all prefered stocks for simplicity

	try
	{
		// generate nTrades trades
		for(int i=0; i < nTrades; ++i)
		{
			timeStamp = t - ((int)(generateRandomNumber()*4000) + 1); // time stamps in last hour
			numShares = (int)(generateRandomNumber()*100) + 1; // each trade with number of shares between 1 and 100
			buyOrSell = 0.5 > generateRandomNumber() ? 1 : 0;    // 1 for buy, 0 for sell
			tradePrice = (double)((int)(generateRandomNumber()*1000)) + 1; // trade price between 1 and 1000
		    fixedDividend = (double)((int)(generateRandomNumber()*100))/100; // fixed dividend beween 0 and 1
			parValue = (double)((int)(generateRandomNumber()*100)) + 1; // par value between 1 and 100
			lastDividend = (double)((int)(generateRandomNumber()*100)) + 1; // last dividend amount between 1 and 100

			if(generateRandomNumber() > 0.5)
			{
				// construct a common stock

				pCSt = new CommonStock(commonStockSymbol, parValue, lastDividend);

				pSt[i] = pCSt;
			}
			else
			{
				// construct a preferred stock

				pPSt = new PreferredStock(prefStockSymbol, parValue, lastDividend, fixedDividend);

				pSt[i] = pPSt;
			}

			vTrade.push_back(Trade(pSt[i], timeStamp, numShares, buyOrSell, tradePrice));
		}

		// We compute the follwing:
		// 1. GBCE All Share Index using the geometric mean of prices of all stocks
		// 2. Volume Weighted Stock Price based on trades in past fifteen minutes, and
		// 

		double numerator = 0;
		double denominator = 0;
		double sumlog_TradePrice = 0;
		int quantity;
	
		time_t currentTime = getCurrentTime();
		time_t trade_timeStamp;

		int nShares = 0;

		for(unsigned int j=0; j < vTrade.size(); ++j)
		{			
			tradePrice = vTrade[j].get_tradePrice();

			if(!(tradePrice < small))
			{
				sumlog_TradePrice += log(tradePrice);
				nShares += 1;
			}
			else
			{
				throw Exception("Trade price too small");
			}

			// Check if this trade happened within the last 15 minutes
			trade_timeStamp = vTrade[j].getTimeStampAsCalendarTime();

			if((difftime(currentTime, trade_timeStamp)) > 15*60)
				continue;

			quantity = vTrade[j].get_numShares();

			numerator += tradePrice * (double)quantity;
			denominator += quantity;
		}

		// Volume Weighted Stock Price based on trades in past 15 minutes
		//
		if(!(denominator < small))
			VWSP = numerator/(double)denominator;

		// GBCE All Share Index using the geometric mean of prices for all stocks
		//
		if(nShares != 0)
			GBCE_Index = exp(sumlog_TradePrice/(double)nShares);
	}
	catch(Exception e)
	{
		cerr << e.message << endl;
	}

	char stockSym[4];
	time_t tradeTime;

	ofstream outfile("trade_data.txt");

	outfile << "StockSymbol ; LastDiv ; FixedDiv ; ParVal ; CurrentTime; TimeStamp; TradePrice ; Qty ; PE_Ratio ; DivYield \n";

	for(int i=0; i<nTrades; ++i)
	{
		vTrade[i].get_stockSymbol(stockSym);

		outfile << stockSym << " ; " << vTrade[i].getStockLastDiv() << " ; "			    
			    << vTrade[i].getStockFixedDiv() << " ; " << vTrade[i].getStockParValue() << " ; ";

		tradeTime = vTrade[i].getTimeStampAsCalendarTime();

		outfile << (int)t  << " ; " << (int)tradeTime << " ; "
	            << vTrade[i].get_tradePrice() << " ; " << vTrade[i].get_numShares() << " ; "
				<< vTrade[i].getPEratio() << " ; " << vTrade[i].getDividendYield() << "\n";
	}

	outfile << "\nVWSP ; " << VWSP << "\n";
	outfile << "GBCE Index ; " << GBCE_Index << "\n";

	for(int i=0; i < nTrades; ++i)
	{
		delete pSt[i];
	}

	return 0;
}






