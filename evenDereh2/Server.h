//
// Created by sarah on 24/01/2020.
//

#ifndef MILESTONE2_23_1_SERVER_H
#define MILESTONE2_23_1_SERVER_H

#include "ClientHandler.h"
#include <iostream>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <chrono>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <cstring>
#define TIME_OUT 1

using namespace std;

namespace server_side {

    class Server {

    public:
        virtual ~Server() {}
        virtual void open(int port, ClientHandler* c) = 0;
        virtual void stop(int sockfd) = 0;
    };
}

#endif //MILESTONE2_23_1_SERVER_H