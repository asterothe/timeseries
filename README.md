# timeseries approximation



Data Source Files:

The program assumes we have an input cvs file. (right now file3.csv)
The TS() Constructor parses the comma separated values. In the current example the format expects to have 15 columns for each 
time stamp. Right now it parses and saves the 3rd parameter in the OriginalSeries vector. It also needs to have quotes before and after the data points. fscanf parameters needs to be modified for other data input files.

En example line from csv: 
"LAJ00572","2015-09-09 16:51:54.105","53283114","0","1.0","456.0","1.0","689.4375","0.0","21.9","594.375","90.15625","78.98901098901099","0","0"

3rd float i.e. "456.0" is pushed to the vector. Mind the "s between values.



In the main 

for PAA Approximations 

1) PAAFixedLength(SegmentLength) : Creates as many segments as necessary of equal SegmentLenght size using PAA method for appoximation. (Averages)  Saves the average value in Averages vector. Also L2 errors is saved in Errors vector and the difference between the sum of estimated values vs actual values are saved in  AbsoluteErrors vector. ElementCountInSegment vector keeps track of the number of elements in each segment. 

2) PAA(MaxError) : Creates as many segments as necessary making sure that the L2 errors do not exceept the MaxError (L2) parameter using PAA and SW method for approximations. (Averages) Also L2 errors is saved in Errors vector and the difference between the sum of estimated values vs actual values are saved in  AbsoluteErrors vector. ElemtCountInSegment vector keeps track of the number of elements in each segment. 


for PRR Approximations 

1)PLRFixedLength(SegmentLength) : Creates as many segments as necessary of equal SegmentLenght size using PAA method for appoximation. (Linear Regression - 1st degree polynomials)  Saves the line's equation parameters in Lines vector. Also L2 errors is saved in Errors vector and the difference between the sum of estimated values vs actual values are saved in  AbsoluteErrors vector. ElementCountInSegment vector keeps track of the number of elements in each segment. 

2) PLRbyLR(MaxError) : Creates as many segments as necessary making sure that the L2 errors do not exceept the MaxError (L2) parameter using PLR and SW method for approximations. (Linear Regression - 1st degree polynomials) Saves the line's equation parameters in Lines vector. Also L2 errors is saved in Errors vector and the difference between the sum of estimated values vs actual values are saved in  AbsoluteErrors vector. ElementCountInSegment vector keeps track of the number of elements in each segment. 

Helper Functions:

GetDesiredApproxElementPAA(positionindex) : Accesses the desired approximated value  for PAA approximations. Can only be called after a PAA approximation is done. 

GetDesiredApproxElementPLR(positionindex) :  Accesses the desired approximated value  for PLR approximations. Can only be called after a PLR approximation is done. 

DebugPrintAllPAA(): Dumps out all created segments showing the original time series elements for the segment and saved error and appriximation parameters. Can only be called after a PAA approximation is done. 

DebugPrintAllPLR(): Dumps out all created segments showing the original time series elements for the segment and saved error and appriximation parameters. Can only be called after a PLR approximation is done. 


Cleanup: Needs to be called between approximations to do house cleaning.
GetAverageErrors(): provides the avergae L2 error after an approximation is done. 

An example of PAA Approximation:

       TimeSeries TS; // constructor parses the cvs file into vector
       
       // make PAA with fixed length 100. Original series has 500k elements.
       TS.PAAFixedLength(100);

       // there will be 500000/100 = 5000 segments
       TS.DebugPrintAllPAA();


       // print out 3000th approximated element
       TS.GetDesiredApproxElementPAA(3000);
       // get the average error using FL segmentation
       double average_error = TS.GetAverageErrors(); //2.29775 in this example

   
       TS.CleanUp();

       // make PAA SW approx using average Errors of previous FL segmentation
       //TS.PAA(average_error);  // produces 375940 segments

       //TS.DebugPrintAllPAA();
       // print out 3000th appoximated element again
       TS.GetDesiredApproxElementPAA(3000);


An example of PLR Approximation:
       
       
       TimeSeries TS; // constructor parses the cvs file into vector
       
       TS.PLRFixedLength(1000);  // 500 segments with 1000 data points
       TS.DebugPrintAllPLR();
       TS.GetDesiredApproxElementPLR(2); // get 2nd element

       double average_error = TS.GetAverageErrors(); //908.49 in this example
       TS.CleanUp();
       TS.PLRbyLR(average_error); // PLR SW approx with threshold 908.49

       TS.DebugPrintAllPLR();  //19683 segments generated

       TS.GetDesiredApproxElementPLR(10000); //get 10000th element
       
       
