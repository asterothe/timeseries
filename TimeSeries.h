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
typedef std::vector<std::vector<double> > Segs; //keeps track the original time series segment by segment

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


	   std::vector<double> OriginalSeries;   // original time series


	   Segs MySegs; // vector of segments. each segment is another vector of the original series for debugging purposes


       // estimated values - 1 for each segment  used only for PAA
       std::vector<double> Averages;

       // line equation parameters. used only for PLR
       std::vector<LineParameters> Lines;

       // error measures - 1 for each segment
       std::vector<double> Errors; // holds L2-norm of errors, each entry is the sum of abs errors for a segment
       std::vector<double> AbsoluteErrors; // hold the abs diff between sum of original and estimated values

       std::vector<unsigned int> ElementCountInSegment; // keeps track of the elements in a segment sequentially

       double GetDesiredApproxElementPAA(unsigned int positionindex); // gets the appoximated value for the desired element
       double GetDesiredApproxElementPLR(unsigned int positionindex); // same for PLR

	   void  PAA(double MaxError);  // calculates PAA approximation using the max error as threshold
	   void  PAAFixedLength(unsigned int SegmentLength); // calculates PAA with Fixed Length segments
	   double GetAverageErrors(); // Get the average of absolute Errors vector
	   void DebugPrintAllPAA();
	   void DebugPrintAllPLR();

       void CleanUp();

	   void  PLR(double MaxError);
	   void  PLRbyLR(double MaxError);

	   void  PLRFixedLength(unsigned int SegmentLength);  // calculates PAA with Fixed Length segments

       void FindLineEquation(double BeginY, double BeginX, double EndY, double EndX  ,double& Slope, double& Constant);
	   void FindLineEquationByLR(double NewX, double NewY,double& SumX, double& SumY, double& SumXY, double& SumXSqr,
	   double& SumYSqr, double& SampleSize, double& Slope, double& Constant);
	   void CalculatePLRError(double ActualValue, double Slope, double Count, double Constant, double& Error);

};
}


#endif /* TIMESERIES_H_ */
