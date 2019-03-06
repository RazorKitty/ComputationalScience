#include<stdio.h>

int main(int argc, char **argv) {
    double H = 0.01;
	double T0 = 0.0;
	double Tf = 15.0;
	double T = 0.00;
	double n = Tf - T0 / H;
	double a = -2.0;
	double b = 2.0;
	double u = 0.0;
    double x[10000] = { 1.0 };
    int k = 0;
    int samples = 0;
    int sampleSize = 10;

    FILE *f = fopen("output.txt", "w");

    while (T <= 15) { 
        u = (T < 5) ? 2.0 : (T < 10) ? 1.0 : 3.0;
        x[k + 1] = x[k] + H * (a * x[k] + b * u);
        if (++samples % sampleSize == 0) {
            fprintf(f, "T=%.6f\tx[k]=%.6f\tU=%.6f\n", T, x[k], u);
        }
        T += H;
        ++k;
    }
    return 0;
}