//Jack Carroll - Using KD Tree for Predictions of Wines

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N; //number of data points
int D; //number of dimensions of each point
int K; //command line input of number of neighbors
double A = 0.1; //alpha

//Wine struct
struct Wine {
    double quality;
    double *attributes;
    double guess;
};

//Node struct for tree
struct Node {
    Wine *wine;
    Node *left, *right;
    Node (Wine* w) {
        wine = w;
        left = right = NULL;
    }
};

Wine *wines; //wines
Node *kd_tree; //tree
vector<Wine*> W; //vector of type Wine
typedef pair<double, Wine*> wineDist; //Wine Distance
queue<wineDist> Q; //Queue of pair where first is distance to neigbor and second is a Wine pointer

//function normalizes the data
void normalize(void) {
    double mean = 0, variance = 0, deviation;

    for (int i = 0; i < D; i++) {

        for (int j = 0; j < N; j++) {
            mean += wines[j].attributes[i];
        }
        mean = mean / N;

        for (int j = 0; j < N; j++) {
            variance += pow((wines[j].attributes[i] - mean), 2);
        } 
        variance = variance / N;
        deviation = sqrt(variance);

        for (int j = 0; j < N; j++) {
            wines[j].attributes[i] = wines[j].attributes[i] - mean;
            wines[j].attributes[i] = wines[j].attributes[i] / deviation;
        }
    }
}

//function inserts data into KD Tree
Node* insert(Node *T, Wine *w, int d) {

    if (T == NULL) { return new Node(w); }
    if (w->attributes[d] < T->wine->attributes[d]) { T->left = insert(T->left, w, (d + 1) % D); }
    else { T->right = insert(T->right, w, (d + 1) % D); }

    return T;
}

//function finds euclidean distance
double Distance(Wine *a, Wine *b) {
    
    double sum = 0;

    for (int i = 0; i < D; i++) {
        sum += pow((a->attributes[i] - b->attributes[i]), 2);
    }
    double dist = sqrt(sum);
    return dist;
}

//function determines the guess for the wine
double Guess(void) {
    double wtavg = 0, wtsum;
    double wt;

    for (int i = 0; i < K; i++) {
        wt = exp((A * -1.0) * Q.front().first);
        wtavg += (wt * Q.front().second->quality);
        wtsum += wt;
        Q.pop();
    }

    double guess = wtavg / wtsum;

    return guess;
}

//function finds and searches through near neighbors
void find(Node* T, Wine *w, int d) {
    
    double distance;

    if (T == NULL) { return; }

    if (T->wine != w) {
        distance = Distance(w, T->wine);
        if (Q.size() < K) {
            Q.push(wineDist(distance, T->wine));
        }
        else if (Q.front().first > distance) {
            Q.pop();
            Q.push(wineDist(distance, T->wine));
        }
    }

    if (w->attributes[d] == T->wine->attributes[d]) {
        find(T->left, w, (d + 1) % D);
        find(T->right, w, (d + 1) % D);
    }

    else if (w->attributes[d] > T->wine->attributes[d]) {
        find(T->right, w, (d + 1) % D);
        if ((Q.size() < K) || (abs(w->attributes[d] - T->wine->attributes[d]) < Q.front().first)) {
            find(T->left, w, (d + 1) % D);
        }
    }

    else {
        find(T->left, w, (d + 1) % D);
        if ((Q.size() < K) || (abs(w->attributes[d] - T->wine->attributes[d]) < Q.front().first)) {
            find(T->right, w, (d + 1) % D);
        }
    }
}

//function searches through neighbors and determines the guess
void Predict(void) {
    
    for (int i = 0; i < N; i++) {
        find(kd_tree, &wines[i], 0);
        wines[i].guess = Guess();
    }
}

//function determines the error between wine quality and the guesses
double Error(void) {
    double err = 0;

    for (int i = 0; i < N; i++) {
        err += pow((wines[i].quality - wines[i].guess), 2);
    }

    return (err / N);
}

void deallocate(Wine *w) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            delete [] &w[i].attributes[j];
        }
    }

    delete [] w;
}


int main(int argc, char *argv[]) {

    //error checking for command line
    if (argc != 3) {
        cout << "Usage: ./kd <data file> <k>\n";
        return 0;
    }

    //gets K
    K = atoi(argv[2]);

    //reads from file and stores data
    ifstream input(argv[1]);
    input >> N >> D;

    wines = new Wine[N];
    for (int i = 0; i < N; i++) {
        input >> wines[i].quality;
        wines[i].attributes = new double[D];
        for (int j = 0; j < D; j++) {
            input >> wines[i].attributes[j];
        }
    }

    input.close();

    //normalizes data
    normalize();

    //insert wines into a vector
    for (int i = 0; i < N; i++) {
        W.push_back(&wines[i]);
    }
    //randomize vector to ensure a balanced tree
    random_shuffle(W.begin(), W.end());

    //insert into the KD Tree
    for (int i = 0; i < N; i++) {
        kd_tree = insert(kd_tree, W[i], 0);
    }

    //calculate the predictions and the error for those predictions
    Predict();
    double avgError = Error();

    //prints out the error
    cout << "Average squared error of " << K << " is: " << avgError << endl;

    deallocate(wines);
    
    return 0; 
}