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
#include <math.h>


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

      val = rand() % 5 + 1;


      OriginalSeries.push_back(val);
      cout << val << " <- generated" << endl;
    }
    sleep(3);

    /*
    for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
    {


     	    cout << *it << endl;


    }
    sleep(5);
    */
}
TimeSeries::~TimeSeries() {

}

void  TimeSeries::PAA(double MaxError)
{
       int i;
       std::vector<double> *TempSegHolder = new std::vector<double>();
       std::vector<double> Errors;
       std::vector<double> Averages;
       double average = 0;
       double count = 1;
       double error = 0;
       double sum = 0;
       double previouserror = 0;
       double lastgoodaverage = 0;
       for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
       {
    	         sum += *it;
    	         average = sum/count++;

    	         //error = abs(average- *it);
    	         // calculate error up to this element
    	         std::vector<double>::iterator it2 = it;
    	         int index = (int) count;
    	         index--;
    	         while(index)
    	         {
    	        	 error += abs(average- *it2);
    	        	 index--;
    	         }
    	         previouserror = error;
             cout << "error =  " << error <<endl;


    	         if (error < MaxError)
    	         {
    	              // add to the segment
    	        	     TempSegHolder->push_back(*it);
    	        	     lastgoodaverage = average;



    	         }
    	         else
    	         {
    	        	     Errors.push_back(previouserror);
    	        	     Averages.push_back(lastgoodaverage);
    	        	      // reset average count error new segment
    	        	     sum = 0;
    	             sum = *it;
    	             count = 1;
    	             average = sum/count;
    	             previouserror= error = abs(average - *it);
    	      	     MySegs.push_back(*TempSegHolder);
    	      	     TempSegHolder->clear();
   	              // add  as the first element of the next segment
   	        	     TempSegHolder->push_back(*it);

    	         }

       }

/*
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
*/

       for (Segs::iterator it1 = MySegs.begin(); it1 != MySegs.end(); it1++)
       {

    	   cout << "new segment" << endl;

    	   for (std::vector<double>::iterator it2=it1->begin() ; it2 != it1->end(); it2++)
    	   {
                cout << " val  = " << *it2 << endl;
    	   }


       }

	   for (std::vector<double>::iterator it3=Errors.begin() ; it3 != Errors.end(); it3++)
	   {
            cout << " Error  = " << *it3 << endl;
	   }

	   for (std::vector<double>::iterator it3=Averages.begin() ; it3 != Averages.end(); it3++)
	   {
            cout << " Average  = " << *it3 << endl;
	   }




}
void  TimeSeries::PLR()
{

}




};
