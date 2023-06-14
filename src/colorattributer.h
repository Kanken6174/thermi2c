#ifndef COLORATTRIBUTER_H
#define COLORATTRIBUTER_H

#include <QObject>
#include <QVector>
#include <QColor>
#include <QString>

class ColorAttributer : public QObject
{
    Q_OBJECT
protected:
    std::map<float, QColor> myColors;
    QString myName;
public:
    float minValue, maxValue;
    ColorAttributer(QString name, const float& minValue = -3000000.0f, const float& maxValue = -1000000.0f) : minValue(minValue), maxValue(maxValue), myName(name) {}
    //ColorAttributer(QString name, const float& minValue = 0.0f, const float& maxValue = 1.0f) : minValue(minValue), maxValue(maxValue), myName(name) {}
    Q_INVOKABLE inline QString getName() const {return myName;}
    Q_INVOKABLE void addColor(const float& value, const QColor& color);
    Q_INVOKABLE QColor encode(const float& value);
};

#endif // COLORATTRIBUTER_H
