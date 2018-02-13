/*
 * approximate.cpp
 *
 *  Created on: Oct 25, 2017
 *      Author: korhan
 */




#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <time.h>
#include <sys/time.h>
#include "TimeSeries.h"


#define NUM_THREADS 4

using namespace ApproPlato;
using namespace std;

int main(void)
{

       TimeSeries TS;


       struct timeval tval_before, tval_after, tval_result;

       gettimeofday(&tval_before, NULL);





/*
       time_t timer;
       char buffer[26];
       struct tm* tm_info;

       time(&timer);
       tm_info = localtime(&timer);

       strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
       puts(buffer);
*/
       // make PAA with fixed length 100. Original series has 500k elements.
       //TS.PAAFixedLength(86400);
       TS.PAAIncremental(41.11);

       gettimeofday(&tval_after, NULL);

       timersub(&tval_after, &tval_before, &tval_result);

       printf("Time elapsed: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
/*
       time(&timer);
       tm_info = localtime(&timer);

       strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
       puts(buffer);

*/
       //TS.PAA(3);
       // there will be 500000/100 = 5000 segments
       //TS.DebugPrintAllPAA();

       TS.WriteAllElementsPAA();
       double average_error = TS.GetAverageErrors();
       //TS.CleanUp();
       //TS.PAAIncremental(2);
       //TS.GetDesiredApproxElementPAA(3000);

       //double average_error = TS.GetAverageErrors(); //2.29775 in this example

       //TS.CleanUp();

       // make PAA approx using average Errors of previous FL segmentation
       //TS.PAA(average_error);  // produces 375940 segments

       //TS.DebugPrintAllPAA();

       //TS.GetDesiredApproxElementPAA(3000);

       //TS.PLRbyLR(2);
      // TS.PLRFixedLength(1000);  // 500 segments with 1000 data points
       //TS.DebugPrintAllPLR();
      // TS.GetDesiredApproxElementPLR(2);

      // TS.GetDesiredApproxElementPLR(8);
      // double average_error = TS.GetAverageErrors(); //908.49 in this example
       //TS.CleanUp();
       //TS.PLRbyLR(25);
       //TS.WriteAllElementsPLR();
       //TS.DebugPrintAllPLR();  //19683 segments generated


	   return EXIT_SUCCESS;
}
