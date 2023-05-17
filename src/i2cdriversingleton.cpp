#include "i2cdriversingleton.h"

I2cif* i2cDriverSingleton::instance;    //instance declaration for the static variable in the singleton

I2cif* i2cDriverSingleton::getinstance()
{
    if(instance == nullptr)
        instance = new I2cif();

    return instance;
}

void i2cDriverSingleton::cleanup(){
    if(instance != nullptr){
        instance->tohVddSet(QString("off"));
    }
}
