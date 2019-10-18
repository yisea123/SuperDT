#ifndef ICONFIGLOADER_H
#define ICONFIGLOADER_H

#include <QDomElement>

class IConfigLoader
{
public:
    virtual void loadConfig(QDomElement root) = 0;
};

#endif // ICONFIGLOADER_H
