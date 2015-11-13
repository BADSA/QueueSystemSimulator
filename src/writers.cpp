#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include "../headers/writers.h"

/*
    File Writers
*/
using namespace std;

void writeFile(msi frecuencies){
    ofstream outfile;
    outfile.open("out.txt");
    typedef msi::iterator it_type;
    for(it_type it = frecuencies.begin(); it != frecuencies.end(); it++) {
        outfile << it->first << ","<<it->second<<endl;
    }
}

void writeFile2(vector<ppii> frecuencies){
    ofstream outfile;
    outfile.open("out.txt");
    for(int i =0;i<frecuencies.size();i++){
        //outfile <<"[" << frecuencies[i].first.first << "," << frecuencies[i].first.second<<"[ = ";
        //        frecuencies[i].second<<endl;
        outfile <<frecuencies[i].first.second<<","<<
        frecuencies[i].second<<endl;
    }
}