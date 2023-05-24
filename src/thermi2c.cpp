#ifdef QT_QML_DEBUG
#include "conv.h"
#include "i2cif.h"
#include "mlx90640_API.h"

#include <QtQuick>
#endif

#include <sailfishapp.h>

int main(int argc, char *argv[])
{
    qmlRegisterType<I2cif>("harbour.i2ctool.I2cif", 1, 0, "I2cif");
    qmlRegisterType<Conv>("harbour.i2ctool.Conv", 1, 0, "Conv");
    qmlRegisterType<MLX90640>("melexis.driver", 1, 0, "MLX90640");

    return SailfishApp::main(argc, argv);
}
