#ifndef I2CDRIVERSINGLETON_H
#define I2CDRIVERSINGLETON_H

#include <QObject>
#include "i2cif.h"

class i2cDriverSingleton : public QObject
{
protected:
    static I2cif* instance;
public:
    i2cDriverSingleton(i2cDriverSingleton& other) = delete; //no copy
    void operator=(const i2cDriverSingleton&) = delete; //no assign

    static I2cif* getinstance();
    static void cleanup();
};

#endif // I2CDRIVERSINGLETON_H
