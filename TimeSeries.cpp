/*
 * TimeSeries.cpp
 *
 *  Created on: Oct 25 2017
 *      Author: korhan
 */

#include "TimeSeries.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>


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

      cout << "here 1" << endl;
      OriginalSeries.push_back(val);
      cout << val << " here 2" << endl;
    }
    sleep(3);
    for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
    {


     	    cout << *it << endl;


    }
    sleep(5);
}
TimeSeries::~TimeSeries() {

}

void  TimeSeries::PAA(double MaxError)
{
       int i;
       std::vector<double> *TempSegHolder = new std::vector<double>();

       for (i = 0; i < OriginalSeries.size(); i++)
       {
    	    // new segment put Oirginal series element i in it
    	    // calculate new segment average (kkeep previous averages and/or aggregate  add one,
    	   // and error  for each
    	   TempSegHolder->push_back(1 + i);
    	   TempSegHolder->push_back(2 + i);
    	   TempSegHolder->push_back(3 + i);
    	   MySegs.push_back(*TempSegHolder);
    	   TempSegHolder->clear();

       }


       for (Segs::iterator it1 = MySegs.begin(); it1 != MySegs.end(); it1++)
       {

    	   for (std::vector<double>::iterator it2=it1->begin() ; it2 != it1->end(); it2++)
    	   {
                cout << " there  = " << *it2 << endl;
    	   }


       }







}
void  TimeSeries::PLR()
{

}




};
