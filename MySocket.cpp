
#include <iostream>
#include <strings.h>

#include <cstring>
#include <cstdio>


#include "MySocket.h"


void *MySocket::openFlightSocket(void *s) {
    struct exmp *myStruct = (struct exmp *) s;
    int sockfd, portno;
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(myStruct->sPort.c_str());

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, 1);
    myStruct->numID = DataReader(sockfd);

    getFlightSocket(myStruct->numID, myStruct->myMap);

}

void *MySocket::getFlightSocket(int id, map<string, float> *data) {

    while (true) {
        char buffer[1000];
        ssize_t bRead;

        bRead = read(id, buffer, 999);

        if (bRead < 0) {
            //TODO error
        } else if (bRead == 0) {
            //TODO conection close
        } else {

            buffer[bRead] = NULL;
            updateTheDateMap(buffer, data);

        }

    }

}

int MySocket::DataReader(int serverId) {

    sockaddr_in client_sock;
    int client;
    int client_sock_fd = accept(serverId, (struct sockaddr *) &client_sock, (socklen_t *) &client);


    int simolatorId = client_sock_fd;

    if (client_sock_fd < 0) {

    } else {

    }
    return simolatorId;
}


void MySocket::updateTheDateMap(string buffer, map<string, float> *data) {
    vector<float> vec = split(buffer);


    data->find("/instrumentation/airspeed-indicator/indicated-speed-kt")->second = vec[0];

    data->find("/instrumentation/altimeter/indicated-altitude-ft")->second = vec[1];
    data->find("/instrumentation/altimeter/pressure-alt-ft")->second = vec[2];
    data->find("/instrumentation/attitude-indicator/indicated-pitch-deg")->second = vec[3];
    data->find("/instrumentation/attitude-indicator/indicated-roll-deg")->second = vec[4];
    data->find("/instrumentation/attitude-indicator/internal-pitch-deg")->second = vec[5];
    data->find("/instrumentation/attitude-indicator/internal-roll-deg")->second = vec[6];
    data->find("/instrumentation/encoder/indicated-altitude-ft")->second = vec[7];
    data->find("/instrumentation/encoder/pressure-alt-ft")->second = vec[8];
    data->find("/instrumentation/gps/indicated-altitude-ft")->second = vec[9];
    data->find("/instrumentation/gps/indicated-ground-speed-kt")->second = vec[10];
    data->find("/instrumentation/gps/indicated-vertical-speed")->second = vec[11];
    data->find("/instrumentation/heading-indicator/indicated-heading-deg")->second = vec[12];
    data->find("/instrumentation/magnetic-compass/indicated-heading-deg")->second = vec[13];
    data->find("/instrumentation/slip-skid-ball/indicated-slip-skid")->second = vec[14];
    data->find("/instrumentation/turn-indicator/indicated-turn-rate")->second = vec[15];
    data->find("/instrumentation/vertical-speed-indicator/indicated-speed-fpm")->second = vec[16];
    data->find("/controls/flight/aileron")->second = vec[17];
    data->find("/controls/flight/elevator")->second = vec[18];
    data->find("/controls/flight/rudder")->second = vec[19];
    data->find("/controls/flight/flaps")->second = vec[20];
    data->find("/controls/engines/engine/throttle")->second = vec[21];
    data->find("/engines/engine/rpm")->second = vec[22];

}


bool MySocket::isVar(string s) {
    map<string, string>::iterator it;
    it = this->varPlaces.find(s);
    if (it != this->varPlaces.end()) {
        return true;
    }

    map<string, double>::iterator it2;
    it2 = this->please.find(s);

    if (it2 != this->please.end()) {
        return true;
    }

    return false;
}

float MySocket::getValueOfVar(string s) {
    string key;
    float val;



    //return the value from the right map.
    map<string, string>::iterator it;

    it = this->varPlaces.find(s);
    if (it != this->varPlaces.end()) {
        key = this->varPlaces[s];
        val = this->dataFromSimolator[key];
    } else {
        val = this->please[s];
    }
    return val;
}


void MySocket::initializeTheMap() {
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/altimeter/indicated-altitude-ft", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/altimeter/pressure-alt-ft", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/attitude-indicator/indicated-roll-deg", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/attitude-indicator/internal-roll-deg", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/encoder/indicated-altitude-ft", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/encoder/pressure-alt-ft", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/gps/indicated-altitude-ft", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/gps/indicated-ground-speed-kt", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/gps/indicated-vertical-speed", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/heading-indicator/indicated-heading-deg", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/magnetic-compass/indicated-heading-deg", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));
    this->dataFromSimolator.insert(pair<string, float>("/instrumentation/turn-indicator/indicated-turn-rate", 0));
    this->dataFromSimolator.insert(
            pair<string, float>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
    this->dataFromSimolator.insert(pair<string, float>("/controls/flight/aileron", 0));
    this->dataFromSimolator.insert(pair<string, float>("/controls/flight/elevator", 0));
    this->dataFromSimolator.insert(pair<string, float>("/controls/flight/rudder", 0));
    this->dataFromSimolator.insert(pair<string, float>("/controls/flight/flaps", 0));
    this->dataFromSimolator.insert(pair<string, float>("/controls/engines/current-engine/throttle", 0));
    this->dataFromSimolator.insert(pair<string, float>("/engines/engine/rpm", 0));


}

vector<float> MySocket::split(string buffer) {


    vector<float> data;
    size_t pos = 0;
    int i = 0;
    string delimiter = ",";
    while ((pos = buffer.find(delimiter)) != string::npos) {


        string temp = buffer.substr(0, pos);
        float a = strtof((temp).c_str(), 0);

        data.push_back(a);


        buffer.erase(0, pos + delimiter.length());
        i++;
    }
    data.push_back(strtof(buffer.substr(0, pos).c_str(), 0));
    return data;
}

map<string, float> *MySocket::getDAtaFromServer() {
    return &this->dataFromSimolator;
}

void MySocket::conectToSimolator(vector<string> data) {

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;


    portno = atoi((data[1]).c_str());

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    this->connectionId = sockfd;

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(data[0].c_str());

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }


}

void MySocket::addBind(string varName, string path) {

    string temp = path.substr(1, path.size() - 2);

    this->varPlaces.insert(pair<string, string>(varName, temp));
    map<string, float>::iterator it;
    it = this->dataFromSimolator.find(temp);


    if (it == this->dataFromSimolator.end()) {
        this->please.insert(pair<string, float>(varName, 0.0));

    }
}

void MySocket::addVar(string varName, float value) {
    string buffer;
    buffer = "set ";

    string converVal = to_string(value);
    map<string, string>::iterator it;
    it = this->varPlaces.find(varName);

    if (it != this->varPlaces.end()) {
        string path = it->second;
        path = path.substr(0, path.length());
        buffer = buffer + path + " ";
        buffer += converVal;
        buffer += "\r\n";

        const char *c = buffer.c_str();
        this->Write(c);
        return;


    }

    map<string, double>::iterator it2;
    it2 = this->please.find(varName);
    if (it2 != this->please.end()) {
        this->please[varName] = value;
        return;
    }
    this->please.insert(pair<string, double>(varName, value));

}

void MySocket::Write(const char *buffer) {

    ssize_t n = ::write(this->connectionId, buffer, strlen(buffer));


    if (n < 0) {
        perror("ERROR working with socket");
        exit(1);
    }
}

void MySocket::print(string var) {
    map<string, double>::iterator it;

    it = this->please.find(var);
    if (it != this->please.end()) {
        cout << this->please[var] << endl;
        return;
    }

    map<string, string>::iterator flightVar;
    flightVar = this->varPlaces.find(var);
    if (flightVar != this->varPlaces.end()) {
        string key = this->varPlaces[var];
        cout << this->dataFromSimolator[key] << endl;
        return;
    }
    cout << var << endl;
}

void MySocket::setSimulatorID(int id) {
    this->simolatorId = id;
}

void MySocket::exitSockets() {
    this->isExit = true;
    exit(this->connectionId);
    exit(this->simolatorId);
}

MySocket::~MySocket() {
    if (!this->isExit) {
        this->isExit = true;
        exitSockets();
    }
}




