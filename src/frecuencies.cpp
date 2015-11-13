#include "../headers/dist_functions.h"
#include "../headers/frecuencies.h"

/*
    Set Frecuencies Functions
*/
using namespace std;

msi setFrecuencies(vf numbers,int size){
    msi points;
    for(int i =0 ; i < size ; i++){
        points[numbers[i]]++;
    }
    return points;
}

vector<ppii> setFrecuencies2(vector<pii> ranges,vf numbers){

    vector<ppii> frecuencies;
    for(int i=0;i<ranges.size();i++){
        ppii p;
        p = make_pair(ranges[i],0);
        frecuencies.push_back(p);
    }

    float curr;
    for(int i=0;i<numbers.size();i++){
        curr = numbers[i];
        for (int j=0;j<ranges.size();j++){
            int lower = ranges[j].first;
            int upper = ranges[j].second;
            if(curr>=lower && curr<upper){
                frecuencies[j].second++;
            }
        }
    }
    return frecuencies;
}

vf binExpectedFrecuencies(msi numbers,double media, double n){
    vf expected;
    double p = media / n;

    for(std::map<int,int>::iterator iter = numbers.begin(); iter != numbers.end(); ++iter){
        double k =  iter->first;
        double value = binomial(n, k ,p) * 1000;
        expected.push_back(value);
    }
    return expected;
}