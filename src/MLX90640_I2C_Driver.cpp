#include "MLX90640_I2C_Driver.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <QCoreApplication>
#include <QSettings>
#include <QProcess>
#include <QThread>
#include <sailfishapp.h>
#include "conv.h"
#include <unistd.h>

void MLX90640_I2CInit(void){

}

int MLX90640_I2CGeneralReset(void){
return 0;
}

int MLX90640_I2CRead(uint8_t slaveAddr,uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data){
return 0;
}

void MLX90640_I2CFreqSet(int freq){

}

int MLX90640_I2CWrite(uint8_t slaveAddr,uint16_t writeAddress, uint16_t data)
{
    int file;
    char buf[200];
    bool parseOk;

    QByteArray tmpBa = devName.toUtf8();
    const char* devNameChar = tmpBa.constData();

    fprintf(stderr, "writing to address %02x: ", address);

    /* parse QString data to buf */
    QStringList bytes = data.split(" ");
    int i;
    for (i=0 ; i<bytes.length(); i++)
    {
        QString tmp = bytes.value(i);
        buf[i] = tmp.toInt(&parseOk, 16);
        if (!parseOk)
        {
            fprintf(stderr, "parsing error %d\n", i);
            emit i2cError();
            return -1;
        }
        fprintf(stderr, "%02x ", buf[i]);
    }
    fprintf(stderr, "\n");


    if ((file = open (devNameChar, O_RDWR)) < 0)
    {
        fprintf(stderr,"open error\n");
        emit i2cError();
        return -1;
    }

    if (ioctl(file, I2C_SLAVE, address) < 0)
    {
        close(file);
        fprintf(stderr,"ioctl error\n");
        emit i2cError();
        return -1;
    }

    /* write the data */
    if (write( file, buf, bytes.length() ) != bytes.length())
    {
        close(file);
        fprintf(stderr,"write error\n");
        emit i2cError();
        return -1;
    }

    close(file);

    fprintf(stderr,"write ok\n");

    emit i2cWriteOk();
    return 0;
}
