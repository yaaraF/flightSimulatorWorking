

#ifndef FLIGHTSIMULATOR_CREATECOMMANDMAP_H
#define FLIGHTSIMULATOR_CREATECOMMANDMAP_H

#include "CommandExpression.h"
#include "OpenDataServerCommand.h"
#include "ConnectCommand.h"
#include "PrintCommand.h"
#include "IfCommand.h"
#include "MySocket.h"
#include "WhileCommand.h"
#include "VarCommand.h"
#include "SleepCommand.h"
#include "EntercCommand.h"
#include "ExitCommand.h"

class CreateCommandMap {
    map<string, Expression *> commands;
    MySocket *mySocket;
    IfCommand *a;
    WhileCommand *b;
public:
    CreateCommandMap();

    map<string, Expression *> getMapCommand();

    ~CreateCommandMap();
};


#endif //FLIGHTSIMULATOR_CREATECOMMANDMAP_H
