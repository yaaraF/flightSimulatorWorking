//
// Created by adi on 12/24/18.
//

#ifndef FLIGHTSIMULATOR_CONDITIONCOMMAND_H
#define FLIGHTSIMULATOR_CONDITIONCOMMAND_H

#include "Command.h"
#include "OrganizedData.h"
#include "CommandExpression.h"

class ConditionCommand :public Command{
protected:
    OrganizedData *data;
    void DoTheCondtion();
    bool check = true;

public:


    ConditionCommand(MySocket *mySocket, OrganizedData *data);

    virtual void doCommand() = 0;
    bool checkTheExpretion();
    void add(string s,Expression *e);
    map<string,Expression*> getMap();
};


#endif //FLIGHTSIMULATOR_CONDITIONCOMMAND_H
