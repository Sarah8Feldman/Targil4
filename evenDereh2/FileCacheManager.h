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

        MapSingleton *myCacheMap;

        unsigned int hash_str(const string& str)
        {
            unsigned int b    = 378551;
            unsigned int a    = 63689;
            unsigned int hash = 0;

            for(std::size_t i = 0; i < str.length(); i++)
            {
                hash = hash * a + str[i];
                a    = a * b;
            }
            return (hash & 0x7FFFFFFF);
        }

        string getSolutionFileName (string problem){
            return "problem_"+to_string(hash_str(problem))+".txt";
        }

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
        bool result = false;
        if (!myCacheMap->isInCacheMap(problem)){
            string solutionFileName = getSolutionFileName(problem);
            fstream solutionFile;
            solutionFile.open(solutionFileName,ios::in);
            if (solutionFile) {
                result=true;
                solutionFile.close();
            }
        }
        return result;
    };

    /**
 * read the solution fro a file
 * @param problem
 * @return  the solution for the problem
 */
    string getSolution(string problem){
        string solution = "";
        string solutionFileName = getSolutionFileName(problem);
        fstream solutionFile;
        solutionFile.open(solutionFileName,ios::in);
        if(!solutionFile){
            cerr << "can't find file" << endl;
        } else{
            while(!solutionFile.eof())
            {
                getline(solutionFile,solution);
            }
        }
        return solution;
    };

    /**
 * Insert a problem and it's solution
 * @param problem
 * @param solution
 */
    void insert(string problem, string solution){
        string solutionFileName = getSolutionFileName(problem);
        myCacheMap->insertToCacheMap(problem, solution);
        fstream solutionFile;
        solutionFile.open(solutionFileName,ios::out);
        solutionFile<<solution;
        solutionFile.close();
    };

};

#endif //SERVER_FILECACHEMANAGER_H
