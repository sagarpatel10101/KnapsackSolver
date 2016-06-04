This program solves the knapsack problem for different sizes of knapsacks (inputs) using a branch and bound algorithm.

The knapsack problem is a problem in which a user has a certain number of objects with different weights and values as well as a "knapsack" that
is limited in how much weight it can hold. The problem is to find which objects can be put in the bag that give the bag the most total value while
keeping the weight below a certain threshold. With 1024 objects the total possible combinations of objects that can be put in the bag (with an
infinite weight threshold) is 2^1024. Objects cannot be divided into fractions.

This algorithm uses a branch and bound algorithm to solve this problem in a small amount of time. The branch and bound algorithm consists of a 
greedy algorithm combined with a brute force algorithm. The greedy algorithm calculates the highest possible value for a bag that can be obtained
using fractions of objects for any possible instance of the problem. The brute force algorithm goes through every possible solution to the problem
while excluding branches where the best possible value that can be obtained from the branch is less than than that of another branch that
has already been explored. If the best possible value for a branch that is being explored is less than a full solution to another branch that
has already been explored then that branch of the search is excluded and the algorithm moves on.
