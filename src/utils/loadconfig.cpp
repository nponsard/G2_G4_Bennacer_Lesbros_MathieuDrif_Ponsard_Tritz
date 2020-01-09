#include "loadconfig.h"
#include <fstream>
#include <algorithm>

using namespace std;

map<string, string> loadConfig(string fileName)
{
    map<string, string> result;
    ifstream ifs(fileName);
    string key;
    string sep;
    AuthorizedKey AK;

    if (!ifs.good())
    {
        ofstream ofs(fileName);
        ofs << "invadersVelocity : 1" << endl
            << "invadersMaxVelocity : 5"
            << endl
            << "invadersVelocityStep : 1"
            << endl
            << "shot : 200"
            << endl
            << "invadersShot : 900"
            << endl
            << "bonusInvaders : 15000"
            << endl
            << "bonusInvaderPosAbs : 0"
            << endl
            << "bonusInvaderPosOrd : 0"
            << endl
            << "playerPosAbs : 0"
            << endl
            << "playerPosOrd : 50"
            << endl
            << "lives : 3"
            << endl
            << "score : 0"
            << endl
            << "bestScore : 0"
            << endl
            << "scoreForMissileDestruction : 50"
            << endl
            << "scoreStep : 100"
            << endl
            << "scoreStepBonusInvaders : 500"
            << endl
            << "torpedoVelocity : 20"
            << endl
            << "wave : 1";
        ifs.open(fileName);
    }

    while (true)
    {
        ifs >> key;

        //unsigned
        if (find(AK.VParamUnsigned.begin(), AK.VParamUnsigned.end(), key) != AK.VParamUnsigned.end())
        {
            ifs >> sep;
            unsigned val;
            ifs >> val;
            result[key] = to_string(val);
        }
        if (ifs.eof())
            return result;
        getline(ifs, sep);
    }
}
