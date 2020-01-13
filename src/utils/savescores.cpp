#include "savescores.h"
#include <fstream>

using namespace std;

/*!
 * \brief enregistre les scores dans le fichier
 * \param[in] scores : les scores liés avec le nom
 * \param[in] filename : nom du fichier où écrire 
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
