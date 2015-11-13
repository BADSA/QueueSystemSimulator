#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include "../headers/readers.h"

/*
    File Readers
*/
using namespace std;

vs readFileStr(std::string filename){
    vs v;
    ifstream infile(filename.c_str());
    string s;
    while (infile >> s){
        v.push_back(s);
    }
    return v;
}

vf readFileFloat(string filename){
    vf v;
    ifstream infile(filename.c_str());
    float s;
    while (infile >> s){
        v.push_back(s);
    }
    return v;
}

vf readFormatFile(string filename){
    vf v;
    freopen(filename.c_str(),"r",stdin);
    int num, denom;
    float s;
    while (scanf("%d/%d\n",&num, &denom) != EOF){
        s = num / (denom*1.0);
        v.push_back(s);
    }
    return v;
}