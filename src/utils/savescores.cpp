#include "savescores.h"
#include <fstream>

using namespace std;

int saveScores(const vector<pair<string, unsigned>> & scores, const string &fileName)
{
    ofstream file(fileName);
    if(!file.is_open())
        return -1;

    for(const pair<string, unsigned> & p : scores)
        file << p.first << " : " << p.second << endl;

    return 0;
}
