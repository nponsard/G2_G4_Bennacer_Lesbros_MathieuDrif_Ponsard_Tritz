#include "loadconfig.h"
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

map<string, string> loadConfig(string fileName)
{
    map<string, unsigned> defaultUnsignedConfig;
    defaultUnsignedConfig["invadersVelocity"] = 1;
    defaultUnsignedConfig["invadersMaxVelocity"] = 5;
    defaultUnsignedConfig["invadersVelocityStep"] = 5;
    defaultUnsignedConfig["shot"] = 200;
    defaultUnsignedConfig["invadersShot"] = 900;
    defaultUnsignedConfig["bonusInvaders"] = 15000;
    defaultUnsignedConfig["bonusInvaderPosAbs"] = 0;
    defaultUnsignedConfig["bonusInvaderPosOrd"] = 0;
    defaultUnsignedConfig["playerPosAbs"] = 0;
    defaultUnsignedConfig["playerPosOrd"] = 50;
    defaultUnsignedConfig["lives"] = 3;
    defaultUnsignedConfig["score"] = 0;
    defaultUnsignedConfig["bestScore"] = 0;
    defaultUnsignedConfig["scoreForMissileDestruction"] = 50;
    defaultUnsignedConfig["scoreStep"] = 100;
    defaultUnsignedConfig["scoreStepBonusInvaders"] = 500;
    defaultUnsignedConfig["torpedoVelocity"] = 20;
    defaultUnsignedConfig["wave"] = 1;
    defaultUnsignedConfig["upgradeVelocity"] = 10;

    map<string, string> result;
    ifstream ifs(fileName);
    string line;
    string key;
    char sep;
    AuthorizedKey AK;


    if(ifs.is_open())
    {
        while(true)
        {
            getline(ifs, line);

            if (ifs.eof())
                break;

            istringstream istr;
            istr.str(line);
            istr >> key;

            //unsigned
            if (find(AK.VParamUnsigned.begin(), AK.VParamUnsigned.end(), key) != AK.VParamUnsigned.end())
            {
                istr >> sep;
                unsigned val;
                istr >> val;
                if(!istr.fail())
                    result[key] = to_string(val);
                else
                    result[key] = to_string(defaultUnsignedConfig[key]);
            }
        }
    }

    //ajouter les valeurs des champs absents du fichier

    //unsigned
    for(map<string, unsigned>::iterator it(defaultUnsignedConfig.begin()); it != defaultUnsignedConfig.end(); ++it)
    {
        if(result.find(it->first) == result.end())
            result[it->first] = to_string(it->second);
    }
    return result;
}
