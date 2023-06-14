#ifndef DATAPOLLCOMMAND_H
#define DATAPOLLCOMMAND_H

#include <QObject>

#include "command.h"
#include "src/MLX90640_API.h"

class DtPollCommand : public Command
{
protected:
    MLX90640* _thermal;
public:
    DtPollCommand(MLX90640* thermal) : _thermal(thermal){}
    void exec() override {_thermal->getData();}
};

#endif // DATAPOLLCOMMAND_H
