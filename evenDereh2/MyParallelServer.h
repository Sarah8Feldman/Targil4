//
// Created by sarah on 24/01/2020.
//

#ifndef MILESTONE2_23_1_YPARALLELSERVER_H
#define MILESTONE2_23_1_YPARALLELSERVER_H

#include "Server.h"
#include <vector>
#include <thread>

class MyParallelServer : public server_side::Server{
    vector<thread> m_threads;
    ClientHandler* m_handler;

private:
    static void clientHandlerObjAdapter(ClientHandler* ch, int sockfd);

public:
    MyParallelServer();
    virtual ~MyParallelServer();

    virtual void open(int port, ClientHandler* ch);
    virtual void stop(int sockfd);
};



#endif //MILESTONE2_23_1_MYPARALLELSERVER_H