#include <vector>
#include "math.h"
#include "../headers/dist_functions.h"
#include "../headers/prob_tests.h"


double chiSquared(vf observed, vf expected){
    int n = observed.size();
    double result = 0;
    for(int i=0;i<n;i++){
        double base = observed[i]-expected[i];
        result += pow(base,2)/expected[i];
    }
    return result;
}


double simpson(double a,double b,double n){
    double h = (b-a)/n;
    double k = 0.0;
    double x = a + h;
    for (int i=1; i < (int)n/2 + 1;i++){
        k += 4 * exponential(x);
        x += 2 * h;
    }
    x = a + 2*h;
    for (int i=1; i < (int)n/2;i++){
        k +=  2 * exponential(x);
        x +=  2 * h;
    }
    return (h/3.0)*(exponential(a)+exponential(b)+k) * 1000;
}


double simpson2(double a,double b,double n){
    double h = (b-a)/n;
    double k = 0.0;
    double x = a + h;
    for (int i=1; i < (int)n/2 + 1;i++){
        k += 4 * normal(13.7167,100.1155,x);
        x += 2 * h;
    }
    x = a + 2*h;
    for (int i=1; i < (int)n/2;i++){
        k +=  2 * normal(13.7167,100.1155,x);
        x +=  2 * h;
    }
    return (h/3.0)*(normal(13.7167,100.1155,a)+normal(13.7167,100.1155,b)+k) * 1000;
}


double f(double x){
    return -0.10*x + (83.80);
}


double simpson3(double a,double b,double n){
    double h = (b-a)/n;
    double k = 0.0;
    double x = a + h;
    for (int i=1; i < (int)n/2 + 1;i++){
        k += 4 * f(x);
        x += 2 * h;
    }
    x = a + 2*h;
    for (int i=1; i < (int)n/2;i++){
        k +=  2 * f(x);
        x +=  2 * h;
    }
    return (h/3.0)*(f(a)+f(b)+k) * 1000;
}