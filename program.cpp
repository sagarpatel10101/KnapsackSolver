//  This code implements a branch and bound algorithm combined with a greedy algorithm to solve the knapsack problem.
//  inputs to this file can be found in this project.
#include "d_except.h"
#include "d_matrix.h"
#include "d_random.h"
#include "knapsack.h"
#include "string"
#include "ctime"
#include "vector"
#include "fstream"

using namespace std;
int runtime = 600;

// returns optimistic bound for a fractional knapsack. Starts at given index in the vector of sorted objects.
//Objects are sorted by 
double fractionalKnapsack (knapsack k, int i)
{
    int costLimit = k.getCostLimit();
    int lastObjectValue = 0;    
    
    // add objects until full objects can't be added starting from input iter i, then break
    for(int j = i; j < k.getNumObjects(); j++)
    {
        if(!k.isSelected(j) && k.getCost() + k.getCost(j) <= costLimit)
            k.select(j);
        // remember the last index visited, so a fraction of it can be taken
        else{
            lastObjectValue = (costLimit - k.getCost()) / k.getCost(j) * k.getValue(j);
        }
    }
    // return the value of all wholly selected objects, plus a fraction of final object
    return k.getValue() + lastObjectValue;
}


// Branch and bound algorithm. This algorithm calculates possible solutions to the knapsack problem
// and stores those results into a vector. 
void BB(knapsack k, vector<knapsack>& kdeq ,double &bestBound, int index)
{
    double bound = fractionalKnapsack(k, index);
    
    //if the value of the knapsack is equal to its optimistic value then compare it against the previous best knapsack config found
    //if the value is greater than the last best value than store the knapsack configuration into the vector
    if (k.getValue() == bound)
    {
        if (bound > bestBound)
        {
            kdeq.push_back(k);
            bestBound = bound;
        }
        return;
    }
    
    //if the value of the knapsack is not equal to its optimistic bound but the optimistic bound is greater than the best value previously found
    //then continue recursing
    else
    {
        if (index + 1 < k.getNumObjects() && bound >= bestBound)
        {
            k.select(index);
            BB(k, kdeq, bestBound, index + 1);
            k.unSelect(index);
            BB(k, kdeq, bestBound, index + 1);
        }
        else return;
    }
    return;
}

//Main funtion asks user for input file (location/name) and runs the branch and bound algorithm
//at the end of the BB algorithm the vector of possible solutions is searched for the best solution
//this solution is outputted to console.
int main()
{
    //file input
    ifstream fin;
    string fileName;
    cout << "Enter knapsack input filename: ";
    cin >> fileName;
    fin.open(fileName.c_str());
    knapsack k(fin);
    
    //sort the input knapsack based on value/cost
    k.insertionSort();
    
    //param init. for BB algorithm
    vector<knapsack> kdeq;
    double bestbound = 0;
    int index = 0;
    
    //run the branch and bound alg.
    BB(k,kdeq, bestbound, index);
    
    //param init. for best knapsack search.
    int bestindex = -1;
    int bestvalue = -1;
    
    for (int i = 0; i < kdeq.size(); i++)
    {
        if (kdeq[i].getValue() > bestvalue)
        {
            bestindex = i;
        }
    }
    
    //print best knapsack configuration
    kdeq[bestindex].printSolution();
    system("pause");
}
