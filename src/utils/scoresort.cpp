#include "scoresort.h"
#include <algorithm>

using namespace std;

//http://www.cplusplus.com/reference/algorithm/sort/

/*!
 * \brief premet de comparer les paires de score ( teste si a>b )
 * \description renvoie true si a > b
 *          utilisé par l'algorithme sort de la bibliothèque algorithm
 * \param[in] a : premier score
 * \param[in] b : deuxième score 
 * \return <ul>
 *          <li> vrai si a>b</li>
 *          <li> faux is a<b</li>
 *         </ul>
 */
bool compPairs(const pair<string, unsigned> &a, const pair<string, unsigned> &b)
{
    return (a.second > b.second);
}

/*!
 *
 * \brief trie tous les scores
 * \param scores : vector de paire pseudo - score
 * 
 */

void scoreSort(vector<pair<string, unsigned>> &scores)
{
    sort(scores.begin(), scores.end(), compPairs);
}
