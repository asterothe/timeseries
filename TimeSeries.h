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

#define SERIES_SIZE  1000

class TimeSeries
{
	public:

	   TimeSeries();
	   virtual ~TimeSeries();


	   std::vector<double> OriginalSeries;
	   std::vector<double> PAASeries;
	   std::vector<double> PLRSeries;



	   void  PAA(float MaxError);
	   void  PLR();

};
}


#endif /* TIMESERIES_H_ */
