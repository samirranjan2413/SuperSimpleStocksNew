#include "Trade.h"

using namespace std;

double Trade::getDividendYield() const
{
	return pStock->getDividendYield(tradePrice);
}
double Trade::getPEratio() const
{
	return pStock->getPEratio(tradePrice);
}

void Trade::getTimeStampMDY(int *sec, int *min, int *hour, int *day, int *month, int *year, int *dow) const
{
	struct tm *localTime;

	localTime = localtime(&timeStamp);

	*sec = localTime->tm_sec;
	*min = localTime->tm_min;
	*hour = localTime->tm_hour;
	*day = localTime->tm_mday;
	*month = localTime->tm_mon;
	*year = localTime->tm_year + 1900;
	*dow = localTime->tm_wday;

	return;
}
