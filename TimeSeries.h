/*
 * TimeSeries.h
 *
 *  Created on: Oct 25, 2017
 *      Author: korhan
 */

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <vector>


using namespace std;

namespace ApproPlato
{

#define SERIES_SIZE  10
typedef std::vector<std::vector<double> > Segs;


class TimeSeries
{
	public:

	   TimeSeries();
	   virtual ~TimeSeries();


	   std::vector<double> OriginalSeries;
	   std::vector<double> PAASeries;
	   std::vector<double> PLRSeries;

	   Segs MySegs;


	   void  PAA(double MaxError);
	   void  PLR();

};
}


#endif /* TIMESERIES_H_ */
