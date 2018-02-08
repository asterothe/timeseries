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



// assumes file3.csv is available. this time we create a time series using the 3rd float parameter which
// is ENGINE SPEED. this is the largest csv file of LAJ00508_part4.cvs minus the first line with column names
// removed. it has 500000 rows therefore the len of the time series is 500000.
TimeSeries::TimeSeries()
{


   float f1, f2, f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14;
   char str1[100], str2[100], str3[100];
    FILE *fp;
    fp = fopen("file3.csv", "r");
    while (fscanf(fp, "\"%8s\",\"%10s %12s\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\",\"%g\"\n",
		  str1, str2, str3, &f1, &f2, &f3, &f4 ,&f5, &f6,&f7, &f8,&f9, &f10,&f11, &f12,&f13) == 16)
    {
       //printf("%g %g %g %g \n", f1, f2, f3, f4);
        OriginalSeries.push_back(f3);
    }
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
  	         average = sum/count;
	         std::vector<double>::iterator it2 = it;
  	         int index = (int) count;
  	         error = 0;
  	         while(index)
  	         {
  	        	     error += abs(average- *it2);
  	        	     index--;
  	        	     it2--;
  	         }

  	         if (count   <= SegmentLength)
  	         {

  	              // add to the segment
  	        	     TempSegHolder->push_back(*it);
  	        	     lastgoodaverage = average;
  	        	     previouserror = error;
  	    	         sumoforiginalTS += *it;
  	    	         sumofestimations  = (count ) * lastgoodaverage;
  	         }
  	         else // NEW SEGMENT
  	         {
  	        	     Errors.push_back(previouserror);
  	        	     Averages.push_back(lastgoodaverage);
  	        	     ElementCountInSegment.push_back(count - 1);
  	        	      // reset average count error new segment
  	        	     sum = 0;
  	             sum = *it;
  	             count = 1;
  	             lastgoodaverage=average = sum/count;
  	             previouserror= error = abs(average - *it);
  	      	     MySegs.push_back(*TempSegHolder);
  	      	     TempSegHolder->clear();
 	              // add  as the first element of the next segment
 	        	     TempSegHolder->push_back(*it);

 	        	     AbsoluteErrors.push_back(abs(sumofestimations-sumoforiginalTS));
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
      	     Errors.push_back(previouserror);
      	     Averages.push_back(lastgoodaverage);
      	     AbsoluteErrors.push_back(abs(sumofestimations-sumoforiginalTS));
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
       for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
       {

    	         sum += *it;
    	         average = sum/count++;

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
    	        	     Errors.push_back(previouserror);
    	        	     Averages.push_back(lastgoodaverage);
    	        	     ElementCountInSegment.push_back(count - 2);

    	        	      // reset average count error new segment
    	        	     sum = 0;
    	             sum = *it;
    	             count = 1;
    	             lastgoodaverage=average = sum/count++;

    	             previouserror= error = abs(average - *it);

    	      	     MySegs.push_back(*TempSegHolder);
    	      	     TempSegHolder->clear();
   	              // add  as the first element of the next segment
   	        	     TempSegHolder->push_back(*it);

   	        	     AbsoluteErrors.push_back(abs(sumofestimations-sumoforiginalTS));
   	        	     // restrart absolute error calculation
   	    	         sumoforiginalTS = *it;
   	    	         sumofestimations = (count - 1) * lastgoodaverage;
    	         }
       }


       if (!TempSegHolder->empty())
       {
    	         MySegs.push_back(*TempSegHolder);
    	         TempSegHolder->clear();
        	     Errors.push_back(previouserror);
        	     Averages.push_back(lastgoodaverage);
        	     AbsoluteErrors.push_back(abs(sumofestimations-sumoforiginalTS));
        	     ElementCountInSegment.push_back(count - 1);
       }
}

void  TimeSeries::PLR(double MaxError)
{
    int i;
    std::vector<double> *TempSegHolder = new std::vector<double>();
    std::vector<double> Errors;
    //std::vector<double> Averages;
    //std::vector<LineParameters> Lines;   // hold line equations for good approximations

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
    LineParameters LastParams;
    std::vector<double>::iterator begit;
    std::vector<double>::iterator endit;
    std::vector<double>::iterator indexit;

    for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
    {
       // cout << "HERE" <<endl;
        if (count == 1)
        {
               Begin = *it;
               begit = it;
               indexit = begit;
               Slope = 0;
               Constant = *it;
               //cout << "HERE 2" <<endl;
        }
        else
        {
               End = *it;
               endit = it;
               //cout << "HERE 3" <<endl;
        }

        if(count > 1)
        {
            cout << " begin =" << Begin <<  "end = " << End <<"count = " << count << endl;
            FindLineEquation(Begin, 1, End, count , Slope, Constant);
            cout << " y =" << Slope << "x+" << Constant << endl;
            //cout << "HERE 4" <<endl;
        }
        // if the next element is on the line do not calculate new equation as an optimization

        if (count > 2)
        {
             //calculate errors until count = 1, Begin.
        	 //cout << "HERE 5" <<endl;

        	     int internalcount = 1;
        	     while (indexit != endit)
        	     {

        	     CalculatePLRError(*indexit, Slope, internalcount++ ,Constant, error);
        	     cout << "error = " << error << endl;
        	     indexit++;
        	     }
        }



        if (error > MaxError)
        {


   	         Errors.push_back(previouserror);

             previouserror = error = 0;
             //CalculatePLRError(*it, Slope, internalcount++ ,Constant, error);
 	         MySegs.push_back(*TempSegHolder);
 	         TempSegHolder->clear();
 	         Lines.push_back(LastParams);
             // add  as the first element of the next segment
  	         TempSegHolder->push_back(*it);
  	         Constant = *it;
  	         Slope = 0;

        	     count = 1;

        }
        else
        {

   	       TempSegHolder->push_back(*it);
   	       LastParams.Constant = Constant;
   	       LastParams.Slope = Slope;
   	       previouserror = error;
        }

        count++;
    }
    if (!TempSegHolder->empty())
    {
 	         MySegs.push_back(*TempSegHolder);
 	         TempSegHolder->clear();
     	     Errors.push_back(previouserror);
     	     Lines.push_back(LastParams);
    }

    cout << " Approx Line equations  = " << endl;
    for (std::vector<LineParameters>::iterator it=Lines.begin() ; it != Lines.end(); it++)
	{
         cout << "C =  " << it->Constant << " m =  " << it->Slope << endl;
	}
	for (std::vector<double>::iterator it3=Errors.begin() ; it3 != Errors.end(); it3++)
	{
            cout << " Error  = " << *it3 << endl;
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


//using linear interpolation
void TimeSeries::FindLineEquation(double BeginY, double BeginX, double EndY, double EndX ,double& Slope, double& Constant)
{
     Slope = (EndY - BeginY)/ (EndX-BeginX);  // m = rise / run
     Constant = BeginY - BeginX  * Slope;      // b = y - mx
}



void TimeSeries::CalculatePLRError(double ActualValue, double Slope, double Count, double Constant, double& Error)
{
     // Error = actual value - (mx + b)
     Error += abs(ActualValue - (Slope * Count + Constant));
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


    std::vector<double>::iterator begit;
    std::vector<double>::iterator endit;
    std::vector<double>::iterator indexit;

    for (std::vector<double>::iterator it = OriginalSeries.begin(); it != OriginalSeries.end(); it++)
    {
        cout << "HERE" << *it << endl;
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
     //   if ( count > 1)
      //  {



            FindLineEquationByLR( X, *it, SumX, SumY,  SumXY,  SumXSqr,
            		 SumYSqr,  count,  Slope,  Constant);
            cout << " y =" << Slope << "x+" << Constant << endl;
            if (count == 1)
            {
            	   Slope = 0;
            	   Constant = *it;
            }
      //  }


        // if the next element is on the line do not calculate new equation as an optimization

        if (count > 2)
        {
             //calculate errors until count = 1, Begin.

        	previouserror = error;
        	     int internalcount = 1;
        	     while (indexit <= endit)
        	     {
        	    	 cout << "error (PRE) = " << error << endl;
        	     CalculatePLRError(*indexit, Slope, internalcount++ ,Constant, error);
        	    //previouserror = error;
        	     cout << "error (AFTER) = " << error << endl;
        	     indexit++;
        	     }
        }
        else
        	 previouserror = error = 0;

        cout << "previouserror = " << previouserror << endl;
        count++;
        X++;

        if (error > MaxError)
        {
        	 Errors.push_back(previouserror);
 	         MySegs.push_back(*TempSegHolder);
 	         TempSegHolder->clear();
 	         Lines.push_back(LastParams);

 	         // add  as the first element of the next segment
	         TempSegHolder->push_back(*it);

	        indexit= begit = it; // for next error calculation

	         endit = it;



        	     count = 1;
        	     previouserror = error = 0;




        	     SumX = 0;
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
                 cout << " y* =" << Slope << "x+" << Constant << endl;
                 LastParams.Constant = Constant;
                   	       LastParams.Slope = Slope;

        	     int internalcount = 1;
        	     count++;
        	     X++;


        }
        else
        {
    	       TempSegHolder->push_back(*it);
    	       LastParams.Constant = Constant;
    	       LastParams.Slope = Slope;
    	       previouserror = error;
        }

        /*
                 if (error > MaxError)
        {


   	         Errors.push_back(previouserror);

             previouserror = error = 0;
             //CalculatePLRError(*it, Slope, internalcount++ ,Constant, error);
 	         MySegs.push_back(*TempSegHolder);
 	         TempSegHolder->clear();
 	         Lines.push_back(LastParams);
             // add  as the first element of the next segment
  	         TempSegHolder->push_back(*it);
  	         Constant = *it;
  	         Slope = 0;

        	     count = 1;

        }
        else
        {

   	       TempSegHolder->push_back(*it);
   	       LastParams.Constant = Constant;
   	       LastParams.Slope = Slope;
   	       previouserror = error;
        }


         */



    }

    if (!TempSegHolder->empty())
     {
  	         MySegs.push_back(*TempSegHolder);
  	         TempSegHolder->clear();
      	     Errors.push_back(previouserror);
      	     Lines.push_back(LastParams);
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


	 cout << "NewX = "<< NewX << endl;
	 cout << "NewY = "<< NewY << endl;
	 cout << "SumX = "<< SumX << endl;
	 cout << "SumY = "<< SumY << endl;
	 cout << "SumXSqr= "<< SumXSqr << endl;
	 cout << "SumYSqr = "<< SumYSqr << endl;
	 cout << "SumXY = "<< SumXY << endl;
	 cout << "Sample Size = "<< SampleSize<< endl;

	 Slope = ((SampleSize * SumXY) - (SumX * SumY))/ ((SampleSize * SumXSqr) - pow(SumX,2));
	 Constant = ((SumY * SumXSqr ) - (SumX * SumXY))/ ((SampleSize * SumXSqr) - pow(SumX,2));
}


//dumps all the calculates values for PAA approx
void TimeSeries::DebugPrintAllPAA()
{
     std::vector<double>::iterator it4=Averages.begin() ;
     std::vector<double>::iterator it5=Errors.begin() ;
     std::vector<double>::iterator it7=AbsoluteErrors.begin() ;
     std::vector<unsigned int>::iterator it8=ElementCountInSegment.begin();

     for (Segs::iterator it1 = MySegs.begin(); it1 != MySegs.end(); it1++)
     {
       cout << "============SEGMENT START=====" << endl;
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
     //std::vector<double>::iterator it4=Averages.begin() ;
     std::vector<double>::iterator it5=Errors.begin() ;
     //std::vector<double>::iterator it7=AbsoluteErrors.begin() ;
     //std::vector<unsigned int>::iterator it8=ElementCountInSegment.begin();
     std::vector<LineParameters>::iterator it9= Lines.begin();

     for (Segs::iterator it1 = MySegs.begin(); it1 != MySegs.end(); it1++)
     {
       cout << "============SEGMENT START=====" << endl;
  	   for (std::vector<double>::iterator it2=it1->begin() ; it2 != it1->end(); it2++)
  	   {
              cout << " original value  = " << *it2 << endl;
  	   }
  /*     cout << "seg approximated value = " << *it4 << endl;
       it4++;
       cout << "seg L2 error = " << *it5 << endl;
       it5++;
       cout << "seg absolute error = " << *it7 << endl;
       it7++;
       cout << "seg element count = " << *it8 << endl;
       it8++;
*/

       cout << "seg L2 error = " << *it5 << endl;
       it5++;
      cout << " line param slope = "  << (*it9).Slope  <<  "constant = " << (*it9).Constant << endl;
       it9++;
       cout << "===============SEGMENT END =====" << endl;
     }
     // they better be the same. for each segment there's an average value and 2 error params
     cout << " segment count = " << Lines.size() << " " << AbsoluteErrors.size() << " "<<Errors.size() << endl;
}

};


