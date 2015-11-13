#ifndef EXAMENIO_DISTRIBUCIONES_DIST_FUNCTIONS_H
#define EXAMENIO_DISTRIBUCIONES_DIST_FUNCTIONS_H

#define e 2.71828152557319224769116772222332656383514404296875
#define pi 3.14159265358979323846


double normal(double standarDes, double miu, double x);
double poisson(double x,double lambda);
double binomial(int n,double k,double p);
double exponencial(double x);

#endif //EXAMENIO_DISTRIBUCIONES_DIST_FUNCTIONS_H
