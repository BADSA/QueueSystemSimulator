#include "math.h"
#include "../headers/prob.h"

using namespace std;

double media(vf numbers){
    double total=0;
    for(int i =0 ; i < numbers.size() ; i++){
        total += numbers[i];
    }
    return (total/numbers.size());
}

double deviation(vf numbers, double ave) {
    double E = 0;
    double inverse = 1.0 / static_cast<double>(numbers.size());
    for(int i=0; i<numbers.size(); i++) {
        E += pow(static_cast<double>(numbers[i]) - ave, 2);
    }
    return sqrt(inverse * E);
}

vf getObserved(msi numbers){
    vf observed;
    for(std::map<int,int>::iterator iter = numbers.begin(); iter != numbers.end(); ++iter){
        double obs =  iter->second;
        observed.push_back(obs);
    }
    return observed;
}


vf getObserved2(vector<ppii> frecuencies){
    vf v;
    for(int i =0;i<frecuencies.size();i++){
        v.push_back(frecuencies[i].second);
    }
    return v;
}

vf foLessFe(vf observed,vf expected){
    vf v;
    for(int i =0 ; i < observed.size() ; i++){
        v.push_back(observed[i]-expected[i]);
    }
    return v;
}

vf fAcum(vf v){
    vf res;
    res.push_back(v[0]);
    for (int i =1;i<v.size();i++){
        res.push_back(res[i-1]+v[i]);
    }
    return res;
}

vector<pii> genRanges(int lower,int upper,float rngAmount){
    lower = (lower/10)*10;
    upper = ((upper+10)/10)*10;
    int totalNum = upper-lower;
    int reason = ceil(totalNum/rngAmount);
    vector<pii> ranges;
    pair<int,int> limits;
    ppii pp;

    while(rngAmount--){
        limits = make_pair(lower,lower+reason);
        ranges.push_back(limits);
        lower+=reason;
    }
    return ranges;
}