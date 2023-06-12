#ifndef THERMALDATARENDERER_H
#define THERMALDATARENDERER_H

#include <QObject>
#include <QVector>
#include <QColor>
#include <QThread>

#include <memory>
#include <exception>
#include "colorattributer.h"

typedef std::shared_ptr<ColorAttributer> ColorAttributerPtr;

class ThermalDataRenderer : public QObject
{
    Q_OBJECT

    bool direct = false;
    QVector<QColor> renderBuffer;   //size = 768
    QVector<ColorAttributerPtr> attributers;
    unsigned int activeAttributer;
    float minValue = 0.0f;
    float maxValue = 1.0f;
public:
    Q_PROPERTY(QVector<std::shared_ptr<ColorAttributer>> attributers READ getAttributers NOTIFY attributersChanged)
    QThread workerThread;
    ThermalDataRenderer() : renderBuffer(768){}
    Q_INVOKABLE QColor getDataForIndex(const int& index){
        if(index < renderBuffer.length() && index >= 0)
        {
            return renderBuffer.at(index);
        }else
            return QColor(0,0,0);
    }

    inline void addAttributer(ColorAttributerPtr attributer) {
        attributers.push_back(attributer);
    }

    inline QVector<ColorAttributerPtr> getAttributers(){ return attributers; }

    Q_INVOKABLE inline void setActiveAttributer(const int& index) {
        if(index < attributers.size()) {
            activeAttributer = index;
        }
    }

    inline unsigned int getActiveAttributer() const {
        return activeAttributer;
    }

    inline void setMinValue(float value) {
        minValue = value;
    }

    inline float getMinValue() const {
        return minValue;
    }

    inline void setMaxValue(float value) {
        maxValue = value;
    }

    inline float getMaxValue() const {
        return maxValue;
    }

public: signals:
    void attributersChanged();
    void dataChanged();

public slots:
    void receiveNewData(QVector<float> data);
};

#endif // THERMALDATARENDERER_H
