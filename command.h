#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class Command
{
public:
    Command();
    virtual void exec() = 0;
};

#endif // COMMAND_H
