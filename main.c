#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double random_double() {
    double range = RAND_MAX - 0;
    double div = RAND_MAX / range;
    return 0 + (rand() / div);
}

int main(/*int argc, char **argv*/) {
    double H = 0.01;
	//double T0 = 0.0;
	double Tf = 15.0;
	//double n = Tf - T0 / H;
	double a = -2.0;
	double b = 2.0;
	double u = 0.0;
    double x[10000] = { 1.0 };
    int k = 0;
    int samples = 0;
    int sampleSize = 10;
    FILE *file1 = fopen("output.txt", "w+");
    for(double T = 0; T < Tf; T += H, ++k) {
        u = (T < 5) ? 2.0 : (T < 10) ? 1.0 : 3.0;
        x[k + 1] = x[k] + H * (a * x[k] + b * u);
        if (++samples % sampleSize == 0)
            /* print T, x[k] u*/
            fprintf(file1, "%lf\t%lf\t%lf\n", T, x[k], u);
    }
    rewind(file1);
    FILE *file2 = fopen("noisy.csv", "w");
    int iteration = 1;
    double SD = 0.001;
    double m = 0.00;
    double T_in, xK_in, u_in;
    double A, B, z1, Xn;
    double z2 = 0;
    while(fscanf(file1, "%lf %lf %lf", &T_in, &xK_in, &u_in) > 0) {
        if (!(iteration % 2)) {
            //do something
            A = random_double() * (2 * M_PI);
            B = SD * sqrt(-2 * log(random_double()));
            z1 = B * sin(A) + m;
            z2 = B * cos(A) + m;
            Xn = xK_in + z1;
        } else {
            //do something else
            Xn = xK_in + z2;
        }
        ++iteration;
        fprintf(file2, "%lf,%lf,%lf,%lf\n", T_in, xK_in, Xn ,u_in);
    }
    return 0;
}
