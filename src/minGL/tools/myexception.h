#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include "CException.h"
#include "CstCodErr.h"

class myexception : public nsUtil::CException
{
public:
    myexception(const unsigned & code);
};

#endif // MYEXCEPTION_H
