/*
 * TimeSeries.cpp
 *
 *  Created on: Oct 25 2017
 *      Author: korhan
 */

#include "TimeSeries.h"
#include <time.h>
#include <stdlib.h>


namespace ApproPlato
{



//random values constructor
TimeSeries::TimeSeries()
{
    int i;
    int val;

    srand(time(NULL)) ;
    for (i = 0; i < SERIES_SIZE; i++)
    {

      val = rand() % 20 + 1;
      OriginalSeries.push_back(val);
    }

}
TimeSeries::~TimeSeries() {

}

void  TimeSeries::PAA(float MaxError)
{
       int i;

       for (i = 0; i < OriginalSeries.size(); i++)
       {
    	    // new segment put Oirginal series element i in it
    	    // calculate new segment average (kkeep previous averages and/or aggregate  add one,
    	   // and error  for each
       }

}
void  TimeSeries::PLR()
{

}




};
