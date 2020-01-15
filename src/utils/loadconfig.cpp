#include "loadconfig.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

///
/// \brief create the default config file
/// \param name of the file to create
/// \param map containing value to put in the file
///
void createConf(const string & fileName, map<string, unsigned> Map)
{
    ofstream file(fileName);
    if(!file.is_open()) {
        cerr << "impossible d'écrire le fichier :" << fileName <<endl;
        return;
    }

    for(map<string, unsigned>::iterator it(Map.begin()); it != Map.end(); ++it)
    {
         file << it->first << " : " << it->second << endl;
    }
}

///
/// \brief load config file
/// \param name of the config file
///
map<string, string> loadConfig(const string & fileName)
{
    map<string, unsigned> defaultUnsignedConfig;
    defaultUnsignedConfig["invadersMaxVelocity"] = 8;
    defaultUnsignedConfig["invadersMinVelocity"] = 2;
    defaultUnsignedConfig["shot"] = 200;
    defaultUnsignedConfig["invadersShot"] = 900;
    defaultUnsignedConfig["bonusInvaders"] = 15000;
    defaultUnsignedConfig["bonusInvaderVelocityFactor"] = 3;
    defaultUnsignedConfig["bonusInvaderPosAbs"] = 0;
    defaultUnsignedConfig["bonusInvaderPosOrd"] = 0;
    defaultUnsignedConfig["playerPosAbs"] = 0;
    defaultUnsignedConfig["playerPosOrd"] = 50;
    defaultUnsignedConfig["lives"] = 3;
    defaultUnsignedConfig["scoreForMissileDestruction"] = 50;
    defaultUnsignedConfig["scoreStep"] = 100;
    defaultUnsignedConfig["scoreStepBonusInvaders"] = 1000;
    defaultUnsignedConfig["torpedoVelocity"] = 20;
    defaultUnsignedConfig["wave"] = 1;
    defaultUnsignedConfig["upgradeVelocity"] = 10;

    map<string, string> result;
    ifstream ifs(fileName);
    if(!ifs.is_open()) createConf(fileName, defaultUnsignedConfig);
    else {

        string line;
        string key;
        char sep;
        AuthorizedKey AK;


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

