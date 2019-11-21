//Jack Carroll - NQueens Problem

#include <bits/stdc++.h>

using namespace std;

int findQueens(int n, int r, vector<int>& down, vector<int>& up, vector<int>& cols) {
    if (n == r) { return 1; }
    int sum = 0;
    for (int c = 0; c < n; c++) {
        if (!down[r + c] && !up[n + r - c - 1] && !cols[c]) {
            down[r + c] = up[n + r - c - 1] = cols[c] = 1;
            sum += findQueens(n, r + 1, down, up, cols);
            down[r + c] = up[n + r - c - 1] = cols[c] = 0;
        }
    }
    return sum;
}

int nQueens(int n)
{
    vector<int> down(2 * n - 1), up(2 * n - 1), cols(n);
    return findQueens(n, 0, down, up, cols);
}

int main(int argc, char *argv[]) {

	//error checking
	if (argc != 2) { 
		cout << "Error: Format to run is ./queens <number of queens>" << endl;
		return 1;
	}

	//convert string to integer
	int queens = atoi(argv[1]);

	//get number of solutions
	int numSolutions = NQueens(queens);

	//print solutions
	cout << "There are " << numSolutions << " solutions to the " << queens << "-Queens Problem" << endl;

	return 0;
}
