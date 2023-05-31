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

        // Create instance of MLX90640
        MLX90640 mlx90640;

        // Initialize application and view
        QGuiApplication app(argc, argv);
        QQuickView view;

        MLX90640 thermal;
        view.rootContext()->setContextProperty("mlx90640",&thermal);

        view.setSource(SailfishApp::pathToMainQml());
        view.show();

        return app.exec();
    }
