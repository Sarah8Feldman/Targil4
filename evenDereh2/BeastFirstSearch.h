//
// Created by sarah on 24/01/2020.
//

#ifndef MILESTONE2_23_1_BEASTFIRSTSEARCH_H
#define MILESTONE2_23_1_BEASTFIRSTSEARCH_H

#include <set>
#include "Searcher.h"
#include "CostComperator.h"
#include "State.h"

template<class T>
class BestFirstSearch : public Searcher<T> {
private:
    State<T> *popFromOpen(multiset<State<T> *, CostComparator<T>> &open);

protected:
    virtual double costBetweenNodes(State<T> *start, State<T> *end) const;

public:
    BestFirstSearch() {}

    virtual ~BestFirstSearch() {}

    virtual vector<State<T> *> search(Searchable<T> *searchable);
};


template<class T>
vector<State<T> *> BestFirstSearch<T>::search(Searchable<T> *searchable) {
    multiset<State<T> *, CostComparator<T>> open;
    set<State<T> *> closed;

    State<T> *curr = searchable->getInitialState();
    open.insert(curr);
    curr->setCameFrom(nullptr);

    while (!open.empty()) {
        curr = this->popFromOpen(open);
        closed.insert(curr);
        if (curr == searchable->getGoalState()) {
            break;
        }

        vector<State<T> *> successors = searchable->getAllPossibleStates(curr);
        for (State<T> *succ : successors) {
            // Ignoring walls
            if (succ->getCost() == -1) {
                continue;
            }
            if (closed.find(succ) != closed.end()) {
                continue;
            }
            // If 'succ' isn't in any of the lists - update it and add to 'open'
            if (open.find(succ) == open.end()) {
                succ->setCameFrom(curr);
                succ->setCost(succ->getCost() + curr->getCost());
                open.insert(succ);
                continue;
            }
            // If there is a better path - update cost
            double cost = this->costBetweenNodes(curr, succ);
            if (cost < succ->getCost()) {
                succ->setCost(cost);

                // If it's a new path
                if (succ->getCameFrom() != curr) {
                    succ->setCameFrom(curr);
                    // It's the same path as before - remove the node and insert back to update priority
                } else {
                    open.erase(succ);
                    open.insert(succ);
                }
            }
        }
    }
    return this->backTraceNodes(searchable->getGoalState());
}

template<class T>
State<T> *BestFirstSearch<T>::popFromOpen(multiset<State<T> *, CostComparator<T>> &open) {
    this->numOfNodesEvaluated++;
    State<T> *x = *(open.begin());
    open.erase(x);
    return x;
}

template<class T>
double BestFirstSearch<T>::costBetweenNodes(State<T> *start, State<T> *end) const {
    return start->getCost() + end->getOriginalCost();
}
#endif //MILESTONE2_23_1_BEASTFIRSTSEARCH_H
