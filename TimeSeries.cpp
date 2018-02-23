
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
#include <fstream>


namespace ApproPlato
{



// assumes file3.csv is available. this time we create a time series using the 3rd float parameter which
// is ENGINE SPEED. this is the largest csv file of LAJ00508_part4.cvs minus the first line with column names
// removed. it has 500000 rows therefore the len of the time series is 500000.
TimeSeries::TimeSeries()
{


   float f1, f2, f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14;
   char str1[100], str2[100], str3[100];
   unsigned int pushcounter = 0;
    FILE *fp;
    //fp = fopen("508-temperature.csv", "r");
    fp = fopen("AUDJPY.csv", "r");
    while (fscanf(fp, "%g\n",
           &f3) == 1)
    {
       //printf("%g %g %g %g \n", f1, f2, f3, f4);
        OriginalSeries.push_back(f3);
        pushcounter++;

        //cout << f3 <<endl;

         //to limit the size of the data we want to process
        if (pushcounter == 100000)
        break;
    }

    cout << "Series size = "<< OriginalSeries.size()  << endl;

/*
    fp = fopen("file2.csv", "r");
    while (fscanf(fp, "\"%8s\",\"%10s %12s\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\"\n",
		  str1, str2, str3, &f1, &f2, &f3, &f4 ,&f5, &f6,&f7, &f8,&f9, &f10,&f11, &f12,&f13) == 16)
    {
       //printf("%g %g %g %g \n", f1, f2, f3, f4);
        OriginalSeries.push_back(f3);
    }
    fclose(fp);
    */
    /*
    fp = fopen("file1.csv", "r");
    while (fscanf(fp, "\"%8s\",\"%10s %12s\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\"\n",
		  str1, str2, str3, &f1, &f2, &f3, &f4 ,&f5, &f6,&f7, &f8,&f9, &f10,&f11, &f12,&f13) == 16)
    {
       //printf("%g %g %g %g \n", f1, f2, f3, f4);
        OriginalSeries.push_back(f3);
    }
    fclose(fp);
    fp = fopen("file3.csv", "r");
    while (fscanf(fp, "\"%8s\",\"%10s %12s\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\"\n",
		  str1, str2, str3, &f1, &f2, &f3, &f4 ,&f5, &f6,&f7, &f8,&f9, &f10,&f11, &f12,&f13) == 16)
    {
       //printf("%g %g %g %g \n", f1, f2, f3, f4);
        OriginalSeries.push_back(f3);
    }
    fclose(fp);
    fp = fopen("file4.csv", "r");
    while (fscanf(fp, "\"%8s\",\"%10s %12s\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\"\n",
		  str1, str2, str3, &f1, &f2, &f3, &f4 ,&f5, &f6,&f7, &f8,&f9, &f10,&f11, &f12,&f13) == 16)
    {
       //printf("%g %g %g %g \n", f1, f2, f3, f4);
        OriginalSeries.push_back(f3);
    }
    fclose(fp);
    fp = fopen("file5.csv", "r");
    while (fscanf(fp, "\"%8s\",\"%10s %12s\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\"\n",
		  str1, str2, str3, &f1, &f2, &f3, &f4 ,&f5, &f6,&f7, &f8,&f9, &f10,&f11, &f12,&f13) == 16)
    {
       //printf("%g %g %g %g \n", f1, f2, f3, f4);
        OriginalSeries.push_back(f3);
    }
    fclose(fp);
    fp = fopen("file6.csv", "r");
    while (fscanf(fp, "\"%8s\",\"%10s %12s\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\"\n",
		  str1, str2, str3, &f1, &f2, &f3, &f4 ,&f5, &f6,&f7, &f8,&f9, &f10,&f11, &f12,&f13) == 16)
    {
       //printf("%g %g %g %g \n", f1, f2, f3, f4);
        OriginalSeries.push_back(f3);
    }
    fclose(fp);
    */


}

TimeSeries::~TimeSeries() {
}

void  TimeSeries::PAAFixedLength(unsigned int SegmentLength)
{
    int i;

     // holds the actual values for the segment. it has as many elements as the segment approximate
     std::vector<double> *TempSegHolder = new std::vector<double>();

     double average = 0;
     double count = 1;
     double error = 0;
     double sum = 0;
     double previouserror = 0;
     double lastgoodaverage = 0;
     double sumoforiginalTS = 0;
     double sumofestimations = 0;
     for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
     {
  	         sum += *it;


  	         // do the calculations once when the segment len is reached or if we are processing the last element
  	         if (count   ==  SegmentLength || (it + 1) == OriginalSeries.end())
  	         {
  	            average = sum/count;
	            std::vector<double>::iterator it2 = it;
  	            int index = (int) count;
  	            error = 0;
  	            while(index)
  	            {
  	        	        error += pow(fabs(average- *it2),2);
  	        	        index--;
  	        	        it2--;
  	            }
                // keep these for consistency otherwise FL does not need
  	            previouserror = error;
  	            lastgoodaverage = average;
  	            sumofestimations  = (count ) * lastgoodaverage;
  	         }

  	         if (count   <= SegmentLength)
  	         {

  	              // add to the segment
  	        	     TempSegHolder->push_back(*it);
  	        	     //lastgoodaverage = average;
  	        	     //previouserror = error;
  	    	         sumoforiginalTS += *it;
  	    	         //sumofestimations  = (count ) * lastgoodaverage;
  	         }
  	         else // NEW SEGMENT
  	         {
  	        	     Errors.push_back(sqrt(previouserror));
  	        	     Averages.push_back(lastgoodaverage);
  	        	     ElementCountInSegment.push_back(count - 1);
  	        	      // reset average count error new segment
  	        	     sum = 0;
  	             sum = *it;
  	             count = 1;
  	             lastgoodaverage=average = sum/count;
  	             previouserror= error = fabs(average - *it);
  	      	     MySegs.push_back(*TempSegHolder);
  	      	     TempSegHolder->clear();
 	              // add  as the first element of the next segment
 	        	     TempSegHolder->push_back(*it);

 	        	     AbsoluteErrors.push_back(fabs(sumofestimations-sumoforiginalTS));
 	        	     // restart absolute error calculation
 	    	         sumoforiginalTS = *it;
 	    	         sumofestimations = count  * lastgoodaverage;
  	         }
             count++;
     }


     if (!TempSegHolder->empty())
     {
  	         MySegs.push_back(*TempSegHolder);
  	         TempSegHolder->clear();
      	     Errors.push_back(sqrt(previouserror));
      	     Averages.push_back(lastgoodaverage);
      	     AbsoluteErrors.push_back(fabs(sumofestimations-sumoforiginalTS));
      	     ElementCountInSegment.push_back(count -1);
     }
}


// calculate PAA using SW, keeping the error for the segment under MaxError
void  TimeSeries::PAA(double MaxError)
{
       int i;

       // holds the actual values for the segment. it has as many elements as the segment approximate
       std::vector<double> *TempSegHolder = new std::vector<double>();

       double average = 0;
       double count = 1;
       double error = 0;
       double sum = 0;
       double previouserror = 0;
       double lastgoodaverage = 0;
       double sumoforiginalTS = 0;
       double sumofestimations = 0;
       unsigned int index2 = 1;
       unsigned int segindex = 1;
       MaxError = pow(MaxError,2); // compare against the squared value to make calculations easier
       for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
       {

    	         sum += *it;
    	         average = sum/count++;
    	         if (index2 % 1000 == 0)
                cout << "working on " << index2 << endl;
    	         index2++;
    	         // calculate error up to this element
    	         std::vector<double>::iterator it2 = it;
    	         int index = (int) count;
    	         index--;
    	         error = 0;
    	         while(index)
    	         {
    	        	     error += pow(fabs(average- *it2),2);
    	        	     index--;
    	        	     it2--;
    	         }

    	         if (error < MaxError)
    	         {
    	              // add to the segment
    	        	     TempSegHolder->push_back(*it);
    	        	     lastgoodaverage = average;
    	        	     previouserror = error;
    	    	         sumoforiginalTS += *it;
    	    	         sumofestimations  = (count -1) * lastgoodaverage;
    	         }
    	         else // Create NEW SEGMENT, save old segment and params
    	         {
    	        	     Errors.push_back(sqrt(previouserror));
    	        	     Averages.push_back(lastgoodaverage);
    	        	     ElementCountInSegment.push_back(count - 2);

    	        	      // reset average count error new segment
    	        	     sum = 0;
    	             sum = *it;
    	             count = 1;
    	             lastgoodaverage=average = sum/count++;

    	             previouserror= error = pow(fabs(average - *it),2);

    	      	     MySegs.push_back(*TempSegHolder);
    	      	     TempSegHolder->clear();
   	              // add  as the first element of the next segment
   	        	     TempSegHolder->push_back(*it);
   	        	     //if (segindex % 10== 0)
                   cout << "new segment "  << segindex++ << endl;
   	        	     AbsoluteErrors.push_back(fabs(sumofestimations-sumoforiginalTS));
   	        	     // restrart absolute error calculation
   	    	         sumoforiginalTS = *it;
   	    	         sumofestimations = (count - 1) * lastgoodaverage;
    	         }
       }


       if (!TempSegHolder->empty())
       {
    	         MySegs.push_back(*TempSegHolder);
    	         TempSegHolder->clear();
        	     Errors.push_back(sqrt(previouserror));
        	     Averages.push_back(lastgoodaverage);
        	     AbsoluteErrors.push_back(fabs(sumofestimations-sumoforiginalTS));
        	     ElementCountInSegment.push_back(count - 1);
       }
}


// calculate PAA using SW, keeping the error for the segment under MaxError
void  TimeSeries::PAAIncremental(double MaxError)
{
       int i;

       // holds the actual values for the segment. it has as many elements as the segment approximate
       std::vector<double> *TempSegHolder = new std::vector<double>();

       double average = 0;
       double count = 1;
       double error = 0;
       double sum = 0;
       double previouserror = 0;
       double lastgoodaverage = 0;
       double sumoforiginalTS = 0;
       double sumofestimations = 0;
       MaxError = pow(MaxError,2); // compare against the squared value to make calculations easier
       for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
       {

    	         sum += *it;
    	         average = sum/count++;

    	         error +=  pow(fabs(average- *it),2);



    	         if (error < MaxError)
    	         {
    	              // add to the segment
    	        	     TempSegHolder->push_back(*it);
    	        	     lastgoodaverage = average;
    	        	     previouserror = error;
    	    	         sumoforiginalTS += *it;
    	    	         sumofestimations  = (count -1) * lastgoodaverage;
    	         }
    	         else // Create NEW SEGMENT, save old segment and params
    	         {
    	        	     Errors.push_back(sqrt(previouserror));
    	        	     Averages.push_back(lastgoodaverage);
    	        	     ElementCountInSegment.push_back(count - 2);

    	        	      // reset average count error new segment
    	        	     sum = 0;
    	             sum = *it;
    	             count = 1;
    	             error = 0;
    	             lastgoodaverage=average = sum/count++;

    	             previouserror= error = pow(fabs(average - *it),2);

    	      	     MySegs.push_back(*TempSegHolder);
    	      	     TempSegHolder->clear();
   	              // add  as the first element of the next segment
   	        	     TempSegHolder->push_back(*it);

   	        	     AbsoluteErrors.push_back(fabs(sumofestimations-sumoforiginalTS));
   	        	     // restrart absolute error calculation
   	    	         sumoforiginalTS = *it;
   	    	         sumofestimations = (count - 1) * lastgoodaverage;
    	         }
       }


       if (!TempSegHolder->empty())
       {
    	         MySegs.push_back(*TempSegHolder);
    	         TempSegHolder->clear();
        	     Errors.push_back(sqrt(previouserror));
        	     Averages.push_back(lastgoodaverage);
        	     AbsoluteErrors.push_back(fabs(sumofestimations-sumoforiginalTS));
        	     ElementCountInSegment.push_back(count - 1);
       }
}

// to access the approximated value of the desired element at position index
double TimeSeries::GetDesiredApproxElementPAA(unsigned int positionindex)
{
    // assume approximation is already done

     std::vector<double>::iterator it2=Averages.begin() ;
     std::vector<double>::iterator it3=Errors.begin() ;
     std::vector<double>::iterator it4=AbsoluteErrors.begin() ;
    // std::vector<unsigned int>::iterator it4=ElementCountInSegment.begin();

    unsigned int absolute_index = 0;

 	for (std::vector<unsigned int>::iterator it1=ElementCountInSegment.begin();  it1 != ElementCountInSegment.end(); it1++)
 	{
             absolute_index += *it1;
             if (positionindex > absolute_index)
             {
            	    it2++;
            	    it3++;
            	    it4++;
             }
             else
            	    break;
 	}

 	cout << "the approximated average PAA value is = " << *it2 << " L2 Error = " << *it3 << " Absolute Error = " << *it4 << " for position index = " << positionindex << endl;

 	return *it2;

}

void TimeSeries::CalculatePLRError(double ActualValue, double Slope, double Count, double Constant, double& Error)
{
     // Error = actual value - (mx + b)
     Error += pow(fabs(ActualValue - (Slope * Count + Constant)),2);
}

void  TimeSeries::PLRbyLR(double MaxError)
{
    int i;
    std::vector<double> *TempSegHolder = new std::vector<double>();
    //std::vector<double> Errors;
    double average = 0;
    double count = 1;
    double error = 0;
    double sum = 0;
    double previouserror = 0;
    double End = 0;
    double Slope = 0;
    double Constant = 0;
    double SumX = 0;
    double SumY = 0;
    double SumXY = 0;
    double SumXSqr = 0;
    double SumYSqr = 0;
    double SampleSize = 0;
    double X = 1;
    LineParameters LastParams;
    double PreviousSumY = 0;
    double SumPLRApprox = 0;
    double PreviousSumPLRApprox = 0;
    unsigned int index = 1;
    unsigned int segindex = 1;
    MaxError = pow(MaxError,2); // compare against the squared value to make calculations easier


    std::vector<double>::iterator begit;
    std::vector<double>::iterator endit;
    std::vector<double>::iterator indexit;

    for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
    {
        //cout << "HERE" << *it << endl;
        if (count == 1)
        {

               begit = it;
               //indexit = begit;

        }
        else
        {
               End = *it;
               endit = it;

        }
        indexit = begit;//????
        error = 0; //????
        if (index % 1000 == 0)
            cout << "working on " << index << endl;
        index++;
        FindLineEquationByLR( X, *it, SumX, SumY,  SumXY,  SumXSqr,
            		 SumYSqr,  count,  Slope,  Constant);
        // cout << " y =" << Slope << "x+" << Constant << endl;
        if (count == 1)
        {
            Slope = 0;
            Constant = *it;
        }



        // if the next element is on the line do not calculate new equation as an optimization
           // previouserror = error;
        if (count > 2)
        {
             //calculate errors until count = 1, Begin.

        	     SumPLRApprox = 0;
        	     int internalcount = 1;
        	     while (indexit <= endit)
        	     {
        	    	// cout << "error (PRE) = " << error << endl;
        	     CalculatePLRError(*indexit, Slope, internalcount ,Constant, error);
        	     SumPLRApprox +=  Slope * internalcount + Constant;
                 internalcount++;
        	    //previouserror = error;
        	     //cout << "error (AFTER) = " << error << endl;
        	     indexit++;
        	     }
        }
      else
      {
    	  SumPLRApprox =  Slope * 1 + Constant;
    	  SumPLRApprox +=  Slope * 2 + Constant;
      }
        //cout << "previouserror = " << previouserror << endl;
        count++;
        X++;

        if (error > MaxError)
        {
        	 Errors.push_back(sqrt(previouserror));
        	 AbsoluteErrors.push_back(fabs(PreviousSumPLRApprox - PreviousSumY));
 	         MySegs.push_back(*TempSegHolder);
 	         TempSegHolder->clear();
 	         Lines.push_back(LastParams);
 	          ElementCountInSegment.push_back(count - 2); //XXX
 	         // add  as the first element of the next segment
	         TempSegHolder->push_back(*it);

       	     //if (segindex % 10== 0)
           cout << "new segment "  << segindex++ << endl;

	         indexit= begit = it; // for next error calculation

	         endit = it;

        	 count = 1;
        	 previouserror = error = 0;

             SumX = 0;

            // cout << "****************** SUM Y = " << PreviousSumY << endl;
            // cout << "****************** SUM PLR APPROX   = " << PreviousSumPLRApprox << endl;
             SumPLRApprox = 0;
             SumY = 0;
             SumXY = 0;
             SumXSqr = 0;
             SumYSqr = 0;
             SampleSize = 0;
             X = 1;

             FindLineEquationByLR( X, *it, SumX, SumY,  SumXY,  SumXSqr,
             		 SumYSqr,  count,  Slope,  Constant);

             if (count == 1)
             {
             	   Slope = 0;
             	   Constant = *it;
             }
            // cout << " y* =" << Slope << "x+" << Constant << endl;
             LastParams.Constant = Constant;
               	       LastParams.Slope = Slope;
             count++;
             X++;
        }
        else
        {
    	     TempSegHolder->push_back(*it);
    	     LastParams.Constant = Constant;
    	     LastParams.Slope = Slope;
    	     previouserror = error;
    	     PreviousSumY = SumY;
    	     PreviousSumPLRApprox = SumPLRApprox;
        }
    }

    if (!TempSegHolder->empty())
     {
  	         MySegs.push_back(*TempSegHolder);
  	         TempSegHolder->clear();
      	     Errors.push_back(sqrt(previouserror));
      	     Lines.push_back(LastParams);
      	     AbsoluteErrors.push_back(fabs(SumPLRApprox - SumY));
      	     ElementCountInSegment.push_back(count - 1); //XXX

    	    // cout << "****************** SUM Y [LAST CALL] = " << SumY << endl;
    	    // cout << "****************** SUM PLR APPROX  [LAST CALL] = " << SumPLRApprox << endl;
     }
}

void  TimeSeries::PLRbyLRIncremental(double MaxError)
{
    int i;
    std::vector<double> *TempSegHolder = new std::vector<double>();
    //std::vector<double> Errors;
    double average = 0;
    double count = 1;
    double error = 0;
    double sum = 0;
    double previouserror = 0;
    double End = 0;
    double Slope = 0;
    double Constant = 0;
    double SumX = 0;
    double SumY = 0;
    double SumXY = 0;
    double SumXSqr = 0;
    double SumYSqr = 0;
    double SampleSize = 0;
    double X = 1;
    LineParameters LastParams;
    double PreviousSumY = 0;
    double SumPLRApprox = 0;
    double PreviousSumPLRApprox = 0;
    MaxError = pow(MaxError,2); // compare against the squared value to make calculations easier


    std::vector<double>::iterator begit;
    std::vector<double>::iterator endit;
    std::vector<double>::iterator indexit;

    for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
    {
        //cout << "HERE" << *it << endl;
        if (count == 1)
        {

               begit = it;
               //indexit = begit;

        }
        else
        {
               End = *it;
               endit = it;

        }
        indexit = begit;//????
        //error = 0; //????

        FindLineEquationByLR( X, *it, SumX, SumY,  SumXY,  SumXSqr,
            		 SumYSqr,  count,  Slope,  Constant);
        // cout << " SUMY =" << SumY <<  "count = " << count << endl;
        if (count == 1)
        {
            Slope = 0;
            Constant = *it;
        }
      //  else
     //   {
     //       FindLineEquationByLR( X, *it, SumX, SumY,  SumXY,  SumXSqr,
     //           		 SumYSqr,  count,  Slope,  Constant);
     //        cout << " SUMY =" << SumY << "count = " << count << endl;
       // }

	     error +=  pow(fabs(*it - (Slope * count + Constant)),2);
	     SumPLRApprox +=  Slope * count + Constant;
	    // cout << " SumPLRApprox =" << SumPLRApprox << "count = " << count << endl;

        // if the next element is on the line do not calculate new equation as an optimization
           // previouserror = error;
       // if (count > 2)
     //   {
             //calculate errors until count = 1, Begin.

        	     //SumPLRApprox = 0;
        	    // int internalcount = 1;
        	   //  while (indexit <= endit)
        	   //  {

        	    // CalculatePLRError(*indexit, Slope, internalcount ,Constant, error);
        	   //  SumPLRApprox +=  Slope * internalcount + Constant;
                // internalcount++;

        	     //indexit++;
        	   // }
        	     //error +=  pow(abs(*it - (Slope * count + Constant)),2);
        	     //SumPLRApprox +=  Slope * count + Constant;
        	    // cout << " SumPLRApprox =" << SumPLRApprox << endl;
     //   }
     // else
     // {
    	 // SumPLRApprox =  Slope * 1 + Constant;
    	 // SumPLRApprox +=  Slope * 2 + Constant;
     // }

        //cout << "previouserror = " << previouserror << endl;
        count++;
        X++;

        if (error > MaxError)
        {
        	 Errors.push_back(sqrt(previouserror));
        	 AbsoluteErrors.push_back(fabs(PreviousSumPLRApprox - PreviousSumY));
        	  //cout << " PreviousSumPLRApprox =" << PreviousSumPLRApprox <<  "PreviousSumY = " << PreviousSumY << " abs(PreviousSumPLRApprox - PreviousSumY) = "<< fabs(PreviousSumPLRApprox - PreviousSumY) << endl;
 	         MySegs.push_back(*TempSegHolder);
 	         TempSegHolder->clear();
 	         Lines.push_back(LastParams);
 	          ElementCountInSegment.push_back(count - 2); //XXX
 	         // add  as the first element of the next segment
	         TempSegHolder->push_back(*it);

	         indexit= begit = it; // for next error calculation

	         endit = it;

        	 count = 1;
        	 previouserror = error = 0;
        	 PreviousSumPLRApprox = PreviousSumY = 0;
             SumX = 0;
             error =0;
            // cout << "****************** SUM Y = " << PreviousSumY << endl;
            // cout << "****************** SUM PLR APPROX   = " << PreviousSumPLRApprox << endl;
             SumPLRApprox = 0;
             SumY = 0;
             SumXY = 0;
             SumXSqr = 0;
             SumYSqr = 0;
             SampleSize = 0;
             X = 1;

             FindLineEquationByLR( X, *it, SumX, SumY,  SumXY,  SumXSqr,
             		 SumYSqr,  count,  Slope,  Constant);

             //cout << " SUMY =" << SumY <<  "count = " << count << endl;

             if (count == 1)
             {
             	   Slope = 0;
             	   Constant = *it;
             }
            // cout << " y* =" << Slope << "x+" << Constant << endl;
             LastParams.Constant = Constant;
               	       LastParams.Slope = Slope;


              	     error +=  pow(fabs(*it - (Slope * count + Constant)),2);
              	     SumPLRApprox +=  Slope * count + Constant;
              	     //cout << " SumPLRApprox =" << SumPLRApprox << "count = " << count << endl;


             count++;
             X++;
        }
        else
        {
    	     TempSegHolder->push_back(*it);
    	     LastParams.Constant = Constant;
    	     LastParams.Slope = Slope;
    	     previouserror = error;
    	     PreviousSumY = SumY;
    	     PreviousSumPLRApprox = SumPLRApprox;
        }
    }

    if (!TempSegHolder->empty())
     {
  	         MySegs.push_back(*TempSegHolder);
  	         TempSegHolder->clear();
      	     Errors.push_back(sqrt(previouserror));
      	     Lines.push_back(LastParams);
      	     AbsoluteErrors.push_back(fabs(SumPLRApprox - SumY));
      		 // cout << " PreviousSumPLRApprox =" << SumPLRApprox <<  "SumY = " << SumY << " abs(SumPLRApprox - SumY) = "<< fabs(SumPLRApprox - SumY) <<endl;
      	     ElementCountInSegment.push_back(count - 1); //XXX

    	    // cout << "****************** SUM Y [LAST CALL] = " << SumY << endl;
    	    // cout << "****************** SUM PLR APPROX  [LAST CALL] = " << SumPLRApprox << endl;
     }
}

// using regression
void TimeSeries::FindLineEquationByLR(double NewX, double NewY,double& SumX, double& SumY, double& SumXY, double& SumXSqr,
		double& SumYSqr, double& SampleSize, double& Slope, double& Constant)
{

     SumX+= NewX;
     SumY+= NewY;
     SumXY += (NewX * NewY);
     SumXSqr += pow(NewX, 2);
	 SumYSqr += pow(NewY, 2);

/*
	 cout << "NewX = "<< NewX << endl;
	 cout << "NewY = "<< NewY << endl;
	 cout << "SumX = "<< SumX << endl;
	 cout << "SumY = "<< SumY << endl;
	 cout << "SumXSqr= "<< SumXSqr << endl;
	 cout << "SumYSqr = "<< SumYSqr << endl;
	 cout << "SumXY = "<< SumXY << endl;
	 cout << "Sample Size = "<< SampleSize<< endl;
*/
	 Slope = ((SampleSize * SumXY) - (SumX * SumY))/ ((SampleSize * SumXSqr) - pow(SumX,2));
	 Constant = ((SumY * SumXSqr ) - (SumX * SumXY))/ ((SampleSize * SumXSqr) - pow(SumX,2));
}

void  TimeSeries::PLRFixedLength(unsigned int SegmentLength)
{
    int i;
    std::vector<double> *TempSegHolder = new std::vector<double>();
    //std::vector<double> Errors;
    double average = 0;
    double count = 1;
    double error = 0;
    double sum = 0;
    double previouserror = 0;
    double End = 0;
    double Slope = 0;
    double Constant = 0;
    double SumX = 0;
    double SumY = 0;
    double SumXY = 0;
    double SumXSqr = 0;
    double SumYSqr = 0;
    double SampleSize = 0;
    double X = 1;
    LineParameters LastParams;
    double PreviousSumY = 0;
    double SumPLRApprox = 0;
    double PreviousSumPLRApprox = 0;


    std::vector<double>::iterator begit;
    std::vector<double>::iterator endit;
    std::vector<double>::iterator indexit;

    for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
    {

        if (count == 1)
        {

               begit = it;


        }
        else
        {
               End = *it;
               endit = it;

        }
        indexit = begit;//????
        error = 0; //????



         FindLineEquationByLR( X, *it, SumX, SumY,  SumXY,  SumXSqr,
            		 SumYSqr,  count,  Slope,  Constant);
            //cout << " y =" << Slope << "x+" << Constant << endl;
         if (count == 1)
         {
            	   Slope = 0;
            	   Constant = *it;
         }



        if (count > 2)
        {
             //calculate errors until count = 1, Begin.

        	     SumPLRApprox = 0;
        	     int internalcount = 1;
        	     while (indexit <= endit)
        	     {

        	       CalculatePLRError(*indexit, Slope, internalcount ,Constant, error);
        	       SumPLRApprox +=  Slope * internalcount + Constant;
                   internalcount++;

        	       indexit++;
        	     }
        }
        else
        {
    	  SumPLRApprox =  Slope * 1 + Constant;
    	  SumPLRApprox +=  Slope * 2 + Constant;
        }

        count++;
        X++;


	    if (count - 1    > SegmentLength)

        {
        	 Errors.push_back(sqrt(previouserror));
        	 AbsoluteErrors.push_back(fabs(PreviousSumPLRApprox - PreviousSumY));
 	         MySegs.push_back(*TempSegHolder);
 	         TempSegHolder->clear();
 	         Lines.push_back(LastParams);
 	          ElementCountInSegment.push_back(count - 2); //XXX
 	         // add  as the first element of the next segment
	         TempSegHolder->push_back(*it);

	         indexit= begit = it; // for next error calculation
	         endit = it;
        	 count = 1;
        	 previouserror = error = 0;
        	 SumX = 0;
        	 //cout << "****************** SUM Y = " << PreviousSumY << endl;
        	 //cout << "****************** SUM PLR APPROX   = " << PreviousSumPLRApprox << endl;
        	 SumPLRApprox = 0;
             SumY = 0;
    	     SumXY = 0;
    	     SumXSqr = 0;
    	     SumYSqr = 0;
    	     SampleSize = 0;
    	     X = 1;

             FindLineEquationByLR( X, *it, SumX, SumY,  SumXY,  SumXSqr,
             		 SumYSqr,  count,  Slope,  Constant);

             if (count == 1)
             {
             	   Slope = 0;
             	   Constant = *it;
             }
             //cout << " y* =" << Slope << "x+" << Constant << endl;
             LastParams.Constant = Constant;
               	       LastParams.Slope = Slope;


    	     count++;
    	     X++;
        }
        else
        {
    	     TempSegHolder->push_back(*it);
    	     LastParams.Constant = Constant;
    	     LastParams.Slope = Slope;
             previouserror = error;
             PreviousSumY = SumY;
             PreviousSumPLRApprox = SumPLRApprox;
        }
    }

    if (!TempSegHolder->empty())
     {
  	         MySegs.push_back(*TempSegHolder);
  	         TempSegHolder->clear();
      	     Errors.push_back(sqrt(previouserror));
      	     Lines.push_back(LastParams);
      	     AbsoluteErrors.push_back(fabs(SumPLRApprox - SumY));
      	     ElementCountInSegment.push_back(count - 1);

    	     //cout << "****************** SUM Y [LAST CALL] = " << SumY << endl;
    	     //cout << "****************** SUM PLR APPROX  [LAST CALL] = " << SumPLRApprox << endl;
     }
}
void  TimeSeries::PLRFixedLength2(unsigned int SegmentLength)
{
    int i;
    std::vector<double> *TempSegHolder = new std::vector<double>();
    //std::vector<double> Errors;
    double average = 0;
    double count = 1;
    double error = 0;
    double sum = 0;
    double previouserror = 0;
    double End = 0;
    double Slope = 0;
    double Constant = 0;
    double SumX = 0;
    double SumY = 0;
    double SumXY = 0;
    double SumXSqr = 0;
    double SumYSqr = 0;
    double SampleSize = 0;
    double X = 1;
    LineParameters LastParams;
    double PreviousSumY = 0;
    double SumPLRApprox = 0;
    double PreviousSumPLRApprox = 0;


    std::vector<double>::iterator begit;
    std::vector<double>::iterator endit;
    std::vector<double>::iterator indexit;

    for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
    {

        if (count == 1)
        {

               begit = it;


        }
        else
        {
               End = *it;
               endit = it;

        }
        indexit = begit;//????
        error = 0; //????



         FindLineEquationByLR( X, *it, SumX, SumY,  SumXY,  SumXSqr,
            		 SumYSqr,  count,  Slope,  Constant);
            //cout << " y =" << Slope << "x+" << Constant << endl;
         if (count == 1)
         {
            	   Slope = 0;
            	   Constant = *it;
         }



        if (count > 2 && ((count == SegmentLength) || ((it +1 )==OriginalSeries.end() )))
        {

           // FindLineEquationByLR( X, *it, SumX, SumY,  SumXY,  SumXSqr,
             //  		 SumYSqr,  count,  Slope,  Constant);

             //calculate errors until count = 1, Begin.

        	     SumPLRApprox = 0;
        	     int internalcount = 1;
        	     while (indexit <= endit)
        	     {

        	       CalculatePLRError(*indexit, Slope, internalcount ,Constant, error);
        	       SumPLRApprox +=  Slope * internalcount + Constant;
                   internalcount++;

        	       indexit++;
        	     }
        }
        else if (count < 2)
        {
    	  SumPLRApprox =  Slope * 1 + Constant;
    	  SumPLRApprox +=  Slope * 2 + Constant;
        }

        count++;
        X++;


	    if (count - 1    > SegmentLength)

        {
        	 Errors.push_back(sqrt(previouserror));
        	 AbsoluteErrors.push_back(fabs(PreviousSumPLRApprox - PreviousSumY));
 	         MySegs.push_back(*TempSegHolder);
 	         TempSegHolder->clear();
 	         Lines.push_back(LastParams);
 	          ElementCountInSegment.push_back(count - 2); //XXX
 	         // add  as the first element of the next segment
	         TempSegHolder->push_back(*it);

	         indexit= begit = it; // for next error calculation
	         endit = it;
        	 count = 1;
        	 previouserror = error = 0;
        	 SumX = 0;
        	 //cout << "****************** SUM Y = " << PreviousSumY << endl;
        	 //cout << "****************** SUM PLR APPROX   = " << PreviousSumPLRApprox << endl;
        	 SumPLRApprox = 0;
             SumY = 0;
    	     SumXY = 0;
    	     SumXSqr = 0;
    	     SumYSqr = 0;
    	     SampleSize = 0;
    	     X = 1;

             FindLineEquationByLR( X, *it, SumX, SumY,  SumXY,  SumXSqr,
             		 SumYSqr,  count,  Slope,  Constant);

             if (count == 1)
             {
             	   Slope = 0;
             	   Constant = *it;
             }
             //cout << " y* =" << Slope << "x+" << Constant << endl;
             LastParams.Constant = Constant;
               	       LastParams.Slope = Slope;


    	     count++;
    	     X++;
        }
        else
        {
    	     TempSegHolder->push_back(*it);
    	     LastParams.Constant = Constant;
    	     LastParams.Slope = Slope;
             previouserror = error;
             PreviousSumY = SumY;
             PreviousSumPLRApprox = SumPLRApprox;
        }
    }

    if (!TempSegHolder->empty())
     {
  	         MySegs.push_back(*TempSegHolder);
  	         TempSegHolder->clear();
      	     Errors.push_back(sqrt(previouserror));
      	     Lines.push_back(LastParams);
      	     AbsoluteErrors.push_back(fabs(SumPLRApprox - SumY));
      	     ElementCountInSegment.push_back(count - 1);

    	     //cout << "****************** SUM Y [LAST CALL] = " << SumY << endl;
    	     //cout << "****************** SUM PLR APPROX  [LAST CALL] = " << SumPLRApprox << endl;
     }
}
//dumps all the calculates values for PAA approx
void TimeSeries::DebugPrintAllPAA()
{
     std::vector<double>::iterator it4=Averages.begin() ;
     std::vector<double>::iterator it5=Errors.begin() ;
     std::vector<double>::iterator it7=AbsoluteErrors.begin() ;
     std::vector<unsigned int>::iterator it8=ElementCountInSegment.begin();
     unsigned int counter = 1;

     for (Segs::iterator it1 = MySegs.begin(); it1 != MySegs.end(); it1++)
     {
       cout << "============SEGMENT START===== " << counter++ << endl;
  	   for (std::vector<double>::iterator it2=it1->begin() ; it2 != it1->end(); it2++)
  	   {
              cout << " original value  = " << *it2 << endl;
  	   }
       cout << "seg approximated value = " << *it4 << endl;
       it4++;
       cout << "seg L2 error = " << *it5 << endl;
       it5++;
       cout << "seg absolute error = " << *it7 << endl;
       it7++;
       cout << "seg element count = " << *it8 << endl;
       it8++;

       cout << "===============SEGMENT END =====" << endl;
     }
     // they better be the same. for each segment there's an average value and 2 error params
     cout << " segment count = " << Averages.size() << " " << AbsoluteErrors.size() << " "<<Errors.size() << endl;
}
double TimeSeries::GetAverageErrors()
{
    double sum = 0;
	std::vector<double>::iterator it5=Errors.begin();
	std::vector<double>::iterator limit;
	if (Errors.size() == 1)
		limit = Errors.end();
	else
		limit = Errors.end() - 1;

    for (; it5 != limit ; it5++)
	sum +=*it5;

	cout << " Average Error = " << sum/Errors.size() << endl;

	return sum/Errors.size();
}

//clean all the vectors except the original series
void TimeSeries::CleanUp()
{
   for (Segs::iterator it1 = MySegs.begin(); it1 != MySegs.end(); it1++)
      (*it1).clear();
   MySegs.clear();
   Errors.clear();
   AbsoluteErrors.clear();
   Averages.clear();
   ElementCountInSegment.clear();
   Lines.clear();

}

//dumps all the calculates values for PLR approx
void TimeSeries::DebugPrintAllPLR()
{

     std::vector<double>::iterator it5=Errors.begin() ;
     std::vector<double>::iterator it7=AbsoluteErrors.begin() ;
     std::vector<unsigned int>::iterator it8=ElementCountInSegment.begin();
     std::vector<LineParameters>::iterator it9= Lines.begin();
     unsigned int counter = 1;

     for (Segs::iterator it1 = MySegs.begin(); it1 != MySegs.end(); it1++)
     {
       cout << "============SEGMENT START===== " << counter++ << endl;
  	   for (std::vector<double>::iterator it2=it1->begin() ; it2 != it1->end(); it2++)
  	   {
              //cout << " original value  = " << *it2 << endl;
  	   }

       cout << "seg L2 error = " << *it5 << endl;
       it5++;
       cout << "seg absolute error = " << *it7 << endl;
       it7++;
       cout << "seg element count = " << *it8 << endl;
       it8++;
       cout << " line params: slope = "  << (*it9).Slope  <<  "constant = " << (*it9).Constant << endl;
       it9++;
       cout << "===============SEGMENT END =====" << endl;
     }
     // they better be the same. for each segment there's an average value and 2 error params
     cout << " segment count = " << Lines.size() << " " << AbsoluteErrors.size() << " "<<Errors.size() << endl;
}
// to access the approximated value of the desired element at position index
double TimeSeries::GetDesiredApproxElementPLR(unsigned int positionindex)
{
    // assume approximation is already done

     std::vector<LineParameters>::iterator it2=Lines.begin() ;
     std::vector<double>::iterator it3=Errors.begin() ;
     std::vector<double>::iterator it4=AbsoluteErrors.begin() ;
    // std::vector<unsigned int>::iterator it4=ElementCountInSegment.begin();

    unsigned int absolute_index = 0;
    unsigned int relative_index = 0; // in the segment
    double   value = 0;
 	for (std::vector<unsigned int>::iterator it1=ElementCountInSegment.begin();  it1 != ElementCountInSegment.end(); it1++)
 	{
             absolute_index += *it1;
             if (positionindex > absolute_index)
             {
            	    it2++;
            	    it3++;
            	    it4++;
             }
             else
             {
            	 absolute_index -= *it1;
            	    break;
             }
 	}

 	relative_index = positionindex - absolute_index;

 	value = (*it2).Slope *  relative_index + (*it2).Constant ;
 	cout << "the approximated PLR value is = " << value << " L2 Error = " << *it3 << " Absolute Error = " << *it4 << " for position index = " << positionindex << endl;
 	cout << "the Slope = " << (*it2).Slope << " the Constant = " << (*it2).Constant << endl;
 	cout << " relative index  = " << relative_index << endl;

 	return value;
}

// write all the appoximated PLR values to a file
void TimeSeries::WriteAllElementsPLR()
{
    // assume approximation is already done

     std::vector<LineParameters>::iterator it2=Lines.begin() ;
     std::vector<double>::iterator it3=Errors.begin() ;
     std::vector<double>::iterator it4=AbsoluteErrors.begin() ;
    // std::vector<unsigned int>::iterator it4=ElementCountInSegment.begin();

    unsigned int absolute_index = 0;
    unsigned int relative_index = 0; // in the segment
    double   value = 0;


    ofstream myfile ("PLRout.txt");

 	for (std::vector<unsigned int>::iterator it1=ElementCountInSegment.begin();  it1 != ElementCountInSegment.end(); it1++)
 	{
          for (int i = 1; i <= *it1; i++)
          {
        	      value =  (*it2).Slope *  i + (*it2).Constant;



        	        myfile << value << " ";

          }
          it2++;
 	}

    myfile.close();

}

// write all the appoximated PAA values to a file
void TimeSeries::WriteAllElementsPAA()
{
    // assume approximation is already done

     std::vector<double>::iterator it2=Averages.begin() ;

    double   value = 0;


    ofstream myfile ("PAAout.txt");

 	for (std::vector<unsigned int>::iterator it1=ElementCountInSegment.begin();  it1 != ElementCountInSegment.end(); it1++)
 	{
          for (int i = 1; i <= *it1; i++)
          {
        	      value =  *it2;
        	      myfile << value << " ";
          }
          it2++;
 	}

    myfile.close();

}

};
