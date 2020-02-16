//
// Created by sarah on 24/01/2020.
//

#ifndef MILESTONE2_23_1_BFS_H
#define MILESTONE2_23_1_BFS_H

#include "Searcher.h"
#include "State.h"
#include "Searchable.h"
#include <queue>

using namespace std;

template<class T>
class BFS : public Searcher<T> {

public:
    BFS() {}

    vector<State<T> *> search(Searchable<T> *searchable) override;

    virtual ~BFS() {}
};

template<class T>
vector<State<T> *> BFS<T>::search(Searchable<T> *searchable) {
    State<T> *node;
    node = searchable->getInitialState();
    //create a queue
    queue<State<T> *> queue;
    //get the initial state
    queue.push(node);
    node->setCameFrom(nullptr);
    this->numOfNodesEvaluated++;

    while (!queue.empty()) {
        node = queue.front();
        queue.pop();

        if (searchable->getGoalState() == node) {
            break;
        }
        vector<State<T> *>  successors = searchable->getAllPossibleStates(node);
        //check if we visited adjacent nodes
        for (auto succ: successors) {
//            State<T> *n = iter;
            if (node->getCost() == -1) {
                continue;
            }
            if (!(succ->isNodeVisited())) {
                succ->setCameFrom(node);
                this->numOfNodesEvaluated++;
                //add to the queue
                queue.push(succ);
            }
        }
    }
//    cout<<this->numOfNodesEvaluated << endl;
    return this->backTraceNodes(searchable->getGoalState());
}


#endif //MILESTONE2_23_1_BFS_H
