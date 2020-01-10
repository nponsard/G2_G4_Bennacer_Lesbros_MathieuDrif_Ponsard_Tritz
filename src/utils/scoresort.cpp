#include "scoresort.h"
#include <algorithm>

using namespace std;

//http://www.cplusplus.com/reference/algorithm/sort/

bool compPairs (const pair<string, unsigned> & a, const pair<string, unsigned> & b)
{
    return (a.second > b.second);
}

void scoreSort(vector<pair<string, unsigned>> & scores)
{
    sort(scores.begin(), scores.end(), compPairs);
}
