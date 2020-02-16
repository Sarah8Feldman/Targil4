//
// Created by sarah on 25/01/2020.
//

#include "SolutionAnalyst.h"
SolutionAnalyst::SolutionAnalyst(){};
SolutionAnalyst::~SolutionAnalyst(){};
string SolutionAnalyst::getPathToGoal(vector<State<Point>*> vec) {
    string path;
    if (vec.empty()) {
        path = "";
    }
    path="";
    for (int i = 1; i < vec.size(); i++) {
        Point *prevPos = vec[i - 1]->getState();
        Point *postPos = vec[i]->getState();
        path += this->getDir(prevPos, postPos) + " ("+to_string(vec[i]->getCost())+") ";
        if(i<vec.size()-1){
            path += ",";
        }
    }
//    path.erase(path.size() - 2, path.size());
    return path;
}

string SolutionAnalyst::getDir( Point *befor, Point *after) {
    string retVal = "";
    if (after->getX() > befor->getX()) {
        retVal = "Down";
    }
    else if (after->getX() < befor->getX()) {
        retVal = "Up";
    }
    else if (after->getY() > befor->getY()) {
        retVal = "Right";
    }
    else{
        retVal = "Left";
    }
    return retVal;
}



