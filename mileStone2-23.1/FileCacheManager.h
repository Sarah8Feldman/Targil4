//
// Created by sarah on 19/01/2020.
//

#ifndef SERVER_FILECACHEMANAGER_H
#define SERVER_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <unordered_map>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include "MapSingleton.h"

class FileCacheManager:public CacheManager<string ,string>{
private:
    //map of <problem, solution>
//    unordered_map<string, string> cashMap;
    MapSingleton *myCacheMap;
public:
/**
 * in the constructor we check for existing problems(file names in the folder) and add them to map
 */
    FileCacheManager(){
        myCacheMap = MapSingleton::getInstance();

    };

    /**
 * checks for an existing problem and solution in ncacheMap
 * @param problem
 * @return true if problem had already been solved
 */
    bool isThereSolutionInMap(string problem){
        return myCacheMap->isInCacheMap(problem);
    };

    /**
 * read the solution fro a file
 * @param problem
 * @return  the solution for the problem
 */
    string getSolution(string problem){
        string solution = "";
        ifstream in_file;
        in_file.open(problem, std::ios::binary);
        if (!in_file) {
            cerr << "can't find file" << endl;
        } else {
            in_file.read((char *) &solution, sizeof(solution));
            in_file.close();
        }
        return solution;
    };

    /**
 * Insert a problem and it's solution
 * @param problem
 * @param solution
 */
    void insert(string problem, string solution){
        myCacheMap->insertToCacheMap(problem, solution);
        ofstream out_file;
        string fileName = problem;
        out_file.open(fileName, std::ios::binary);
        out_file.write((char*)&solution, sizeof(solution));
        out_file.close();
    };

};


#endif //SERVER_FILECACHEMANAGER_H
