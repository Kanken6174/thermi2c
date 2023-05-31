#ifndef THERMALDATARENDERER_H
#define THERMALDATARENDERER_H

#include <QObject>
#include <QVector>
#include <QColor>

class ThermalDataRenderer
{
    bool direct = false;
    QVector<QColor> renderBuffer;
    float minValue = 0.0f;
    float maxValue = 0.0f;
public:
    ThermalDataRenderer();
};

#endif // THERMALDATARENDERER_H
