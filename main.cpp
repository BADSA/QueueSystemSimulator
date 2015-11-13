#include "headers/dist_functions.h"
#include "headers/frecuencies.h"
#include "headers/prob.h"
#include "headers/prob_tests.h"
#include "headers/readers.h"
#include "headers/writers.h"
#include "headers/globals.h"


using namespace std;


int main() {

    //cout << media(numbers)<<endl;
    /*
    writeFile(m);

    double a[] = {17,73,141,198,203,148,92,75,31,17,3,1,1};
    vf obs(a,a + sizeof(a) / sizeof(double));

    vf expected;
    for(double i =0.0; i < 13.0 ; i++){
        expected.push_back(poisson(i,4.032)*1000);
    }

    vf v2 = foLessFe(obs,expected);

    vf v = fAcum(v2);


    ofstream outfile;
    outfile.open("out.txt");
    for(int i =0;i<v.size();i++){
        outfile << v[i]<<endl;
    }
    */


    /*

    vf numbers = readFileFloat("Arch2");
    msi m = setFrecuencies(numbers,numbers.size());

    double med = media(numbers);
    int n = *max_element(numbers.begin(),numbers.end());
    vf expected = binExpectedFrecuencies(m,med,n);

    vf observed = getObserved(m);
    //cout << chiSquared(observed,expected)<<endl;
    vf subtract = foLessFe(observed,expected);

    vf facum = fAcum(subtract);
    ofstream outfile;
    outfile.open("out.txt");
    for(int i =0;i<facum.size();i++){
        outfile << facum[i]<<endl;
    }



    */



    vf numbers = readFileFloat("S4.txt");
    sort(numbers.begin(),numbers.end());
    int lower = numbers.front();
    int upper = numbers.back();
    vector<pii> ranges = genRanges(lower,upper,30);



    vector<ppii> frecuencies = setFrecuencies2(ranges,numbers);
    writeFile2(frecuencies);

    /*
    vf observed = getObserved2(frecuencies);

    vf expected;
    for(int i =0;i<frecuencies.size();i++){
        int lower = frecuencies[i].first.first;
        int upper = frecuencies[i].first.second;
        expected.push_back(simpson3(lower,upper,30));
    }

    vf substrac = foLessFe(observed,expected);

    vf acum = fAcum(substrac);

    cout << chiSquared(observed,expected)<<endl;

    */


    /*
    cout << chiSquared(observed,expected)<<endl;

    ofstream outfile;
    outfile.open("out.txt");
    for(int i =0;i<acum.size();i++){
        outfile << acum[i]<<endl;
    }
    */

    cout << "Listo"<<endl;

    return 0;
}
