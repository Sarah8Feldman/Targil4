//
// Created by sarah on 24/01/2020.
//

#ifndef MILESTONE2_23_1_ASTAR_H
#define MILESTONE2_23_1_ASTAR_H
#include "BestFirstSearch.h"
#include "State.h"
#include "Heuristic.h"

template<class T>
class AStar : public BestFirstSearch<T> {
private:
    Heuristic<T> *m_heuristic;
    double x, y, x1, y1;

protected:
     double costBetweenNodes(State<T> *start, State<T> *end) const {
         double cost = 0;
        if (start == end) {
            cost = m_heuristic->evaluateFromNode(end);
        }
         cost = start->getCost() + end->getOriginalCost();
         return cost;
    }

public:
    explicit AStar(Heuristic<T> *h) {
        m_heuristic = h;
     }

     vector<State<T> *> search(Searchable<T> *searchable) {
         m_heuristic->setGoal(searchable->getGoalState());
        return BestFirstSearch<T>::search(searchable);
    }

//    double manhatanDistance() {
//        double val = abs(x- x1);
//        val += abs(y- y1);
//        return val;
//    }
//
//    State<Point>* getGoalStateFromSearchable(Searchable<T> *searchable){
//        return searchable->getGoalState();
//    }
    int getNumOfNodesEvaluated(){
        return BestFirstSearch<T>::getNumberOfNodesEvaluated();
     }
    virtual ~AStar() {}

};


#endif //MILESTONE2_23_1_ASTAR_H
