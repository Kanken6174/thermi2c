#include "thermaldatarenderer.h"
#include <chrono>
void ThermalDataRenderer::receiveNewData(QVector<float> data) {
    auto start = std::chrono::high_resolution_clock::now();
    //fprintf(stderr, "in renderer");
    //fprintf(stderr, "renderer received data of length: %d\n",data.length());

    if(activeAttributer >= attributers.size()){
        fprintf(stderr, "attr size mismatch: %d; %d",activeAttributer,attributers.size());
        activeAttributer = 0;
    }

    if(renderBuffer.size() < data.size())
        renderBuffer = QVector<QColor>(data.size()+1);

    for (int i = 0; i < data.size() && i < renderBuffer.size(); ++i) {
        renderBuffer[i] = attributers[activeAttributer]->encode(data[i]);
    }
    emit dataChanged();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    //fprintf(stderr,"renderer time: %lld\n",elapsed);
}
