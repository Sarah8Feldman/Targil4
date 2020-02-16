//
// Created by sarah on 21/01/2020.
//

#ifndef SERVER_MAIN_H
#define SERVER_MAIN_H

#include <string>
#include "Solver.h"
#include "StringReverser.h"
#include "Server.h"
#include "Server.h"
#include "MySerialServer.h"
#include "ClientHandler.h"
#include "MyTestClientHandler.h"
#include "Point.h"
#include "Heuristic.h"
#include "ManhattanDistance.h"
#include "Searcher.h"
#include "Astar.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"


using namespace std;

namespace boot {
    class Main{
    public:
        void main(int port) {
            cout << "Server Port is " << port << endl;
            auto *parallelServer = new MyParallelServer();
            FileCacheManager *cache = new FileCacheManager;
            Heuristic<Point>* h = new ManhattanDistance();
            Searcher<Point> *searcher = new AStar<Point>(h);

            ClientHandler *myClient = new MyClientHandler<Point>(cache,searcher );

//            auto *s = new MyClientHandler<Position>(searcher, fcm);
            parallelServer->open(port, myClient);
            parallelServer->stop(port);

//            server_side::Server *serialServer = new MySerialServer();
//            serialServer->open(port,myClient);
//            myClient->handleClient(1);


        }
        static bool isNumber(const char* varValue);
        static const int _DEFAULT_SERVER_PORT = 5400;

    };


}
#endif //SERVER_MAIN_H
