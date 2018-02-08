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
#include "TimeSeries.h"


#define NUM_THREADS 4

using namespace ApproPlato;
using namespace std;

int main(void)
{

       TimeSeries TS;

       // make PAA with fixed length 100. Original series has 500k elements.
       //TS.PAAFixedLength(100);

       // there will be 500000/100 = 5000 segments
       //TS.DebugPrintAllPAA();



       //TS.GetDesiredApproxElementPAA(3000);

       //double average_error = TS.GetAverageErrors(); //2.29775 in this example

       //TS.CleanUp();

       // make PAA approx using average Errors of previous FL segmentation
       //TS.PAA(average_error);  // produces 375940 segments

       //TS.DebugPrintAllPAA();

       //TS.GetDesiredApproxElementPAA(3000);

       TS.PLRbyLR(2);
       TS.DebugPrintAllPLR();

	   return EXIT_SUCCESS;
}

