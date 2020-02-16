//
// Created by sarah on 25/01/2020.
//

#ifndef MILESTONE2_23_1_MATRIX_H
#define MILESTONE2_23_1_MATRIX_H

#include "Point.h"
#include <vector>
#include "State.h"
template <class T>
class Matrix {
private:
    vector<vector<string >> myMatrix;
    vector<vector<State<Point>*>> myStateMatrix;
    int numOfRows, numOfColums, startRow, startColum, goalRow, goalColum;
    State<Point> **stateMatrix;
public:

    int getNumOfRows() const {
        return numOfRows;
    }

    int getNumOfColums() const {
        return numOfColums;
    }

    int getStartRow() const {
        return startRow;
    }

    int getStartColum() const {
        return startColum;
    }

    int getGoalRow() const {
        return goalRow;
    }

    int getGoalColum() const {
        return goalColum;
    }

    Matrix(vector<string> &vec) {
        numOfColums= this->getNumOfColumsFromString(vec.at(0));
        numOfRows = vec.size() - 3;
        this->setStartingPoint(vec.at(numOfRows));
        this->setGoalPoint(vec.at(numOfRows + 1));
//        this->createStateMatrix(vec);
    }
    vector<string> lineParser(string line) {
        int start_of_num = 0;
        int end_of_num;
        vector<string> line_vec;
        if (line[line.length() - 1] != ',') {
            line += ",";
        }
        while (true) {
            end_of_num = line.find(',', start_of_num);
            if (end_of_num != -1) {
                line_vec.push_back(line.substr(start_of_num, end_of_num - start_of_num));
                start_of_num = end_of_num + 1;
            } else {
                return line_vec;
            }
        }
    }
    void createCostMatrix(vector<string> matrix_vec) {
        int vec_size = matrix_vec.size() - 2; // variable for the loop to run throw only the lines of the matrix
        vector<string> line_vec;

        for (int i = 0; i < vec_size; i++) { // run throw all lines of the matrix
            line_vec = lineParser(matrix_vec.at(i));
            myMatrix.push_back(line_vec);
        }

    }

    double getNumOfColumsFromString(string &line) const {
        int counter = 0;
        stringstream check1(line);
        string intermediate;
        while(getline(check1, intermediate, ','))
        {
            counter++;
        }
        return (counter);
    }

    void setStartingPoint(string &str) {
        // 0,0
        startRow = stoi(str.substr(0, str.find(',')));
        startColum = stoi(str.substr(str.find(',') + 1));
    }

    void setGoalPoint(string &str) {
        //(N-1, N-1)
        goalRow = stoi(str.substr(0, str.find(',')));
        goalColum = stoi(str.substr(str.find(',') + 1));
    }
    State<Point> ** createStateMatrix(vector<string> &details) {
        // Creating one big continuous block of memory
        stateMatrix = new State<Point> *[numOfRows * numOfColums];
        string line = "";
        // Each cell in the matrix is a pointer to a State object
        for (int i = 0; i < numOfRows; i++) {
            line = details[i];
            int j=0;
            stringstream check1(line);
            string intermediate;
            // Tokenizing w.r.t. space ' '
            while(getline(check1, intermediate, ','))
            {
                Point *p = new Point(i,j);
                int cost = stoi(intermediate);
                stateMatrix[i * numOfColums + j] = new State<T>(p);
                stateMatrix[i * numOfColums + j]->setCost(cost);
                j++;
            }

//            for (int j = 0; j < numOfColums; j++) {
//                Point *p = new Point(i,j);
//
////                State<Point> *s = new State<T>(p);
//                stateMatrix[i * numOfColums + j] = new State<T>(p);
//                double cost = stod(line[j*2]);
//                stateMatrix[i * numOfColums + j]->setCost(cost);
//            }
        }

//        int n = 0;
//        // Setting the costs of all the cells in the matrix
//        for (int i = 0; i < numOfRows; i++) {
//            string curr = details.at(n);
//            for (int j = 0; j < numOfColums; j++) {
//                unsigned long index = curr.find(',');
//                if (index > curr.length()) {
//                    index = curr.length();
//                }
//                double cost = stod(curr.substr(0, index));
//                stateMatrix[i * numOfColums + j]->setCost(cost);
//                // If we reached the end of the string
//                if (index == curr.length()) {
//                    break;
//                }
//                // Ignoring spaces
//                if (curr[index + 1] == ' ') {
//                    curr = curr.substr(index + 2);
//                } else {
//                    curr = curr.substr(index + 1);
//                }
//            }
//            n++;
//        }
        return stateMatrix;
    }


};


#endif //MILESTONE2_23_1_MATRIX_H
