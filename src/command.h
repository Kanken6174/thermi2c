#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class Command : public QObject
{
    Q_OBJECT
public:
    Command();
    virtual void exec() = 0;
};

#endif // COMMAND_H
