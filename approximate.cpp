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

       //TS.PAA(3);

       //TS.PLR(5);
       //TS.PLRbyLR(5);

      // cout <<" XXXXXXXXXXXXXXXXX   Linear Interpolation   XXXXXXXXXXX" << endl;
       //TS.PLR(5);

       TS.PAA(10);



	   return EXIT_SUCCESS;
}

