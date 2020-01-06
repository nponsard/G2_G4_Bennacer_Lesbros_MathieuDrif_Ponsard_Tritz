#include "myexception.h"

using namespace nsUtil;

myexception::myexception(const unsigned &code)
{
    m_CodErr = code;
    auto it = kError.find(code);
    if (it == kError.end()) exit (kExcInconnue);
    m_Libelle = it->second;
}
