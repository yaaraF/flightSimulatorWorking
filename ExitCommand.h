
#ifndef HOPEGOOD_EXITCOMMAND_H
#define HOPEGOOD_EXITCOMMAND_H


#include "Command.h"

class ExitCommand : public Command {
public:
    ExitCommand(MySocket *mySocket);

    void doCommand();
};


#endif //HOPEGOOD_EXITCOMMAND_H
