#include <math.h>
#include "../headers/dist_functions.h"

/*
    Distribution functions.
*/

double normal(double standarDes, double miu, double x){
    return 1.0/(standarDes * sqrt( 2 * pi ))
           * pow(e,-0.5 * pow( (x-miu)/standarDes , 2 ));
}

long fact(int x){
    if (!x || x==1) return 1;
    else{
        return x * fact(x-1);
    }
}

double poisson(double x,double lambda){
    return (pow(e,-lambda) * pow(lambda,x)) / fact(x);
}

double combinations(double n,double k){
    if (k > n) return 0;
    if (k * 2 > n) /*return*/ k = n-k;  //remove the commented section
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

double binomial(int n,double k,double p){
    return combinations(n,k) * pow(p,k) * pow(1-p,n-k);
}

double exponential(double x){
    double l = 1 / 12.3697; // media de arch3
    return l * pow( e , (-l * x));
}