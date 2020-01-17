#include "savescores.h"
#include <fstream>

using namespace std;

/*!
 * \brief saves the scores in a file
 * \param scores : vector containing all the pairs linking names and scores
 * \param filename : name of the file in which write the scores
 * 
 */

int saveScores(const vector<pair<string, unsigned>> &scores, const string &fileName)
{
    ofstream file(fileName);
    if (!file.is_open())
        return -1;

    for (const pair<string, unsigned> &p : scores)
        file << p.first << " : " << p.second << endl;

    return 0;
}
