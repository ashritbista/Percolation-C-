/*
* disjoint_sets.cpp
*
*  Created on: Nov 2, 2016
*      Author: Ashrit
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "percolation.h"

using namespace std;

//This function will calculate the mean of all the ratios
//of the open cells
//formula = (x_1 + x_2 +........+x_n)/n
void findMean(int trials, double *ratio, double &mean)
{
	double sum = 0;
	for (int i = 0; i < trials; i++)
	{
		sum = sum + ratio[i];
	}
	mean = sum / (double)trials;
}

//this function calculates the the variance of the ratios
//utilizing the mean from above function
//formula = sqrt(((x_1 - mean)^2 + (x_2 - mean)^2 +..........+(x_n - mean)^2)/(n-1))
void Variance(int trials, double *ratio, double mean, double &sampleVar)
{
	double sum = 0;

	for (int i = 0; i < trials; i++)
	{
		sum = sum + pow((ratio[i] - mean), 2);
	}
	sampleVar = sum / (double)(trials - 1);
	sampleVar = sqrt(sampleVar);
}

//At the beginning of the program this function will
//ask for the users value to be used in the process
void getUserinputs(int &dimension, int &trials, char &answer)
{
	cout << "Enter the dimension of the grid: " << endl;;
	cin >> dimension;
	cout << endl;
	cout << "Enter # of trials to perform: " << endl;
	cin >> trials;
	cout << "Show final grid? (y/n): ";
	cin >> answer;
	cout << endl;
}

//most of the data processing is carried out in this function
int main()
{
	int n, trials, count = 0, openCount = 0;
	char answer;

	getUserinputs(n, trials, answer);

	double *ratio = new double[trials];
	double item = 0, sampleVar = 0, mean = 0,
		confiInterval1 = 0, confiInterval2 = 0;

	//initialize random number generator
	srand(time(NULL));
	percolation system(n);

	int row_val = 0, col_val = 0;

	//now we will loop the logic of finding
	//if a system percolates or not. This will
	//loop until the total number of trials
	while (count < trials)
	{
		row_val = rand() % n;
		col_val = rand() % n;

		system.open(row_val, col_val);

		//if the system percolates
		if (system.percolates())
		{
			openCount = system.getOpenCellCount();
			item = (double)openCount / (double)(n * n);
			ratio[count] = item;

			cout << "Trial: " << count << " ";
			cout << "N: " << n << " ";
			cout << "open count: " << openCount << " " << "ratio: ";
			cout << ratio[count] << endl;
			cout << endl;
			//we increment the count for the next iteration
			count++;

			//if the last iteration is done break out of the loop
			if (count == trials)
				break;

			//if not we reset the grid and the sets used in the percolation class
			//this is done by the class provided in the header file "percolation.h"
			else
				system.resetGrid();
		}
	}

	//we now call the function to calculate
	//the mean and sample variance
	findMean(trials, ratio, mean);
	Variance(trials, ratio, mean, sampleVar);


	//this is where the confidence interval is calculated
	confiInterval1 = mean - (1.96 * sampleVar) / sqrt((double)trials);
	confiInterval2 = mean + (1.96 * sampleVar) / sqrt((double)trials);

	cout << "Here is the confidence interval: " << '(' << confiInterval1;
	cout << ", " << confiInterval2 << ')' << endl;

	if (answer == 'y')
		system.showFinalVisualization();

	//delete the pointer to an array as we are done
	//using it
	delete[] ratio;
	return 0;
}
