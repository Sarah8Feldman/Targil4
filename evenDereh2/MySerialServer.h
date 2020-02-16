//
// Created by sarah on 24/01/2020.
//

#ifndef MILESTONE2_23_1_MYSERIALSERVER_H
#define MILESTONE2_23_1_MYSERIALSERVER_H

#include "Server.h"

class MySerialServer : public server_side::Server {

public:
    MySerialServer();
    virtual ~MySerialServer();

    virtual void open(int port, ClientHandler* ch);
    virtual void stop(int sockfd);
};


#endif //MILESTONE2_23_1_MYSERIALSERVER_H