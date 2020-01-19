#ifndef LOADCONFIG_H
#define LOADCONFIG_H

#include <map>
#include <string>
#include <vector>

/*!
 *
 * \brief names of the parameters which can be in the config file
 * 
 */

struct AuthorizedKey
{
    /* List of authorized key for the type char in a struct CMyParam*/
    // const std::vector<std::string> VParamChar {};
    /* List of authorized key for the type string in a struct CMyParam*/
    // const std::vector<std::string> VParamString {};
    /* List of authorized key for the type unsigned in a struct CMyParam*/
    const std::vector<std::string> VParamUnsigned{"invadersMaxVelocity", "invadersMinVelocity", "shot", "invadersShot", "bonusInvaders", "bonusInvaderVelocityFactor", "bonusInvaderPosAbs",
                                                  "bonusInvaderPosOrd", "playerPosAbs", "playerPosOrd", "lives", "scoreForMissileDestruction", "scoreStep",
                                                  "scoreStepBonusInvaders", "torpedoVelocity", "wave", "upgradeSpeed"};
};

std::map<std::string, std::string> loadConfig(const std::string &fileName);

#endif // LOADCONFIG_H
