#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>
#include<time.h>

double complex random_double() {
    return (double complex)rand()/((double complex)RAND_MAX/(double complex)1.00);
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



    srand(time(NULL));
    FILE *file2 = fopen("noisy.csv", "w");
    int iteration = 0;
    double complex SD = 0.001;
    double complex m = 0.00;
    double T_in, xK_in, u_in;
    double complex A, B, z1, Xn;
    double complex z2 = 0;
    while(fscanf(file1, "%lf %lf %lf", &T_in, &xK_in, &u_in) > 0) {
        A = (random_double()* (2.00 * M_PI));
        B = SD * csqrt(-2.00 * clog(random_double()));
        if (!(iteration % 2)) {
            //do something
            z1 = B * csin(A) + m;
            z2 = B * ccos(A) + m;
            Xn = xK_in + z1;
        } else {
            //do something else
            Xn = xK_in + z2;
        }
        ++iteration;
//        printf("A,B\t%lf\t%lf\nz1,z2\t %lf\t%lf\n",creal(A),creal(B),creal(z1),creal(z2));
        fprintf(file2, "%lf,%lf,%lf,%lf\n", T_in, xK_in, creal(Xn) ,u_in);
    }
    return 0;
}
