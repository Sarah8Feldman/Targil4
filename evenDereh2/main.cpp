//
// Created by sarah on 23/01/2020.
//
#include "main.h"
using namespace boot;

    // validates the correctness of the port number
    bool Main::isNumber(const char* charValue){

        string varValue(charValue);

        if (varValue.size()<1){
            return false;
        }
        for (unsigned int i = 0; i<varValue.size();i++){
            if (!isdigit(varValue[i])){
                return false;
            }
        }
        return true;
    }

    int main(int argc, char **argv) {
        Main m;
        if (argc < 2) {
            m.main(Main::_DEFAULT_SERVER_PORT);
        }
        else{
            if (Main::isNumber(argv[1])) {
                m.main(atoi(argv[1]));
            }
            else {
                m.main(Main::_DEFAULT_SERVER_PORT);
            }
        }
    }

