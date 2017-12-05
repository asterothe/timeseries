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

 /*   srand(time(NULL)) ;
    for (i = 0; i < SERIES_SIZE; i++)
    {

      val = rand() % 5 + 1;


      OriginalSeries.push_back(val);
      //cout << val << " <- generated" << endl;

      cout << val << " " ;
    }
    cout << endl;
*/
    sleep(3);


    OriginalSeries.push_back(5);
   // OriginalSeries.push_back(5);
    OriginalSeries.push_back(6);
    OriginalSeries.push_back(10);
    OriginalSeries.push_back(1);
    OriginalSeries.push_back(3);

    /*
    OriginalSeries.push_back(5);
    OriginalSeries.push_back(5);
    OriginalSeries.push_back(1);
    OriginalSeries.push_back(5);
    OriginalSeries.push_back(2);
    OriginalSeries.push_back(3);
    OriginalSeries.push_back(5);
    OriginalSeries.push_back(3);
    OriginalSeries.push_back(4);
    OriginalSeries.push_back(3);

*/
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

    	         cout << "-------------------------------------- " << endl;
    	         sum += *it;
    	         average = sum/count++;
             cout << "sum = " << sum << endl;
             cout << "average = " << average << endl;
    	         //error = abs(average- *it);
    	         // calculate error up to this element
    	         std::vector<double>::iterator it2 = it;
    	         int index = (int) count;
    	         index--;
    	         error = 0;
    	         while(index)
    	         {
    	        	     error += abs(average- *it2);
    	        	     index--;
    	        	     it2--;
    	         }
    	         //previouserror = error;
             cout << "error =  " << error <<endl;


    	         if (error < MaxError)
    	         {
    	              // add to the segment
    	        	     TempSegHolder->push_back(*it);
    	        	     lastgoodaverage = average;
    	        	     previouserror = error;


    	         }
    	         else
    	         {
    	        	     Errors.push_back(previouserror);
    	        	     Averages.push_back(lastgoodaverage);
    	        	      // reset average count error new segment
    	        	     sum = 0;
    	             sum = *it;
    	             count = 1;
    	             lastgoodaverage=average = sum/count++;
    	             cout << "sum* = " << sum << endl;
    	             cout << "average* = " << average << endl;
    	             previouserror= error = abs(average - *it);
    	             cout << "error* =  " << error <<endl;
    	      	     MySegs.push_back(*TempSegHolder);
    	      	     TempSegHolder->clear();
   	              // add  as the first element of the next segment
   	        	     TempSegHolder->push_back(*it);

    	         }

       }


       if (!TempSegHolder->empty())
       {
    	         MySegs.push_back(*TempSegHolder);
    	         TempSegHolder->clear();
        	     Errors.push_back(previouserror);
        	     Averages.push_back(lastgoodaverage);
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


       /*
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
*/
	   cout << " PAA Approx  = " << endl;
	   for (std::vector<double>::iterator it3=Averages.begin() ; it3 != Averages.end(); it3++)
	   {
            cout << " " << *it3;
	   }
       cout << endl;

       sleep(5);

       std::vector<double>::iterator it4=Averages.begin() ;
       std::vector<double>::iterator it5=Errors.begin() ;
       for (Segs::iterator it1 = MySegs.begin(); it1 != MySegs.end(); it1++)
       {

    	   cout << "new segment" << endl;

    	   for (std::vector<double>::iterator it2=it1->begin() ; it2 != it1->end(); it2++)
    	   {
                cout << " val  = " << *it2 << endl;
    	   }
       cout << "seg approx = " << *it4 << endl;
       it4++;
       cout << "seg error = " << *it5 << endl;
       it5++;
       }

       cout << " Approximations : "  << endl;
       std::vector<double>::iterator it6=Averages.begin() ;
       //std::vector<double>::iterator it7=Errors.begin() ;
       for (Segs::iterator it1 = MySegs.begin(); it1 != MySegs.end(); it1++)
       {



    	   for (std::vector<double>::iterator it2=it1->begin() ; it2 != it1->end(); it2++)
    	   {
                //cout << " val  = " << *it2 << endl;

                cout << " " << *it6 ;

    	   }
       it6++;

       //it5++;
       }
       cout << endl;



}
void  TimeSeries::PLR(double MaxError)
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
    double Begin = 0;
    double End = 0;
    double Slope = 0;
    double Constant = 0;
    std::vector<double>::iterator begit;
    std::vector<double>::iterator endit;
    std::vector<double>::iterator indexit;

    for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
    {
        cout << "HERE" <<endl;
        if (count == 1)
        {
               Begin = *it;
               begit = it;
               indexit = begit;
               cout << "HERE 2" <<endl;
        }
        else
        {
               End = *it;
               endit = it;
               cout << "HERE 3" <<endl;
        }

        if(count > 1)
        {
            cout << " begin =" << Begin <<  "end = " << End <<"count = " << count << endl;
            FindLineEquation(Begin, 1, End, count , Slope, Constant);
            cout << " y =" << Slope << "x+" << Constant << endl;
            cout << "HERE 4" <<endl;
        }
        // if the next element is on the line do not calculate new equation as an optimization

        if (count > 2)
        {
             //calculate errors until count = 1, Begin.
        	 cout << "HERE 5" <<endl;

        	     int internalcount = 1;
        	     while (indexit != endit)
        	     {

        	     CalculatePLRError(*indexit, Slope, internalcount++ ,Constant, error);
        	     cout << "error = " << error << endl;
        	     indexit++;
        	     }
        }

       count++;

        if (error > MaxError)
        {
        	     count = 1;
        	     error = 0;
        }
    }

}

void TimeSeries::FindLineEquation(double BeginY, double BeginX, double EndY, double EndX ,double& Slope, double& Constant)
{
     Slope = (EndY - BeginY)/ (EndX-BeginX);  // m = rise / run
     Constant = BeginY - BeginX  * Slope;      // b = y - mx
}

void TimeSeries::CalculatePLRError(double ActualValue, double Slope, double Count, double Constant, double& Error)
{
     // Error = actual value - (mx + b)
     Error += abs(ActualValue - Slope * Count - Constant);
}
};
