//
// Created by sarah on 24/01/2020.
//

#ifndef MILESTONE2_23_1_DFS_H
#define MILESTONE2_23_1_DFS_H

#include <stack>
#include "Searcher.h"
#include "Searchable.h"

using namespace std;

template<class T>
class DFS : public Searcher<T> {
public:
    DFS();

    virtual vector<State<T> *> search(Searchable<T> *searchable);

    virtual ~DFS();
};

template<class T>
DFS<T>::~DFS() {
}

template<class T>
DFS<T>::DFS() {}

template<class T>
vector<State<T> *> DFS<T>::search(Searchable<T> *searchable) {
//    State<T> *cameFrom;
//    vector<State<T> *> adjacentStates;
    //init the start and goal state
    stack<State<T> *> stack;
    State<T> *startState = searchable->getInitialState();
    State<T> *goalState = searchable->getGoalState();
    startState->setCameFrom(nullptr);
    this->numOfNodesEvaluated++;
    stack.push(startState);

    while (!stack.empty()) {
        startState = stack.top();
        stack.pop();
        //if got to the the goal state-break
        if (startState == goalState) {
            break;
        }

        vector<State<T> *> successors = searchable->getAllPossibleStates(startState);
        for (State<T> *succ : successors) {
            // Ignoring walls
            if (succ->getCost() == -1) {
                continue;
            }
            if (!succ->isNodeVisited()) {
                succ->setCameFrom(startState);
                this->numOfNodesEvaluated++;
                stack.push(succ);
            }
        }
    }
//    cout<<this->numOfNodesEvaluated << endl;
    return this->backTraceNodes(searchable->getGoalState());

}
#endif //MILESTONE2_23_1_DFS_H
