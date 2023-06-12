#include "mlx90640_I2C_Driver.h"
#include "i2cdriversingleton.h"
#include <QString>

#define DEFAULT_I2C_DEV QString("/dev/i2c-1/")

///
/// \brief mlx90640_I2CInit Setup the I2C lines
///
void mlx90640_I2CInit(void){
    i2cDriverSingleton::getinstance()->tohVddSet(QString("on"));
    i2cDriverSingleton::getinstance()->i2cProbe(DEFAULT_I2C_DEV);
}

///
/// \brief mlx90640_I2CGeneralReset resets the I2C line and devices
/// \return 0 if success
///
int mlx90640_I2CGeneralReset(void){
    return 0;
}

///
/// \brief mlx90640_I2CFreqSet Sets the frequency for the I2C bus
/// \param freq
///
void mlx90640_I2CFreqSet(int freq){

}

int mlx90640_I2CRead(uint8_t slaveAddr,uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data){
    return i2cDriverSingleton::getinstance()->i2cRead(slaveAddr, startAddress, nMemAddressRead, data);
}

int mlx90640_I2CWrite(uint8_t slaveAddr,uint16_t writeAddress, uint16_t data)
{
    return i2cDriverSingleton::getinstance()->i2cWrite(slaveAddr, writeAddress, data);
}
