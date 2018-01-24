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

typedef struct
{
     float Slope;
     float Constant;
}LineParameters;


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
	   void  PLR(double MaxError);
	   void  PLRbyLR(double MaxError);

	   void FindLineEquation(double BeginY, double BeginX, double EndY, double EndX  ,double& Slope, double& Constant);
	   void FindLineEquationByLR(double NewX, double NewY,double& SumX, double& SumY, double& SumXY, double& SumXSqr,
	   		double& SumYSqr, double& SampleSize, double& Slope, double& Constant);
	   void CalculatePLRError(double ActualValue, double Slope, double Count, double Constant, double& Error);

};
}


#endif /* TIMESERIES_H_ */
