//Jack Carroll - Traveling Salesman

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

//constant number of cities
const int numCities = 50;

//point struct
struct Points {
	double x, y;
};

Points p[numCities];

//function that finds length of tour
double tourLength(int *tour) {

	double length = 0.0;
	for (int i = 0; i < numCities; i++) {
		double xdis = p[tour[i]].x - p[tour[(i + 1) % numCities]].x;
		double ydis = p[tour[i]].y - p[tour[(i + 1) % numCities]].y;
		length += sqrt(pow(xdis, 2) + pow(ydis, 2));
	}
	return length;
}

//function randomly swaps tours
void randomSwap(int *tour) {

	for (int i = 0; i < numCities; i++) {
		tour[i] = i;
		swap(tour[i], tour[rand() % (i+1)]);
	}
}

//function that reverses tours
void tourReversal(int *tour, int a, int b) {

	if (a >= b) { return; }
	swap(tour[a], tour[b]);
	tourReversal(tour, a+1, b-1);
}

//function that prunes the tour
bool pruneTour(int *tour) {

	double lastLength = tourLength(tour);
	for (int a = 0; a < numCities; a++) {
		for (int b = numCities - 1; b >= 0; b--) {
			tourReversal(tour, a+1, b-1);
			if (tourLength(tour) < lastLength) { return true; }
			tourReversal(tour, a+1, b-1);
		}
	}
	return false;
}

//this function finds best tour and takes in a pointer for tour length so it doesnt return anything
void getBest(int *best, int *last, double *length) {

	for (int i = 0; i < 150; i++) {
		randomSwap(last);
		while (pruneTour(last)) {
			if (tourLength(last) < (*length)) {
				*length = tourLength(last);
				copy(last, last + numCities, best);
			}
		}
	}
}

int main (void) {

	//read in points
	ifstream input("tsp_points.txt");
	for (int i = 0; i < numCities; i++) {
		input >> p[i].x >> p[i].y;
	}
	input.close();

	//initalize best length to some extremely high number
	double bestLength = 999999.0;

	//finds best tour and best tour length
	int best[numCities], last[numCities];
	getBest(best, last, &bestLength);

	//prints out results
	cout << "Best length for tour: " << bestLength << endl;
	for (int i = 0; i < numCities; i++) {
		cout << " " << best[i];
	}
	cout << endl;

	return 0;
}
