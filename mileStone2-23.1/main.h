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
#include "BestFirstSearch.h"
#include "BFS.h"
#include "DFS.h"


using namespace std;

namespace boot {
    class Main{
    public:
        void main(int port) {
            FileCacheManager *cache = new FileCacheManager;
            Heuristic<Point>* h = new ManhattanDistance();
            Searcher<Point> *searcher = new AStar<Point>(h);
            ClientHandler *myClient = new MyClientHandler<Point>(cache,searcher );
//            server_side::Server *serialServer = new MySerialServer();
//            serialServer->open(port,myClient);
            myClient->handleClient(1);


        }
    };
}
#endif //SERVER_MAIN_H
