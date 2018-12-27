
#include "OpenDataServerCommand.h"
#include <pthread.h>



void OpenDataServerCommand::doCommand() {


    if(this->parm.size()!=2){
        throw "the parm are not match to openDataServer";
    }


    this->t->myMap = this->mySocket->getDAtaFromServer();
    this->t->sPort=this->parm[0];
    pthread_t trid;
    int x=pthread_create(&trid, nullptr,MySocket::openFlightSocket,t);

}

OpenDataServerCommand::OpenDataServerCommand(MySocket *mySocket) : Command(mySocket) {}

OpenDataServerCommand::~OpenDataServerCommand() {
    delete(this->t);
}