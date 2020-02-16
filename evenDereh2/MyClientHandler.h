//
// Created by sarah on 25/01/2020.
//

#ifndef MILESTONE2_23_1_MYCLIENTHANDLER_H
#define MILESTONE2_23_1_MYCLIENTHANDLER_H
#include "ClientHandler.h"
#include "Solver.h"
#include <string>
#include <unistd.h>
#include <sstream>
#include <regex>
#include "Searcher.h"
#include "CacheManager.h"
#include "MatrixSearchable.h"
#include "SolutionAnalyst.h"

using namespace std;
template <class T>
class MyClientHandler: public ClientHandler{
private:
    Searcher<T> *searcher;
    CacheManager<string, string> *cacheManager;
    bool isEndOfLine(char* buffer);
public:
    MyClientHandler(CacheManager<string, string> *manager, Searcher<T> *searcher) {
        this->searcher = searcher;
        this->cacheManager = manager;
    }

    void handleClient(int sockfd){
        vector<string> vec = readFromSocket(sockfd);
//        testing matrix
//        vector<string> vec = readMatrixFromFile("matrix_test.txt");
//        vector<string> vec = readMatrixFromFile("mat.txt");
        Searchable<Point> *matrix= new MatrixSearchable(vec);
        string problem = matrix->toString();

        string solution = getSolution(cacheManager,matrix,searcher);
        char* finalSolution = &solution[0];
        cout << finalSolution << endl;
//        ssize_t writeVal = write(sockfd, finalSolution, solution.length());
//        problem = "";
//        if(writeVal < 0){
//            perror("error writing to socket - myTestClientHendler");
//        }
            }

    vector<string> readFromSocket(int sockfd) {
        vector<string> vec;
        string lineData;
        stringstream ss;
        char buffer[256] = {0};
        while (true) {
            int readVal = read(sockfd, buffer, 255);
            ss << buffer;
            buffer[256] = {0};
            string line = ss.str();
            cout << line << endl;
            if (line.substr(0).find("end") < line.size()) {
                break;
            }
//            if (isEndOfLine(ss.str())) {
//                break;
//            }
            if (readVal < 0) {
                perror("error reading from socket - ClientHendler");
            }
        }
        while (getline(ss,lineData)) {
            vec.push_back(lineData);
        }
        vec.pop_back();

        return vec;
    }

    bool isEndOfLine(string line) {
        if (line.substr(0).find("end") < line.size()) {
            return true;
        } else {
            return false;
        }
    }
    string getSolution(CacheManager<string,string> *cache, Searchable<Point> *matrix,
                       Searcher<Point> *searcher){
        string problem = matrix->toString();
        if(cache->isThereSolutionInMap(problem))
        {
            return cache->getSolution(problem);
        }
        else {
            vector<State<Point> *> nodes = searcher->search(matrix);
            SolutionAnalyst *sv = new SolutionAnalyst();
            string solution = sv->getPathToGoal(nodes);
            cache->insert(problem, solution);
            return solution;
        }
    }

    vector<string> readMatrixFromFile(string fileName){
        vector<string> tmpVec;
        vector<string>::iterator it;
        vector<string> finalVec;
        ifstream in_file;
        in_file.open(fileName, ios::in);
        if (!in_file) {
            throw ("an error");
        } else {
            string line;
            while (getline(in_file, line)) { //read data from file object and put it into string.
                tmpVec.push_back(line);
//                for (it = tmpVec.begin(); it != tmpVec.end(); it++)
//                {
//                    finalVec.push_back(*it);
//                }
            }
        }
        in_file.close(); //close the file object
        return tmpVec;
    }
    vector<string> regexMatches(string str) {

        string pattern = "(\\r\\n)|(-?\\d\\n?)";

        auto matches = regexer(str, pattern);
        return matches;
    }

/**
 * The regex function.
 * @param str
 * @param pattern
 * @return matches
 */
    vector<string> regexer(string str, string pattern) {
        vector<string> matches;

        auto reg = regex(pattern);
        auto iter = sregex_iterator(str.begin(), str.end(), reg);
        auto ith = sregex_iterator();

        // loop the matches
        for (auto i = iter; i != ith; ++i) {
            int count = 0;
            for (string match : *i) {
                // skip empty matches
                if (match.empty()) {
                    continue;
                }

                if (count > 0) {
                    matches.push_back(match);
                }
                count++;
            }
        }

        return matches;
    }

};
#endif //MILESTONE2_23_1_MYCLIENTHANDLER_H
