#include "colorattributer.h"

Q_INVOKABLE QColor ColorAttributer::encode(const float& value) {
    if(myColors.size() < 2)
        return QColor();

    float normalizedValue = (value - minValue) / (maxValue - minValue);

    auto upper = myColors.lower_bound(normalizedValue);
    auto lower = upper;
    if(upper == myColors.begin()) {
        return upper->second;
    }
    else if(upper == myColors.end()) {
        --lower;
        return lower->second;
    }
    else {
        --lower;

        float fraction = (normalizedValue - lower->first) / (upper->first - lower->first);

        return QColor::fromRgbF(
            lower->second.redF()   + fraction * (upper->second.redF()   - lower->second.redF()),
            lower->second.greenF() + fraction * (upper->second.greenF() - lower->second.greenF()),
            lower->second.blueF()  + fraction * (upper->second.blueF()  - lower->second.blueF())
        );
    }
}

void ColorAttributer::addColor(const float& value, const QColor& color) {
    if (value >= 0.0 && value <= 1.0) {
        myColors[value] = color;
    } else {
        return; //invalid color mapping (0->1)
    }
}
