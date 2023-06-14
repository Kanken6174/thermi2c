#include "i2cif.h"
#include "mlx90640_API.h"
#include "ColorAttributer.h"
#include "ThermalDataRenderer.h"
#include "DataPollCommand.h"
#include "PollingTimer.h"
#include "conv.h"
#include "datapollcommand.h"

#include <QString>

#include <QtQuick>
#include <sailfishapp.h>

int main(int argc, char *argv[]) {
    // Register types and create instances
    qmlRegisterType<I2cif>("harbour.i2ctool.I2cif", 1, 0, "I2cif");
    qmlRegisterType<Conv>("harbour.i2ctool.Conv", 1, 0, "Conv");
    qmlRegisterType<MLX90640>("melexis.driver", 1, 0, "MLX90640");
    qmlRegisterType<ThermalDataRenderer>("my.app", 1, 0, "ThermalDataRenderer");
    //qmlRegisterType<ColorAttributer>("my.app", 1, 0, "ColorAttributer");

    MLX90640 mlx90640;

    ThermalDataRenderer* thermalRenderer = new ThermalDataRenderer();

    auto hotIron = std::make_shared<ColorAttributer>("hot iron");
    hotIron->addColor(0.0, QColor(0, 0, 0)); // Black
    hotIron->addColor(0.35, QColor(128, 0, 128)); // Magenta
    hotIron->addColor(0.5, QColor(255, 69, 0)); // OrangeRed
    hotIron->addColor(1.0, QColor(255, 255, 0)); // Yellow

    auto rainbow = std::make_shared<ColorAttributer>("rainbow");
    rainbow->addColor(0.0, QColor(255, 0, 0)); // Red
    rainbow->addColor(0.33, QColor(0, 255, 0)); // Green
    rainbow->addColor(0.67, QColor(0, 0, 255)); // Blue
    rainbow->addColor(1.0, QColor(255, 0, 255)); // Magenta

    auto grayscale = std::make_shared<ColorAttributer>("grayscale");
    grayscale->addColor(0.0, QColor(0, 0, 0)); // Black
    grayscale->addColor(0.25, QColor(75, 75, 75)); // dark gray
    grayscale->addColor(0.5, QColor(150, 150, 150)); // gray
    grayscale->addColor(0.75, QColor(200, 200, 200)); // light gray
    grayscale->addColor(1.0, QColor(255, 255, 255)); // White

    auto sunset = std::make_shared<ColorAttributer>("sunset");
    sunset->addColor(0.0, QColor(255, 80, 80)); // Deep red
    sunset->addColor(0.2, QColor(255, 165, 0)); // Orange
    sunset->addColor(0.4, QColor(255, 255, 0)); // Yellow
    sunset->addColor(0.6, QColor(255, 204, 0)); // Gold
    sunset->addColor(0.8, QColor(255, 102, 0)); // Orange-red
    sunset->addColor(1.0, QColor(255, 0, 0)); // Red

    auto ocean = std::make_shared<ColorAttributer>("ocean");
    ocean->addColor(0.0, QColor(0, 0, 255)); // Blue
    ocean->addColor(0.25, QColor(0, 128, 255)); // Light blue
    ocean->addColor(0.5, QColor(0, 255, 255)); // Cyan
    ocean->addColor(0.75, QColor(0, 204, 128)); // Sea green
    ocean->addColor(1.0, QColor(0, 51, 102)); // Dark blue

    auto fire = std::make_shared<ColorAttributer>("fire");
    fire->addColor(0.0, QColor(255, 0, 0)); // Red
    fire->addColor(0.2, QColor(255, 102, 0)); // Orange-red
    fire->addColor(0.4, QColor(255, 153, 0)); // Orange
    fire->addColor(0.6, QColor(255, 204, 0)); // Yellow
    fire->addColor(0.8, QColor(255, 255, 0)); // Bright yellow
    fire->addColor(1.0, QColor(255, 255, 255)); // White

    thermalRenderer->addAttributer(hotIron);
    thermalRenderer->addAttributer(rainbow);
    thermalRenderer->addAttributer(grayscale);
    thermalRenderer->addAttributer(sunset);
    thermalRenderer->addAttributer(ocean);
    thermalRenderer->addAttributer(fire);

    thermalRenderer->setActiveAttributer(2);//enable hotiron

    QGuiApplication app(argc, argv);
    QQuickView view;

    MLX90640* thermal = new MLX90640();

    DtPollCommand* dtpoll = new DtPollCommand(thermal);
    PollingTimer* pt = new PollingTimer(dtpoll);
    pt->moveToThread(&(pt->workerThread));
    pt->workerThread.start();

    qRegisterMetaType<QVector<float>>("QVector<float>");
    //when a frame is ready, pass it to the renderer
    QObject::connect(thermal, SIGNAL(dataReady(QVector<float>)), thermalRenderer, SLOT(receiveNewData(QVector<float>)), Qt::ConnectionType::DirectConnection);

    pt->setDelay(100);

    view.rootContext()->setContextProperty("polling_timer",pt);
    view.rootContext()->setContextProperty("mlx90640", thermal);
    view.rootContext()->setContextProperty("thermalRenderer", thermalRenderer);

    view.setSource(SailfishApp::pathToMainQml());
    view.show();

    return app.exec();
}
